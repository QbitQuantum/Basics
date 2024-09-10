	handle *frontend_controller::profile(const void *in_image_address)
	{
		if (1 == _InterlockedIncrement(_worker_refcount.get()))
		{
			shared_ptr<void> exit_event(::CreateEvent(NULL, TRUE, FALSE, NULL), &::CloseHandle);
			auto_ptr<thread> frontend_thread(new thread(bind(&frontend_controller::frontend_worker,
				_frontend_thread.get(), _factory, &_collector, _image_load_queue, exit_event)));

			_frontend_thread.release();

			swap(_exit_event, exit_event);
			swap(_frontend_thread, frontend_thread);
		}

		return new profiler_instance(in_image_address, _image_load_queue, _worker_refcount, _exit_event);
	}