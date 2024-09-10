void env_relocate (void)
{
	DEBUGF ("%s[%d] offset = 0x%lx\n", __FUNCTION__,__LINE__, gd->reloc_off);

	env_ptr = (env_t *)mALLOc (CONFIG_ENV_SIZE);
	DEBUGF ("%s[%d] malloced ENV at %p\n", __FUNCTION__,__LINE__,env_ptr);

    set_env_funcptrs() ;
    (*env_init)() ;

	if (gd->env_valid == 0) {
#if defined(CONFIG_GTH)	|| defined(CONFIG_ENV_IS_NOWHERE)	/* Environment not changable */
		puts ("Using default environment\n\n");
#else
		//puts ("*** Warning - bad CRC, using default environment\n\n");
		puts ("*** We do not have environment varialbes stored in the booting storgage, so we using default environment\n\n");
		//show_boot_progress (-60);
#endif
		set_default_env();
	}
	else {
        printf("  Finding the environment variables in boot storage...\n") ;
		(*env_relocate_spec)();
	}
	gd->env_addr = (ulong)&(env_ptr->data);
}