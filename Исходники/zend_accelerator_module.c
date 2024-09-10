static ZEND_INI_MH(OnUpdateMemoryConsumption)
{
	zend_long *p;
	zend_long memsize;
#ifndef ZTS
	char *base = (char *) mh_arg2;
#else
	char *base = (char *) ts_resource(*((int *) mh_arg2));
#endif

	/* keep the compiler happy */
	(void)entry; (void)mh_arg2; (void)mh_arg3; (void)stage;

	p = (zend_long *) (base + (size_t)mh_arg1);
	memsize = atoi(ZSTR_VAL(new_value));
	/* sanity check we must use at least 8 MB */
	if (memsize < 8) {
		const char *new_new_value = "8";
		zend_ini_entry *ini_entry;

		memsize = 8;
		zend_accel_error(ACCEL_LOG_WARNING, "opcache.memory_consumption is set below the required 8MB.\n");
		zend_accel_error(ACCEL_LOG_WARNING, ACCELERATOR_PRODUCT_NAME " will use the minimal 8MB configuration.\n");

		if ((ini_entry = zend_hash_str_find_ptr(EG(ini_directives),
					"opcache.memory_consumption",
					sizeof("opcache.memory_consumption")-1)) == NULL) {
			return FAILURE;
		}

		ini_entry->value = zend_string_init(new_new_value, 1, 1);
	}
	if (UNEXPECTED(memsize > ZEND_ULONG_MAX / (1024 * 1024))) {
		*p = ZEND_ULONG_MAX;
	} else {
		*p = memsize * (1024 * 1024);
	}
	return SUCCESS;
}