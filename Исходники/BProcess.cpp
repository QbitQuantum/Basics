	uint64_t Process::processid() const {
#ifdef _MSC_VER
		return (uint64_t)_getpid();
#else
		return (uint64_t)getpid();
#endif
}