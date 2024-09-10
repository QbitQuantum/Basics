            inline handle create_anonymous_semaphore(long initial_count,long max_count)
            {
#if !defined(BOOST_NO_ANSI_APIS)  
                handle const res=CreateSemaphoreA(0,initial_count,max_count,0);
#else
                handle const res=CreateSemaphoreW(0,initial_count,max_count,0);
#endif               
                if(!res)
                {
                    boost::throw_exception(thread_resource_error());
                }
                return res;
            }