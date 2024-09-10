        void crash_handler::set_thread_exception_handlers()
        {
            if (!is_crash_handle_enabled())
                return;

            // Catch terminate() calls. 
            // In a multithreaded environment, terminate functions are maintained 
            // separately for each thread. Each new thread needs to install its own 
            // terminate function. Thus, each thread is in charge of its own termination handling.
            // http://msdn.microsoft.com/en-us/library/t6fk7h29.aspx
            
            // NOTE : turn off terminate handle
            // set_terminate(terminate_handler);       

            // Catch unexpected() calls.
            // In a multithreaded environment, unexpected functions are maintained 
            // separately for each thread. Each new thread needs to install its own 
            // unexpected function. Thus, each thread is in charge of its own unexpected handling.
            // http://msdn.microsoft.com/en-us/library/h46t5b69.aspx  
            set_unexpected(unexpected_handler);    

            // Catch a floating point error
            typedef void (*sigh)(int);
            signal(SIGFPE, (sigh)sigfpe_handler);     

            // Catch an illegal instruction
            signal(SIGILL, sigill_handler);     

            // Catch illegal storage access errors
            signal(SIGSEGV, sigsegv_handler);   

        }