		bool ObjectWatcher::StartWatching(HANDLE object, Delegate* delegate) {
			CHECK(delegate);
			if (wait_object_) {
				NOTREACHED() << "Already watching an object";
				return false;
			}

			// Since our job is to just notice when an object is signaled and report the
			// result back to this thread, we can just run on a Windows wait thread.
			DWORD wait_flags = WT_EXECUTEINWAITTHREAD | WT_EXECUTEONLYONCE;

			// DoneWaiting can be synchronously called from RegisterWaitForSingleObject,
			// so set up all state now.
			callback_ = base::Bind(&ObjectWatcher::Signal, weak_factory_.GetWeakPtr(),
				delegate);
			object_ = object;
			origin_loop_ = MessageLoop::current();

			if (!RegisterWaitForSingleObject(&wait_object_, object, DoneWaiting,
				this, INFINITE, wait_flags)) {
				DPLOG(FATAL) << "RegisterWaitForSingleObject failed";
				object_ = NULL;
				wait_object_ = NULL;
				return false;
			}

			// We need to know if the current message loop is going away so we can
			// prevent the wait thread from trying to access a dead message loop.
			MessageLoop::current()->AddDestructionObserver(this);
			return true;
		}