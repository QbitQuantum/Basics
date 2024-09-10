int property_change_system_value( char* name, char* value )
{
	
	typedef struct{
		char name[64];
		char value[64];
		//byte size;
		//byte flag;		// 0 is int, 1 is string
		//byte sync;
		//byte tmp;
	}_s_node_prop_item;
	
	// system value update.
	// ipaddr etc...
	int kc;
	char *ki[ 15 ];
	//char tmp_buf[  sizeof( npi->value ) ];
	char tmp_buf[  64 ];
	int val1, val2, val3, val4;
	_s_node_prop_item tmp_npi;
	_s_node_prop_item *npi;

	npi = &tmp_npi;
	strcpy( npi->name, name );
	strcpy( npi->value, value );
	_d_str( name );
	_d_str( value );
	
	// add the , explain the sys command string.
	if( strcmp( npi->name, "ipaddr" ) == 0 
			|| strcmp( npi->name, "ip" ) == 0 ){
		_d_str( (char*)npi->value );
		memcpy( tmp_buf, npi->value, sizeof( npi->value ) );
		kc = analysis_string_to_strings_by_decollator( tmp_buf, ".", ki, 15 );
		if( kc != 4 )
			return 0;
		g_machine_ip[0] = atoi( ki[0] );
		g_machine_ip[1] = atoi( ki[1] );
		g_machine_ip[2] = atoi( ki[2] );
		g_machine_ip[3] = atoi( ki[3] );
		//debug_show_ip_str(g_machine_ip);
		return 0;
	}
	else if( strcmp( npi->name, "hostip" ) == 0 ){
		_d_str( (char*)npi->value );
		memcpy( tmp_buf, npi->value, sizeof( npi->value ) );
		kc = analysis_string_to_strings_by_decollator( tmp_buf, ".", ki, 15 );
		if( kc != 4 )
			return 0;
		g_send_package_socket_ip[0] = atoi( ki[0] );
		g_send_package_socket_ip[1] = atoi( ki[1] );
		g_send_package_socket_ip[2] = atoi( ki[2] );
		g_send_package_socket_ip[3] = atoi( ki[3] );
		//debug_show_ip_str(g_send_package_socket_ip);
		return 0;
	}
	else if( strcmp( npi->name, "hport" ) == 0 ){
		_d_str( (char*)npi->value );
		val1 = atoi( (char*)npi->value );
		g_send_package_socket_port = val1;
		_d_int( g_send_package_socket_port );
		return 0;
	}
	else if( strcmp( npi->name, "webport" ) == 0 ){
		return 0;
	}
	else if( strcmp( npi->name, "timeout" ) == 0 ){
		_d_str( (char*)npi->value );
		val1 = atoi( (char*)npi->value );
		g_net_time_out = val1;
		_d_int( g_net_time_out );
		return 0;
	}
	else if( strcmp( npi->name, "no" ) == 0 ){
		_d_str( (char*)npi->value );
		val1 = atoi( (char*)npi->value );
		g_machine_no = val1;
		_d_int( g_machine_no );
		return 0;
	}
	else if( strcmp( npi->name, "keyboard" ) == 0 ){
		_d_str( (char*)npi->value );
		_d_buf( (char*)npi->value, sizeof( npi->value ) );
		if( s_strcmp( (char*)npi->value, "disable" ) == 0 ){
			//Key_EnableScan( 0 );
		}
		else{
			//Key_EnableScan( 1 );
		}
		//val1 = atoi( (char*)npi->value );
		//g_machine_no = val1;
		//_d_int( g_machine_no );
		return 0;
	}
	else if( strcmp( npi->name, "hosttype" ) == 0 ){
		_d_str( (char*)npi->value );
		if( strcmp( (char*)npi->value, "tcmd" ) == 0 )
			g_host_type = 1;
		else if( strcmp( (char*)npi->value, "dlc" ) == 0 )
			g_host_type = 2;
		else
			g_host_type = 0;
		
		//val1 = atoi( (char*)npi->value );
		//g_machine_no = val1;
		_d_int( g_host_type );
		return 0;
	}
	return -1;
}