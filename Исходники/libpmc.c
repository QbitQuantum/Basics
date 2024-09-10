K runtest(K opv, K ecxv, K eaxv, K edxv, K testCount)
{
	struct MsrInOut s_pmc_reset[9];
	struct MsrInOut s_pmc_read[9];
	unsigned long long s_ffc_fixed[FFC_COUNT];
	unsigned long long s_pmc_fixed[PMC_COUNT]; 
	struct MsrInOut *ptr;
	int i;
	long long count;
	void *handle;
	char *error;
	K result;
	void (*execute_test)(void (s1)(void), void(s2)(void));

	// dynamically load the test library
	handle = dlopen("libtest.so", RTLD_NOW);
	//handle = dlopen("libtest.so", RTLD_LAZY);
	if (!handle) {
		krr(dlerror()); // signal exception to kdb+
		return (K)0;
	}
	execute_test = dlsym(handle, "execute_test");
	if ((error = dlerror()) != NULL) {
		krr("While locating symbof 'execute_test'");
		return (K)0;
	}


	// zero the fixed-cost accumulators
	for (i = 0 ; i < PMC_COUNT ; i++)
		s_pmc_fixed[i] = 0;
	for (i = 0 ; i < FFC_COUNT ; i++)
		s_ffc_fixed[i] = 0;

	// set the global (static) pointers
	ffc_fixed = s_ffc_fixed;
	pmc_fixed = s_pmc_fixed;
	pmc_reset = s_pmc_reset;
	pmc_read = s_pmc_read;
	ptr = pmc_cfg = (struct MsrInOut*)malloc((opv->n + 1) * sizeof(struct MsrInOut));

	if (pmc_cfg == NULL) {
		orr("malloc");
		return (K)0;
	}
	
	record_reset();
	record_read();

	// record the PMC instructions to memory
	count = opv->n;
	for (i = 0 ; i < count ; i++) {
		wr_msrio(ptr++, kI(opv)[i], kI(ecxv)[i], kI(eaxv)[i], kI(edxv)[i]);
	}
	msr_wr_stop(ptr++);
	
	loadDriver();
	if (fd == -1) {
		return (K)0;
	}
	result = run_test(execute_test, testCount->i);
	
	// disable and zero the PMC MSRs
	ioctl(fd, IOCTL_MSR_CMDS, (long long)s_pmc_reset);

	// return the dynamically allocated memory
	free(pmc_cfg);	
	// close the dyn-lib function handle
	dlclose(handle);
	// close the MSR driver
	closeDriver(fd);

	return result;
}