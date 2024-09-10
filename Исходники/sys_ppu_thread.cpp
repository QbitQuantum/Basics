void sys_ppu_thread_yield()
{
	sys_ppu_thread.trace("sys_ppu_thread_yield()");

	std::this_thread::yield();
}