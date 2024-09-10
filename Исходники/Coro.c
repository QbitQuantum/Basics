void Coro_initializeMainCoro(Coro *self)
{
	self->isMain = 1;
#ifdef USE_FIBERS
	// We must convert the current thread into a fiber if it hasn't already been done.
	if ((LPVOID) 0x1e00 == GetCurrentFiber()) // value returned when not a fiber
	{
		// Make this thread a fiber and set its data field to the main coro's address
		ConvertThreadToFiber(self);
	}
	// Make the main coro represent the current fiber
	self->fiber = GetCurrentFiber();
#endif
}