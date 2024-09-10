HICON __fastcall CreateIconFromIndexes(short base, short overlay, short overlay2, short overlay3, short overlay4)
{
	HICON hIcon = NULL;	// returned HICON
	HICON hTmp = NULL;
	HICON icMain = NULL;
	HICON icOverlay = NULL;
	HICON icOverlay2 = NULL;
	HICON icOverlay3 = NULL;
	HICON icOverlay4 = NULL;

	KN_FP_MASK* mainMask = &(def_kn_fp_mask[base]);
	icMain = IcoLib_GetIconByHandle(mainMask->hIcolibItem);

	if (icMain) {
		KN_FP_MASK* overlayMask = (overlay != -1) ? &(def_kn_fp_overlays_mask[overlay]) : NULL;
		KN_FP_MASK* overlay2Mask = (overlay2 != -1) ? &(def_kn_fp_overlays2_mask[overlay2]) : NULL;
		KN_FP_MASK* overlay3Mask = (overlay3 != -1) ? &(def_kn_fp_overlays3_mask[overlay3]) : NULL;
		KN_FP_MASK* overlay4Mask = (overlay4 != -1) ? &(def_kn_fp_overlays4_mask[overlay4]) : NULL;
		icOverlay = (overlayMask == NULL) ? NULL : IcoLib_GetIconByHandle(overlayMask->hIcolibItem);
		icOverlay2 = (overlay2Mask == NULL) ? NULL : IcoLib_GetIconByHandle(overlay2Mask->hIcolibItem);
		icOverlay3 = (overlay3Mask == NULL) ? NULL : IcoLib_GetIconByHandle(overlay3Mask->hIcolibItem);
		icOverlay4 = (overlay4Mask == NULL) ? NULL : IcoLib_GetIconByHandle(overlay4Mask->hIcolibItem);

		hIcon = icMain;

		if (overlayMask)
			hTmp = hIcon = CreateJoinedIcon(hIcon, icOverlay);

		if (overlay2Mask) {
			hIcon = CreateJoinedIcon(hIcon, icOverlay2);
			if (hTmp) DestroyIcon(hTmp);
			hTmp = hIcon;
		}

		if (overlay3Mask) {
			hIcon = CreateJoinedIcon(hIcon, icOverlay3);
			if (hTmp) DestroyIcon(hTmp);
			hTmp = hIcon;
		}

		if (overlay4Mask) {
			hIcon = CreateJoinedIcon(hIcon, icOverlay4);
			if (hTmp) DestroyIcon(hTmp);
		}
	}

	if (hIcon == icMain)
		hIcon = CopyIcon(icMain);

	IcoLib_ReleaseIcon(icMain);
	IcoLib_ReleaseIcon(icOverlay);
	IcoLib_ReleaseIcon(icOverlay2);
	IcoLib_ReleaseIcon(icOverlay3);
	IcoLib_ReleaseIcon(icOverlay4);
	return hIcon;
}