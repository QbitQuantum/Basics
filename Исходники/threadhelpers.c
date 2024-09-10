int sysArchPrctl(int which, void *addr) {
	int error = 0;
	uintptr_t uaddr = (uintptr_t)addr;

	if (uaddr & (0xFFFF8000UL << 32)) {
		return -EINVAL;
	}
	thread_t thread = getCurrentThread();
	switch (which) {
		case PRCTL_FS:
			thread->fsBase = addr;
			wrmsr(0xC0000100, uaddr);
			break;
		case PRCTL_GS:
			thread->gsBase = addr;
			wrmsr(0xC0000102, uaddr);
			break;
		default:
			error = -EINVAL;
			break;
	}

	return error;
}