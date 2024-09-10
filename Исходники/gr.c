int gr_init(void)
{
	int org_gamma;
	int retcode;
        int mode = SM(320,200);

	// Only do this function once!
	if (gr_installed==1)
                return 3;

#ifdef __DJGPP__
	if (!__djgpp_nearptr_enable()) {
		printf("nearptr enable=%x\n", __dpmi_error);
		return 10;
	}
#ifndef SAVEGR
	gr_video_memory = (unsigned char *)(__djgpp_conventional_base + 0xa0000);
#else
	gr_video_memory=(unsigned char *)-1;
#endif
	pVideoMode =  (volatile ubyte *)(__djgpp_conventional_base+0x449);
	pNumColumns = (volatile ushort *)(__djgpp_conventional_base+0x44a);
	pNumRows = (volatile ubyte *)(__djgpp_conventional_base+0x484);
	pCharHeight = (volatile ushort *)(__djgpp_conventional_base+0x485);
	pCursorPos = (volatile ushort *)(__djgpp_conventional_base+0x450);
	pCursorType = (volatile ushort *)(__djgpp_conventional_base+0x460);
	pTextMemory = (volatile ushort *)(__djgpp_conventional_base+0xb8000);
#endif
#ifndef __DJGPP__
	if (gr_init_A0000())
		return 10;
#endif

	// Save the current text screen mode
	if (gr_save_mode()==1)
                return 2;

#ifndef NOGRAPH
	// Save the current palette, and fade it out to black.
	gr_palette_read( gr_pal_default );
	gr_palette_faded_out = 0;
	org_gamma = gr_palette_get_gamma();
	gr_palette_set_gamma( 0 );
	gr_palette_fade_out( gr_pal_default, 32, 0 );
	gr_palette_clear();
	gr_palette_set_gamma( org_gamma );
	gr_sync_display();
	gr_sync_display();
#endif

#ifdef __DJGPP__
#ifdef SAVEGR
	__djgpp_nearptr_disable();
#endif
#endif

	MALLOC( grd_curscreen,grs_screen,1 );
	memset( grd_curscreen, 0, sizeof(grs_screen));

	// Set the mode.
	if ((retcode=gr_set_mode(mode)))
	{
		gr_restore_mode();
		return retcode;
	}
	//JOHNgr_disable_default_palette_loading();

	// Set all the screen, canvas, and bitmap variables that
	// aren't set by the gr_set_mode call:
	grd_curscreen->sc_canvas.cv_color = 0;
	grd_curscreen->sc_canvas.cv_drawmode = 0;
	grd_curscreen->sc_canvas.cv_font = NULL;
	grd_curscreen->sc_canvas.cv_font_fg_color = 0;
	grd_curscreen->sc_canvas.cv_font_bg_color = 0;
	gr_set_current_canvas( &grd_curscreen->sc_canvas );

#if 0
	if (!dpmi_allocate_selector( &gr_fade_table, 256*GR_FADE_LEVELS, &gr_fade_table_selector ))
		Error( "Error allocating fade table selector!" );

	if (!dpmi_allocate_selector( &gr_palette, 256*3, &gr_palette_selector ))
		Error( "Error allocating palette selector!" );
#endif

//	if (!dpmi_allocate_selector( &gr_inverse_table, 32*32*32, &gr_inverse_table_selector ))
//		Error( "Error allocating inverse table selector!" );


	// Set flags indicating that this is installed.
	gr_installed = 1;
#ifdef __GNUC__

	atexit((void (*)) gr_close);
#else
	atexit(gr_close);
#endif
	return 0;
}