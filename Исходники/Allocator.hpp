		/**
		* Frees memory
		* @param ptr Address of the memory to deallocate
		*/
		void deallocate(ptr_t ptr)
		{
			//Free memory
			int ec = VirtualFreeEx(	proc_.getHandle(),
											reinterpret_cast<void*>(ptr),
											0,
											MEM_RELEASE);
			if(!ec)
			{
				dword_t error = GetLastError();
				throw WinException(	"Process::freeMemory()",
											"VirtualFreeEx()",
											error);
			}

			//If case scoped_release was specified we need to remove the pointer
			if(scoped_release)
			{
				if(allocations_.size() == 0)
					return;

				AllocIter element;
				element = std::find(allocations_.begin(), allocations_.end(), ptr);

				if((*element) == ptr)
					allocations_.erase(element);
			}
		}