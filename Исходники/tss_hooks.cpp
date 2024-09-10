    extern "C" RCF_BOOST_THREAD_DECL void RBT_on_process_exit(void)
    {
        boost::call_once(init_threadmon_mutex, once_init_threadmon_mutex);
        boost::mutex::scoped_lock lock(*threadmon_mutex);

#ifndef __MINGW32__
        BOOST_ASSERT(attached_thread_count == 0);
#endif

        //Free the tls slot if one was allocated.

        if (tls_key != invalid_tls_key)
        {
            TlsFree(tls_key);
            tls_key = invalid_tls_key;
        }
    }