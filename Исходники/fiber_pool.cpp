FiberPool_::coro_pull_interface* FiberPool_::getFiber(size_t size, void** sp, coro_handler h, void* param /*= NULL*/)
{
	assert(size && size % 4096 == 0 && size <= 1024 * 1024);
	void* currentFiber = NULL;
#if _WIN32_WINNT >= 0x0600
	if (IsThreadAFiber())
	{
		currentFiber = GetCurrentFiber();
	}
	else
	{
		currentFiber = ConvertThreadToFiberEx(NULL, FIBER_FLAG_FLOAT_SWITCH);
	}
#else//#elif _MSC_VER >= 0x0501
	currentFiber = ConvertThreadToFiberEx(NULL, FIBER_FLAG_FLOAT_SWITCH);
	if (!currentFiber)
	{
		currentFiber = GetCurrentFiber();
	}
#endif
	{
		fiber_pool_pck& pool = s_fiberPool._fiberPool[size / 4096 - 1];
		pool._mutex.lock();
		if (!pool._pool.empty())
		{
			coro_pull_interface* oldFiber = pool._pool.back();
			pool._pool.pop_back();
			pool._mutex.unlock();
			oldFiber->_fiber._pushHandle = currentFiber;
			oldFiber->_fiber._currentHandler = h;
			oldFiber->_fiber._fiberHandle->_param = param;
			oldFiber->_fiber._tick = 0;
			*sp = oldFiber->_fiber._fiberHandle->_stackTop;
			SwitchToFiber(oldFiber->_fiber._fiberHandle);
			return oldFiber;
		}
		pool._mutex.unlock();
	}
	s_fiberPool._stackCount++;
	s_fiberPool._stackTotalSize += size;
	coro_pull_interface* newFiber = new coro_pull_interface;
#ifdef _WIN64
	newFiber->_fiber._fiberHandle = (FiberStruct_*)CreateFiberEx(size, 64 * 1024, FIBER_FLAG_FLOAT_SWITCH, FiberPool_::fiberHandler, newFiber);
#else
	newFiber->_fiber._fiberHandle = (FiberStruct_*)CreateFiberEx(size, 0, FIBER_FLAG_FLOAT_SWITCH, FiberPool_::fiberHandler, newFiber);
#endif
	if (newFiber->_fiber._fiberHandle)
	{
		newFiber->_fiber._pushHandle = currentFiber;
		newFiber->_fiber._currentHandler = h;
		newFiber->_fiber._fiberHandle->_param = param;
		newFiber->_fiber._tick = 0;
		*sp = newFiber->_fiber._fiberHandle->_stackTop;
		SwitchToFiber(newFiber->_fiber._fiberHandle);
		return newFiber;
	}
	delete newFiber;
	throw std::shared_ptr<string>(new string("Fiber不足"));
}