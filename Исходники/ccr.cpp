static void* ccr_worker(void *arg)
{
    int r, resume;
    process_t *proc;
    while (1)
    {
        // Checks if threads need to be killed and the the ready procces's queue is empty
        // That way only when the queue is empty the threads are killed
        // if ((free_flag.compare_and_swap(false, true)) && (prc_ready.empty()))
        if (free_flag.compare_and_swap(false, true))
        {
            pthread_t thread = pthread_self();
            // removes reference from the pool
            thr_pool.remove(thread);

            // checks if threre's more threads to kill and set the flag
            if (free_workers.fetch_and_decrement() > 1)
            {
                free_flag.compare_and_swap(true, false);
            }

            //kills the current thread
            pthread_exit(NULL);
        }
        prc_ready.pop(proc);
        if (!proc) return NULL;
        r = lua_resume(proc->L, 0);
        switch (r)
        {
            case  LUA_YIELD:
                //cerr << "Yield!\n";
                switch (proc->status)
                {
                    case PS_READY:
                        // releasing the lock acquired in ccr_yield
                        proc->wlock.release();
                        prc_ready.push(proc);
                        break;
                    case PS_BLOCKING:
                        proc->status = PS_BLOCKED;
                        // releasing the lock acquired in ccr_yield
                        proc->wlock.release();
                        break;
                }
                break;
            case LUA_ERRRUN:
            case LUA_ERRMEM:
            case LUA_ERRERR:
                cerr << "[ERROR][PROCESSING A LUA PROCESS] " << lua_tostring(proc->L, -1) << endl;
                // fall-through
            case 0:
                lua_close(proc->L);
                mbx_close(proc->mbox);
                prc_free(proc);
                break;
        }
    }
    return NULL;
}