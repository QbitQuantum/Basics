/**
 * Initialization function. Returns context for processing dev-mode delay.
 */
VbAudioContext *VbAudioOpen(VbCommonParams *cparams)
{
	GoogleBinaryBlockHeader* gbb =
		(GoogleBinaryBlockHeader *)cparams->gbb_data;
	VbAudioContext *audio = &au;
	int use_short = 0;
	uint64_t a, b;

	/* Note: may need to allocate things here in future */

	/* Calibrate audio delay */
	a = VbExGetTimer();
	VbExSleepMs(10);
	b = VbExGetTimer();
	ticks_per_msec = (b - a) / 10ULL ;
	VBDEBUG(("VbAudioOpen() - ticks_per_msec is %llu\n", ticks_per_msec));

	/* Initialize */
	Memset(audio, 0, sizeof(*audio));
	audio->background_beep = 1;
	audio->play_until = b;                /* "zero" starts now */

	/* See if we have full background sound capability or not. */
	if (VBERROR_SUCCESS != VbExBeep(0,0)) {
		VBDEBUG(("VbAudioOpen() - VbExBeep() is limited\n"));
		audio->background_beep = 0;
	}

	/*
	 * Prepare to generate audio/delay event. Use a short developer screen
	 * delay if indicated by GBB flags.
	 */
	if (gbb->major_version == GBB_MAJOR_VER && gbb->minor_version >= 1
	    && (gbb->flags & GBB_FLAG_DEV_SCREEN_SHORT_DELAY)) {
		VBDEBUG(("VbAudioOpen() - using short dev screen delay\n"));
		use_short = 1;
	}

	VbGetDevMusicNotes(audio, use_short);
	VBDEBUG(("VbAudioOpen() - note count %d\n", audio->note_count));

	return audio;
}