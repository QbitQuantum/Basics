    virtual void schedule(pplx::TaskProc_t proc, void* param)
    {
        pplx::details::atomic_increment(s_flag);
        auto schedulerParam = std::unique_ptr<_Scheduler_Param>(new _Scheduler_Param(proc, param));
        auto work = CreateThreadpoolWork(DefaultWorkCallbackTest, schedulerParam.get(), NULL);

        if (work == nullptr)
        {
            throw utility::details::create_system_error(GetLastError());
        }

        SubmitThreadpoolWork(work);
        CloseThreadpoolWork(work);
        schedulerParam.release();
    }