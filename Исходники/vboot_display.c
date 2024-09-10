VbError_t VbCheckDisplayKey(VbCommonParams *cparams, uint32_t key,
                            VbNvContext *vncptr)
{
	int i;

	/* Update key buffer */
	for(i = 1; i < MAGIC_WORD_LEN; i++)
		MagicBuffer[i - 1] = MagicBuffer[i];
	/* Save as lower-case ASCII */
	MagicBuffer[MAGIC_WORD_LEN - 1] = (key | 0x20) & 0xFF;

	if ('\t' == key) {
		/* Tab = display debug info */
		return VbDisplayDebugInfo(cparams, vncptr);
	} else if (VB_KEY_LEFT == key || VB_KEY_RIGHT == key ||
		   VB_KEY_DOWN == key || VB_KEY_UP == key) {
		/* Arrow keys = change localization */
		uint32_t loc = 0;
		uint32_t count = 0;

		VbNvGet(vncptr, VBNV_LOCALIZATION_INDEX, &loc);
		if (VBERROR_SUCCESS != VbGetLocalizationCount(cparams, &count))
			loc = 0;  /* No localization count (bad GBB?) */
		else if (VB_KEY_RIGHT == key || VB_KEY_UP == key)
			loc = (loc < count - 1 ? loc + 1 : 0);
		else
			loc = (loc > 0 ? loc - 1 : count - 1);
		VBDEBUG(("VbCheckDisplayKey() - change localization to %d\n",
			 (int)loc));
		VbNvSet(vncptr, VBNV_LOCALIZATION_INDEX, loc);

#ifdef SAVE_LOCALE_IMMEDIATELY
		VbNvTeardown(vncptr);  /* really only computes checksum */
		if (vncptr->raw_changed)
			VbExNvStorageWrite(vncptr->raw);
#endif

		/* Force redraw of current screen */
		return VbDisplayScreen(cparams, disp_current_screen, 1, vncptr);
	}

	if (0 == Memcmp(MagicBuffer, MAGIC_WORD, MAGIC_WORD_LEN)) {
		if (VBEASTEREGG)
			(void)VbDisplayScreen(cparams, disp_current_screen,
					      1, vncptr);
	}

  return VBERROR_SUCCESS;
}