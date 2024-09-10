int main(int argc, char **argv, char **envp)
{
	uint64_t module_count;
	proc_module_info_t *buffer = NULL;
	struct lpar_info_format1_t  lpar_data1;
	struct utsname my_uname;
	int rc;
	int i;
	char *progname;
	char iobuf[BUFSIZ];

	setvbuf(stdout, iobuf, _IOFBF, sizeof(iobuf));

	progname=(char*)strdup((const char*)basename(argv[0]));
	if (!progname)
	{
		fprintf(stderr, "FATAL: Buffer allocation failed at (%s:%d): %s, error code %d\n",
		 __FILE__, __LINE__, strerror(errno), errno);
		return EXIT_FAILURE;
	}

	uname(&my_uname);

	/* Retrieve the total count of modules on the system */
	rc = lpar_get_info(NUM_PROC_MODULE_TYPES, &module_count, sizeof(uint64_t));
			 
	if (rc)
	{
		fprintf(stderr, "%s: lpar_get_info(NUM_PROC_MODULES_TYPES, ...) failed at (%s:%d):  %s, error code %d\n",
		 progname, __FILE__, __LINE__, strerror(errno), errno);
		return EXIT_FAILURE;
	}
	             
	/* Allocate buffer of exact size to accomodate module information */
	buffer = malloc(module_count * sizeof(proc_module_info_t));
	     
	if (!buffer)
	{
		fprintf(stderr, "%s: Buffer allocation failed at (%s:%d): %s, error code %d\n",
		 progname, __FILE__, __LINE__, strerror(errno), errno);
		return EXIT_FAILURE;
	}
	
	rc = lpar_get_info(PROC_MODULE_INFO, buffer, (module_count * sizeof(proc_module_info_t)));
	
	if (rc)
	{
		fprintf(stderr, "%s: lpar_get_info(PROC_MODULE_INFO, ...) failed at (%s:%d):  %s, error code %d\n",
		 progname, __FILE__, __LINE__, strerror(errno), errno);
		return EXIT_FAILURE;
	}
	
	/* Retrieve the static LPAR structure */
	rc = lpar_get_info(LPAR_INFO_FORMAT1, &lpar_data1, sizeof(lpar_data1));
			 
	if (rc)
	{
		fprintf(stderr, "%s: lpar_get_info(LPAR_INFO_FORMAT1, ...) failed at (%s:%d):  %s, error code %d\n",
		 progname, __FILE__, __LINE__, strerror(errno), errno);
		return EXIT_FAILURE;
	}


	/*  If rc is 0, then buffer contains an array of proc_module_info_t
	 *  structures with module_count elements.  For an element of 
	 *  index i:
	 *       
	 *      buffer[i].nsockets is the total number of sockets
	 *      buffer[i].nchips   is the number of chips per socket		 
	 *      buffer[i].ncores   is the number of cores per chip
	 */
	 
	printf(
	  "Nodename     %-." QUOTE(SYS_NMLN) "s\n"
	  "LPAR         %-." QUOTE(LPAR_NAME_LEN1) "s\n"
	  "Machine      %-." QUOTE(SYS_NMLN) "s\n"
	  "Sysname      %-." QUOTE(SYS_NMLN) "s\n"
	  "Version      %-." QUOTE(SYS_NMLN) "s\n"
	  "Release      %-." QUOTE(SYS_NMLN) "s\n"
	  "SMT threads  %hu\n",
	  &(my_uname.nodename),
	  &(lpar_data1.lpar_name),
	  &(my_uname.machine),
	  &(my_uname.sysname),
	  &(my_uname.version),
	  &(my_uname.release),
	  lpar_data1.smt_threads);

	for (i=0 ; i < module_count ; i++)
	{
		printf(
		  "Sockets      %d\n"
		  "Chips/Socket %d\n"
		  "Cores/Chip   %d\n"
		  "Cores/Socket %d\n",
		  buffer[i].nsockets,
		  buffer[i].nchips,
		  buffer[i].ncores,
		  buffer[i].ncores * buffer[i].nchips);
	}
	fflush(stdout);
	return 0;
}