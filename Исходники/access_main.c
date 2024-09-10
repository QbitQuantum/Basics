int sub_do_cam( int device_no, DWORD card_id, DWORD time, char* show_buf, int max_show_buf )
{
	char buf[64];
	char time_area_list[32];
	int group_id;
	int allow_id;
	int not_allow_id;
	char white_name_content[32];
	int no, time_area_no;
	DWORD begin_time, end_time;
	int password = 0;

	//cam_read_white_name_record( card_id, buf );
	_d_u( card_id );
	if( cam_read_group_id_from_white_name_record( card_id, buf, sizeof(buf) ) < 0 ){
		error_message( (char*)"can not search this card_id", card_id );
		goto do_cam_error_exit;
	}
	//old design: 职员工号，职员姓名，物理卡号，组别，用户密码，反潜会控制
	// card_id,group_id,show_mode_id,data....
	//_d_str( buf );
	strcpy( white_name_content, buf );
	_d_str( white_name_content );
	if( white_name_list_get_value( buf, &group_id, &allow_id, &not_allow_id, &password ) < 0 )
		goto not_allow_enter;
	//goto do_cam_error_exit;

	//_d_str( white_name_content );
	if( cam_read_time_area_list_from_week_table( group_id, time, time_area_list, sizeof(time_area_list) ) < 0 ){
		error_message( (char*)"read time_area_list error", group_id );
		goto not_allow_enter;
		//goto do_cam_error_exit;
	}
	// loop check the time_area
	_d_str( time_area_list );
	no = 0;
	while( 1 ){
		_d_int( no );
		time_area_no = cam_get_no_from_time_area_list( time_area_list, no );
		if( time_area_no <= 0 )
			break;
		_d_int( time_area_no );
		//get time area, and check ok.
		if( cam_read_time_area_from_time_area_file( time_area_no, &begin_time, &end_time ) < 0 ){
			error_message( (char*)"read time_area from time_area_file error", time_area_no );
			break;
		}
		_d_int( begin_time );
		_d_int( end_time );
		_d_int( time );
		if( begin_time <= time && time <= end_time ){
			if( show_buf ){
				// check the password.
#if 0
				if( password ){
					buf[0] = 0;
					if( main_basic_gui_get_string( buf, sizeof(buf) ) < 0 ){
						// or hint password input problem?
						goto not_allow_enter;
					}
					if( password != atoi( buf ) ){
						// or hint password error?
						goto not_allow_enter;
					}
				}
#endif
				if( card_group_operate() < 0 )
					goto not_allow_enter;

#if 0
				// the password is ok.
				// deal the show info.
				if( txt_file_read_line( "/c/show", allow_id, buf, sizeof(buf) ) > 0 ){
					//_d_str( buf );
					cam_show( buf, white_name_content, show_buf, max_show_buf );
				}
				else{
					s_sprintf( show_buf, "%u, Allowed", card_id );
				}
#endif
			}
			return allow_id;
		}
		no ++;
	}
	_d_line();
not_allow_enter:
	_d_line();
#if 0	
	if( show_buf ){
		_d_line();
		// deal the show info.
		if( txt_file_read_line( "/c/show", not_allow_id, buf, sizeof(buf) ) > 0 ){
			//_d_str( buf );
			cam_show( buf, white_name_content, show_buf, max_show_buf );
		}
		else{
			s_sprintf( show_buf, "%u, Not Allowed", card_id );
		}
		return -1;
	}
#endif
	return -1;

do_cam_error_exit: 	
	_d_line();
#if 0	
	if( show_buf ){
		_d_line();
		if( txt_file_read_line( "/c/show", 0, buf, sizeof(buf) ) > 0 ){
			char *po = show_buf;
			char *buf_po;
			int len ;
			//_d_str( buf );
			white_name_content[0] = 0;
			s_sprintf( po, "%u", card_id );
			len = strlen( po );
			po += len;
			buf_po = buf;
			_d_hex( buf_po[0] );
			_d_hex( buf_po[1] );
			_d_hex( buf_po[2] );
			_d_hex( buf_po[3] );
			if( (unsigned char)buf_po[0] == (unsigned char)0xef && (unsigned char)buf_po[1] == (unsigned char)0xbb && (unsigned char)buf_po[2] == (unsigned char)0xbf )
				buf_po += 3;
			cam_show( buf_po, white_name_content, po, max_show_buf-len );
		}
		else{
			s_sprintf( show_buf, "%u, Error", card_id );
		}
	}
#endif	
	//return -1;
	// illegal card
	return -2;

}