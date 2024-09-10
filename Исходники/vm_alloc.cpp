int vm_reset_write_watch(void * addr, size_t size)
{
#ifdef HAVE_VM_WRITE_WATCH
#ifdef HAVE_WIN32_VM
	int ret_code = ResetWriteWatch(addr, size);
	return ret_code == 0 ? 0 : -1;
#endif
#endif
	// Unsupported
	return -1;
}