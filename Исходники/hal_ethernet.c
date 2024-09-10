static u08 __eth_init_interface( u08 internal_id, char const * keyname )
{
	u08 result = (u08)GetPrivateProfileIntA( "interfaces", 
		keyname, 0x0ff, "../ijw-router-win32.ini" );
	if (result == 0xff)
		return 0;

	if (eth_init_interface( internal_id, result ))
	{
		num_interfaces = internal_id + 1;
		return 1;
	}

	return 0;
}