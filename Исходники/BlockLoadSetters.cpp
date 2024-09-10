intptr_t CustomMemFree(void* allocator, void* pointer)
{
	intptr_t retval = g_origMemFree(allocator, pointer);

	/*if (pointer != nullptr && *g_unsafePointerLoc)
	{
		size_t allocSize = 0;

		if (g_unsafeStack.size() == 0)
		{
			{
				std::unique_lock<std::mutex> lock(g_allocMutex);

				auto it = g_allocData.find(pointer);

				if (it != g_allocData.end())
				{
					allocSize = it->second;
					g_allocData.erase(it);
				}
			}

			if (**(void***)g_unsafePointerLoc >= pointer && **(void***)g_unsafePointerLoc < ((char*)pointer + allocSize))
			{
				std::vector<uintptr_t> stackList(96);

				uintptr_t* stack = (uintptr_t*)_AddressOfReturnAddress();

				for (int i = 0; i < stackList.size(); i++)
				{
					stackList[i] = stack[i];
				}

				g_unsafeStack = stackList;
			}
		}

	}*/

	if (/*!g_didLevelFree && */pointer != nullptr)
	{
		//std::unique_lock<std::mutex> lock(g_allocMutex);
		EnterCriticalSection(&g_allocCS);

		uintptr_t ptr = (uintptr_t)pointer;

		auto it = g_allocData.find(ptr);

		if (it != g_allocData.end())
		{
			size_t allocSize = it->second;

			static char* location = hook::pattern("4C 8D 0D ? ? ? ? 48 89 01 4C 89 81 80 00 00").count(1).get(0).get<char>(3);
			static char** g_collectionRoot = (char**)(location + *(int32_t*)location + 4);

			for (int i = 0; i < 0x950; i++)
			{
				if (g_collectionRoot[i])
				{
					void* baad = *(void**)(g_collectionRoot[i] + 32);

					if (baad >= pointer && baad < ((char*)pointer + allocSize))
					{
						atArray<char>* array = (atArray<char>*)(g_collectionRoot[i] + 128);

						trace("freed collection %s (%p-%p)\n", &array->Get(0), pointer, allocSize + (char*)pointer);

						uintptr_t* stack = (uintptr_t*)_AddressOfReturnAddress();
						stack += (32 / 8);

						for (int i = 0; i < 16; i++)
						{
							trace("stack: %p\n", stack[i]);
						}
					}
				}
			}
			/*if (g_inLevelFree)
			{
			if (allocSize != -1)
			{
			int stackIdx = g_stackIdx++;

			std::vector<uintptr_t> stackList(96);

			uintptr_t* stack = (uintptr_t*)_AddressOfReturnAddress();

			for (int i = 0; i < stackList.size(); i++)
			{
			stackList[i] = stack[i];
			}

			g_stacks[stackIdx] = stackList;

			trace("level free: %p-%p - stack idx: %d\n", pointer, (char*)pointer + allocSize, stackIdx);
			}
			}*/

			g_allocData.erase(it);
		}

		LeaveCriticalSection(&g_allocCS);
	}

	return retval;
}