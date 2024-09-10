	void uthread::enter_thread()
	{
		uthread_impl *impl = new uthread_impl();
		void *f = ConvertThreadToFiber(impl);
		if(!f)
		{
			delete impl;
			DeleteFiber(f);
			return;
		}

		impl->fiber = f;

		if(!dry_thread)
		{
			dry_thread = uthread_create(uthread_dry, nullptr);
			dry_thread->mSuspended = true;
		}

		enter_thread_common();
	}