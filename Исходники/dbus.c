int hw_dbus_exit(void)
{
	int err;

	// exit linkport
	if((err = lc.close()))
	{
		print_lc_error(err);
		return -1;
	}
	if((err = lc.exit()))
	{ 
		print_lc_error(err);
		return -1;
	}
	
	// exit directfile
	exit_linkfile();

    return 0;
}