void _run_wizard_action(
		HWND        hwnd,
		_wz_sheets *sheets,
		_dnode     *node
												
	)
{
	BOOL set_loader = (BOOL)
		SendMessage(
			GetDlgItem(sheets[WPAGE_ENC_BOOT].hwnd, IDC_COMBO_BOOT_INST), CB_GETCURSEL, 0, 0
			);

	wchar_t *fs_name = 
		fs_names[SendMessage(
			GetDlgItem(sheets[WPAGE_ENC_FRMT].hwnd, IDC_COMBO_FS_LIST), CB_GETCURSEL, 0, 0
			)];

	int  kb_layout = _get_combo_val( GetDlgItem(sheets[WPAGE_ENC_PASS].hwnd, IDC_COMBO_KBLAYOUT), kb_layouts );
	BOOL q_format  = _get_check( sheets[WPAGE_ENC_FRMT].hwnd, IDC_CHECK_QUICK_FORMAT );

	int is_small = (
		IsWindowEnabled( GetDlgItem( sheets[WPAGE_ENC_CONF].hwnd, IDC_COMBO_ALGORT ) ) ? FALSE : TRUE
	);

	crypt_info  crypt;
	dc_pass    *pass = NULL;

	crypt.cipher_id  = _get_combo_val( GetDlgItem(sheets[WPAGE_ENC_CONF].hwnd, IDC_COMBO_ALGORT), cipher_names );
	crypt.wp_mode    = _get_combo_val( GetDlgItem(sheets[WPAGE_ENC_CONF].hwnd, IDC_COMBO_PASSES), wipe_modes );
 
	node->dlg.rlt = ST_ERROR;

	switch ( node->dlg.act_type )
	{
	///////////////////////////////////////////////////////////////
	case ACT_REENCRYPT :
	///////////////////////////////////////////////////////////////
	/////// REENCRYPT VOLUME //////////////////////////////////////
	{
		wchar_t mnt_point[MAX_PATH] = { 0 };
		wchar_t vol[MAX_PATH];

		dlgpass dlg_info = { node, NULL, NULL, mnt_point };

		ShowWindow(hwnd, FALSE);
		if ( _dlg_get_pass(__dlg, &dlg_info) == ST_OK )
		{
			node->mnt.info.status.crypt.wp_mode = crypt.wp_mode;
			node->dlg.rlt = dc_start_re_encrypt( node->mnt.info.device, dlg_info.pass, &crypt );

			secure_free( dlg_info.pass );
			if ( mnt_point[0] != 0 )
			{
				_snwprintf( vol, sizeof_w(vol), L"%s\\", node->mnt.info.w32_device );
				_set_trailing_slash( mnt_point );

				if ( SetVolumeMountPoint(mnt_point, vol) == 0 )
				{
					__error_s( __dlg, L"Error when adding mount point", node->dlg.rlt );
				}
			}
		} else {
			node->dlg.rlt = ST_CANCEL;
		}
	}
	break;
	///////////////////////////////////////////////////////////////
	case ACT_ENCRYPT_CD :
	///////////////////////////////////////////////////////////////
	/////// ENCRYPT CD ////////////////////////////////////////////
	{
		_init_speed_stat( &node->dlg.iso.speed );
		pass = _get_pass_keyfiles( sheets[WPAGE_ENC_PASS].hwnd, IDE_PASS, IDC_USE_KEYFILES, KEYLIST_CURRENT );		

		if ( pass )
		{
			DWORD resume;
			{
				wchar_t s_src_path[MAX_PATH] = { 0 };
				wchar_t s_dst_path[MAX_PATH] = { 0 };

				GetWindowText( GetDlgItem(sheets[WPAGE_ENC_ISO].hwnd, IDE_ISO_SRC_PATH), s_src_path, sizeof_w(s_src_path) );
				GetWindowText( GetDlgItem(sheets[WPAGE_ENC_ISO].hwnd, IDE_ISO_DST_PATH), s_dst_path, sizeof_w(s_dst_path) );

				wcscpy( node->dlg.iso.s_iso_src, s_src_path );
				wcscpy( node->dlg.iso.s_iso_dst, s_dst_path );

				node->dlg.iso.cipher_id = crypt.cipher_id;
				node->dlg.iso.pass      = pass;
			}

			node->dlg.iso.h_thread = 
				CreateThread(
					NULL, 0, _thread_enc_iso_proc, pv(node), CREATE_SUSPENDED, NULL
					);

			SetThreadPriority( node->dlg.iso.h_thread, THREAD_PRIORITY_LOWEST );
			resume = ResumeThread( node->dlg.iso.h_thread );

			if ( !node->dlg.iso.h_thread || resume == (DWORD) -1 )
			{
				__error_s( hwnd, L"Error create thread", -1 );
				secure_free(pass);
			}
		}		
	}
	break;
	///////////////////////////////////////////////////////////////
	default :
	///////////////////////////////////////////////////////////////
	{
		node->mnt.info.status.crypt.wp_mode = crypt.wp_mode;
		node->dlg.rlt = ST_OK;

		if ( sheets[WPAGE_ENC_BOOT].show )
		{
			if ( set_loader )
			{
				node->dlg.rlt = _set_boot_loader( hwnd, -1, is_small );
			}
		}
		if ( ( node->dlg.rlt == ST_OK ) && 
			 ( IsWindowEnabled( GetDlgItem( sheets[WPAGE_ENC_PASS].hwnd, IDC_LAYOUTS_LIST ) ) ) 
		   )
		{
			node->dlg.rlt = _update_layout( node, kb_layout, NULL );
		}
		if ( node->dlg.rlt == ST_OK )
		{
			switch ( node->dlg.act_type )
			{
		///////////////////////////////////////////////////////////////
			case ACT_ENCRYPT :
		///////////////////////////////////////////////////////////////
		/////// ENCRYPT VOLUME ////////////////////////////////////////
			{
				pass = _get_pass_keyfiles( sheets[WPAGE_ENC_PASS].hwnd, IDE_PASS, IDC_USE_KEYFILES, KEYLIST_CURRENT );

				if ( pass != NULL )
				{
					node->dlg.rlt = dc_start_encrypt( node->mnt.info.device, pass, &crypt );
					secure_free(pass);
				}
			}
			break;
		///////////////////////////////////////////////////////////////
			case ACT_FORMAT :
		///////////////////////////////////////////////////////////////
		/////// FORMAT VOLUME /////////////////////////////////////////
			{
				pass = _get_pass_keyfiles( sheets[WPAGE_ENC_PASS].hwnd, IDE_PASS, IDC_USE_KEYFILES, KEYLIST_CURRENT );
				if ( pass )
				{
					node->dlg.rlt = dc_start_format( node->mnt.info.device, pass, &crypt );
					secure_free(pass);
				}
			}
			break;
			}
		}
	}
	}
	node->dlg.q_format = q_format;
	node->dlg.fs_name  = fs_name;

	if ( !node->dlg.iso.h_thread )
	{
		EndDialog( hwnd, 0 );
	}
}