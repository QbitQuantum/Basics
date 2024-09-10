int main(int argc, char **argv, char **envp)
{
    uc_engine *uc;
    uc_err err;
	int ret;
	uc_hook hhc;
	uint32_t val;
	EmuStarterParam_t starter_params;
#ifdef _WIN32
	HANDLE th = (HANDLE)-1;
#else
	pthread_t th;
#endif

	// dynamically load shared library
#ifdef DYNLOAD
	uc_dyn_load(NULL, 0);
#endif

	// Initialize emulator in MIPS 32bit little endian mode
    printf("uc_open()\n");
	err = uc_open(UC_ARCH_MIPS, UC_MODE_MIPS32, &uc);
    if (err)
	{
        printf("Failed on uc_open() with error returned: %u\n", err);
        return err;
    }

	// map in a page of mem
	printf("uc_mem_map()\n");
	err = uc_mem_map(uc, addr, 0x1000, UC_PROT_ALL);
    if (err)
	{
        printf("Failed on uc_mem_map() with error returned: %u\n", err);
        return err;
    }

	// write machine code to be emulated to memory
	printf("uc_mem_write()\n");
    err = uc_mem_write(uc, addr, loop_test_code, sizeof(loop_test_code));
	if( err )
	{
        printf("Failed on uc_mem_write() with error returned: %u\n", err);
        return err;
    }
	
    // hook all instructions by having @begin > @end
	printf("uc_hook_add()\n");
    uc_hook_add(uc, &hhc, UC_HOOK_CODE, mips_codehook, NULL, 1, 0);
	if( err )
	{
        printf("Failed on uc_hook_add(code) with error returned: %u\n", err);
        return err;
    }
	
	
	// start background thread
	printf("---- Thread Starting ----\n");
	starter_params.uc = uc;
	starter_params.startAddr = addr;
	starter_params.endAddr = addr + sizeof(loop_test_code);

#ifdef _WIN32
	// create thread
	th = (HANDLE)_beginthreadex(NULL, 0, win32_emu_starter, &starter_params, CREATE_SUSPENDED, NULL);
	if(th == (HANDLE)-1)
	{
		printf("Failed on _beginthreadex() with error returned: %u\n", _errno());
		return -1;
	}
	// start thread
	ret = ResumeThread(th);
	if( ret == -1 )
	{
		printf("Failed on ResumeThread() with error returned: %u\n", _errno());
		return -2;
	}
	// wait 3 seconds
	Sleep(3 * 1000);
#else
	// add posix code to start the emu_starter() thread
	ret = pthread_create(&th, NULL, posix_emu_starter, &starter_params);
	if( ret )
	{
		printf("Failed on pthread_create() with error returned: %u\n", err);
		return -2;
	}
	// wait 3 seconds
	sleep(3);
#endif


	// Stop the thread after it has been let to run in the background for a while
	printf("---- Thread Stopping ----\n");
	printf("uc_emu_stop()\n");
	err = uc_emu_stop(uc);
	if( err )
	{
        printf("Failed on uc_emu_stop() with error returned: %u\n", err);
        return err;
    }
	test_passed_ok = true;
	

	// done executing, print some reg values as a test
	uc_reg_read(uc, UC_MIPS_REG_PC, &val);	printf("pc is %X\n", val);
	uc_reg_read(uc, UC_MIPS_REG_A0, &val);	printf("a0 is %X\n", val);
	
	// free resources
	printf("uc_close()\n");
	uc_close(uc);
	
	if( test_passed_ok )
		printf("\n\nTEST PASSED!\n\n");
	else
		printf("\n\nTEST FAILED!\n\n");

	// dynamically free shared library
#ifdef DYNLOAD
    uc_dyn_free();
#endif

	return 0;
}