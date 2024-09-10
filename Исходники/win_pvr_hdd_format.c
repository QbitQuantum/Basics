static void hddfmt_start()
{
	UINT8 back_saved;
	win_popup_choice_t choice;
	UINT8 mode;
	struct dvr_HDD_info hdd_info;
	char volume_name[48];
	char osd_name[48];
	char hint[64];
	BOOL ret;

	disk_format_mode_num = get_fsystem_installed(disk_mode, 8);
	//sprintf(temp, "%s", disk_mode[input]);

	storage_index_to_osd_string((UINT8)hddfmt_cur_volume,osd_name);	
	sprintf(hint, "Are you sure to format the %s?", osd_name);

	if(disk_format_mode_num == 1)
	{
		win_compopup_init(WIN_POPUP_TYPE_OKNO);
		win_compopup_set_btnstr_ext(0, disk_mode[0]);
		win_compopup_set_default_choice(WIN_POP_CHOICE_NO);		
	}
	else if(disk_format_mode_num == 2)
	{
		win_compopup_init(WIN_POPUP_TYPE_OKNOCANCLE);
		win_compopup_set_btnstr_ext(0, disk_mode[0]);
		win_compopup_set_btnstr_ext(1, disk_mode[1]);
		win_compopup_set_default_choice(WIN_POP_CHOICE_CANCEL);		
	}
	win_compopup_set_msg(hint, NULL, 0);
	choice = win_compopup_open_ext(&back_saved);

	if(((disk_format_mode_num == 1) && (choice == WIN_POP_CHOICE_YES)) || ((disk_format_mode_num == 2) && ((choice == WIN_POP_CHOICE_YES) || (choice == WIN_POP_CHOICE_NO))))
	{
		if(choice == WIN_POP_CHOICE_YES)
			mode = 1;
		else
			mode = 2;

		storage_index2volume((UINT8)hddfmt_cur_volume,volume_name);
		storage_add_parent_dir(volume_name);		
		win_compopup_init(WIN_POPUP_TYPE_SMSG);
		win_compopup_set_frame(GET_MID_L(286), GET_MID_T(130), 286, 130);
		win_compopup_set_msg_ext("formating wait!",NULL,0);
		win_compopup_open_ext(&back_saved);
		ret = pvr_format_multi_hdd(mode, volume_name);
		win_compopup_smsg_restoreback();

		if(!ret) 		
		{
			win_compopup_init(WIN_POPUP_TYPE_OK);
			sprintf(hint, "Format %s error?", osd_name);
			win_compopup_set_msg(hint, NULL, 0);
			win_compopup_set_default_choice(WIN_POP_CHOICE_CANCEL);		
			win_compopup_open_ext(&back_saved);
			return;
		}

		if(STRCMP((char *)pvr_get_mout_prefix(), volume_name)==0)
		{
			if(pvr_get_HDD_info(&hdd_info))
			{
				api_pvr_check_level(&hdd_info);		
				ap_clear_all_message();//or usb reflash msg maybe send fail
				pvr_evnt_callback(0, PVR_HDD_FORMATTED);
			}		
		}
		win_hddfmt_draw_disk_infor();
	}
}