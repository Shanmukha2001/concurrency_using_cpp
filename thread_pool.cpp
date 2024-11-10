    #include "thread_pool.h"

    int main(){
        thread_pool pool;
        std::cout<<"Testing thread pool"<<std::endl;
        for(int i=0;i<100;i++){
            pool.submit([=]{
                std::cout<<"thread: "<<i<<" printed: "<<std::this_thread::get_id()<<std::endl;
            });
        }
        system("pause");
    }