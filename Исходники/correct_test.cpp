void increment() {
	type res = __hle_acquire_test_and_set4(&lock);
	while (res == 1) { // wait until lock was not locked
		_mm_pause();
//		__asm volatile ("pause" ::: "memory");
		res = __hle_acquire_test_and_set4(&lock);
	}
//	printf("Acquired Lock: %d  |  i: %d\n", lock, i);

	usleep(1); // provoke an error
	i++;

	__hle_release_clear4(&lock);
//	printf("Released Lock: %d  |  i: %d\n", lock, i);
}