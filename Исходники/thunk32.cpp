	Thunk32Base::Thunk32Base()
	{
		// Double checked locking, guaranteed by Acquire/Release-semantics in Microsoft's
		// volatile-implementation.
		if(bytecodeHeap == NULL)
		{
			hMutex = CreateMutex(NULL, TRUE, NULL);
			while (hMutex == (HANDLE)NULL || hMutex == (HANDLE)ERROR_ALREADY_EXISTS || hMutex == (HANDLE)ERROR_ACCESS_DENIED) {
				Sleep(1000);
			}

			if(bytecodeHeap == NULL)
			{
				bytecodeHeap = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE, 0, 0);
				if(bytecodeHeap == NULL)
				{
					throw std::exception("Heap creation failed!");
				}

				// Schedule the heap to be destroyed when the application terminates.
				// Until then, it will manage its own size.
				atexit(cleanupHeap);
			}
		}

		bytecode = reinterpret_cast<Bytecode*>(HeapAlloc(bytecodeHeap, 0, sizeof(Bytecode)));
		if(bytecode == NULL) 
		{
			throw std::exception("Bytecode allocation failed!");
		}
		new (bytecode) Bytecode;
	}