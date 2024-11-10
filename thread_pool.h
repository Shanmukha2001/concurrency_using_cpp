    #include<thread>
    #include<atomic>
    #include<vector>
    #include<iostream>
    #include<functional>
    #include "./cpp_concurrency_masterclass-master/common/common_thread_safe_queue.h"
    #include "./cpp_concurrency_masterclass-master/common/common_objs.h"
    #include "./cpp_concurrency_masterclass-master/common/utils.h"

    class thread_pool
    {
        std::atomic_bool done;
        threadsafe_queue<std::function<void()>> work_queue;
        std::vector<std::thread> threads;
        join_threads joiner;

        void work_thread(){
            while (!done)
            {
                std::function<void()> task;
                if(work_queue.try_pop(task)){
                    task();
                }else{
                    std::this_thread::yield();
                }
            }
            
        }

        public:
        thread_pool():done(false),joiner(threads){
            int const thread_count = std::thread::hardware_concurrency();
            try{
                for(int i=0;i< thread_count;i++){
                    threads.push_back(
                        std::thread(&thread_pool::work_thread,this)
                    );
                }
            }catch(...){
                done = true;
                throw;
            }
        }

        template<typename Function_type>
        void submit(Function_type f){
            work_queue.push(std::function<void()>(f));
        }

        ~thread_pool(){
            done = true;
        }
    };

