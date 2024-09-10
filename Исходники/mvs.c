static void neogeo_exit(void)
{
	SceUID fd;
	char path[MAX_PATH];

	video_set_mode(32);
	video_clear_screen();

	ui_popup_reset();

	video_clear_screen();
	msg_screen_init(WP_LOGO, ICON_SYSTEM, TEXT(EXIT_EMULATION2));

	msg_printf(TEXT(PLEASE_WAIT2));

#ifdef ADHOC
	if (!adhoc_enable)
#endif
	{
		sprintf(path, "%smemcard/%s.bin", launchDir, game_name);
		if ((fd = sceIoOpen(path, PSP_O_WRONLY|PSP_O_CREAT, 0777)) >= 0)
		{
			sceIoWrite(fd, neogeo_memcard, 0x800);
			sceIoClose(fd);
		}

		sprintf(path, "%snvram/%s.nv", launchDir, game_name);
		if ((fd = sceIoOpen(path, PSP_O_WRONLY|PSP_O_CREAT, 0777)) >= 0)
		{
			swab(neogeo_sram16, neogeo_sram16, 0x2000);
			sceIoWrite(fd, neogeo_sram16, 0x2000);
			sceIoClose(fd);
		}


#ifdef COMMAND_LIST
		free_commandlist();
#endif

		if (neogeo_save_sound_flag) option_sound_enable = 1;
		save_gamecfg(game_name);
	}

	msg_printf(TEXT(DONE2));

#ifdef ADHOC
	if (adhoc_enable) adhocTerm();
#endif

	show_exit_screen();
}