		Thread::ThreadPtr IoServiceCore::createNamedThread(const char* name)
		{
			auto thread = Thread::create();
			thread->run();

			LOGT("Create named thread [ %s -- %s ]", name, thread->getThreadId());

			_namedThread.insert(make_pair(name, thread));
			return thread;
		}