static void win_miscset_save_setting(void)
{
	MULTISEL	*msel;
	SYSTEM_DATA* sys_data;
	UINT32 val;

	sys_data = sys_data_get();

#ifndef NEW_DEMO_FRAME
	struct nim_lnb_info lnb_info;
	for(i=0;i<2;i++)
	{
        lib_nimg_get_lnb_info(i+1,&lnb_info);
        if(LNB_POWER_OFF == sys_data->bLNB_power)
            lnb_info.lnb_power_off = 1;
        else
            lnb_info.lnb_power_off = 0;                      
		lib_nimg_set_lnb_info(i+1,&lnb_info);
	}
#else
	struct nim_config lnb_info;
	struct nim_device *nim;
UINT16 i;
	for(i=0;i<2;i++)
	{
        nim = (struct nim_device *)dev_get_by_id(HLD_DEV_TYPE_NIM, i);
        dev_get_nim_config(nim,FRONTEND_TYPE,&lnb_info);
        if(LNB_POWER_OFF == sys_data->bLNB_power)
            lnb_info.antenna.antenna_enable = /*0*/1;   //Seiya fix BUG37540:
        else
            lnb_info.antenna.antenna_enable = 1;                   
	    dev_set_nim_config(nim, FRONTEND_TYPE, &lnb_info);
	}
#endif

	msel =&miscset_sel1;
	val = OSD_GetMultiselSel(msel);
	sys_data->chan_sw = val;
	
	msel =&miscset_sel2;
	val = OSD_GetMultiselSel(msel);
	sys_data->chchgvideo_type = val;

#ifdef CHANCHG_VIDEOTYPE_SUPPORT
#ifndef NEW_DEMO_FRAME
	UIChChgSetVideoType(sys_data->chchgvideo_type);
#endif
#endif
	
	msel =&miscset_sel3;
	val = OSD_GetMultiselSel(msel);
	sys_data->install_beep = val;

    msel =&miscset_sel4;
	val = OSD_GetMultiselSel(msel);
	sys_data->auto_standby_en= val;


#ifdef ORDER_GZ1207009
	   msel =&miscset_sel6;
	val = OSD_GetMultiselSel(msel);
	sys_data->standbymode= val;
#endif

#ifdef RAM_TMS_TEST
    msel =&miscset_sel5;
	val = OSD_GetMultiselSel(msel);

	char rec_part[16];
	char tms_part[16];

	if (sys_data->ram_tms_en != val) // detach tms part
	{
		rec_part[0] = tms_part[0] = 0;
		pvr_get_cur_mode(rec_part, tms_part);
		if (tms_part[0] != 0)
		{
			if (STRCMP(rec_part, tms_part) == 0)
				pvr_set_disk_use(PVR_REC_ONLY_DISK, rec_part);
			else
				pvr_detach_part(tms_part, PVR_TMS_ONLY_DISK);
			api_pvr_adjust_tms_space();
		}
	}
	
	if (sys_data->ram_tms_en == 0 && val == 1) // enable RAM disk timeshift
	{
		UINT32 ram_len = RAM_DISK_SIZE;	
		UINT32 ram_addr = (void *)(RAM_DISK_ADDR & 0x0fffffff | 0x80000000);

		ramdisk_create((UINT32)ram_addr, ram_len);

		struct pvr_register_info pvr_reg_info;
		MEMSET(&pvr_reg_info, 0, sizeof(struct pvr_register_info));
		STRCPY(pvr_reg_info.mount_name, "/mnt/rda1");
		pvr_reg_info.disk_usage = PVR_TMS_ONLY_DISK;
		pvr_reg_info.sync = 1;
		pvr_reg_info.init_list = 0;
		pvr_reg_info.check_speed = 0;
		pvr_register((UINT32)&pvr_reg_info, 0);
	}
	else if (sys_data->ram_tms_en == 1 && val == 0) // disable RAM disk timeshift
	{
		ramdisk_delete();
	}

	if (sys_data->ram_tms_en != val)
	{
		if (val == 0) // disable RAM disk timeshift, select PVR partition again
		{
			UINT8 back_saved;
			rec_part[0] = tms_part[0] = 0;
			pvr_select_part(rec_part, tms_part);
			if (rec_part[0] != 0 || tms_part[0] != 0)
			{
				win_compopup_init(WIN_POPUP_TYPE_SMSG); 					   
				win_compopup_set_msg_ext("Init PVR partitions, please wait...", NULL, 0);
				win_compopup_open_ext(&back_saved);
				if (STRCMP(rec_part, tms_part) == 0)
				{
					pvr_change_part(rec_part, PVR_REC_AND_TMS_DISK);
				}
				else
				{
					pvr_change_part(rec_part, PVR_REC_ONLY_DISK);
					pvr_change_part(tms_part, PVR_TMS_ONLY_DISK);
				}
				win_compopup_smsg_restoreback();
			}
		}
		
		struct dvr_HDD_info hdd_info;
		pvr_get_HDD_info(&hdd_info);
		api_pvr_check_level(&hdd_info);
		if (pvr_get_cur_mode(NULL, NULL) == PVR_DISK_INVALID)
		{
			api_pvr_clear_up_all();
		}
	}
	sys_data->ram_tms_en = val;
#endif

    sys_data_save(1);
    
}