#include <thread>
#include <atomic>
#include <future>

using namespace std;

class interrupt_flag{
    bool local_flag;
    public:
        void set()
        {
            local_flag = true;
        }
        bool is_set()
        {
            return local_flag;
        }
};

thread_local interrupt_flag this_thread_flag; // Thread-local interrupt flag

class jthread_local{
    thread _thread;
    interrupt_flag* flag;
    public:
    template<typename Functiontype>
    jthread_local(Functiontype f){
        promise<interrupt_flag*> p;
        _thread = std::thread([f, &p] {
			p.set_value(&this_thread_flag);
			f();
			});
        flag = p.get_future().get();
    }

    void interrupt()
	{
		flag->set();
	}

	~jthread_local()
	{
		if (_thread.joinable())
			_thread.join();
	}
};

bool interrupt_point()
{
	if (this_thread_flag.is_set())
		return true;
	return false;
}

int main(){

}