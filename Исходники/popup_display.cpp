void POPUP_DISPLAY::update()
{
	// once per 40 milliseconds update popup windows alpha
	if (clock() > nextUpdateTime)
	{
		nextUpdateTime = clock() + DISPLAY_UPDATE_TICK;
		if (branches.isSafeToShowBranchesData() && bookmarks.itemUnderMouse >= 0 && bookmarks.itemUnderMouse < TOTAL_BOOKMARKS && bookmarks.bookmarksArray[bookmarks.itemUnderMouse].notEmpty)
		{
			if (taseditorConfig.displayBranchScreenshots && !hwndScreenshotBitmap)
			{
				// create window
				hwndScreenshotBitmap = CreateWindowEx(WS_EX_LAYERED | WS_EX_TRANSPARENT, szClassName, szClassName, WS_POPUP, taseditorConfig.windowX + screenshotBitmapX, taseditorConfig.windowY + screenshotBitmapY, SCREENSHOT_WIDTH, SCREENSHOT_HEIGHT, taseditorWindow.hwndTASEditor, NULL, fceu_hInstance, NULL);
				redrawScreenshotBitmap();
				ShowWindow(hwndScreenshotBitmap, SW_SHOWNA);
			}
			if (taseditorConfig.displayBranchDescriptions && !hwndNoteDescription)
			{
				RECT wrect;
				GetWindowRect(playback.hwndPlaybackMarkerEditField, &wrect);
				descriptionX = screenshotBitmapX + (SCREENSHOT_WIDTH - (wrect.right - wrect.left)) / 2;
				hwndNoteDescription = CreateWindowEx(WS_EX_LAYERED | WS_EX_TRANSPARENT, szClassName2, szClassName2, WS_POPUP, taseditorConfig.windowX + descriptionX, taseditorConfig.windowY + descriptionY, wrect.right - wrect.left, wrect.bottom - wrect.top, taseditorWindow.hwndTASEditor, NULL, fceu_hInstance, NULL);
				changeDescriptionText();
				ShowWindow(hwndNoteDescription, SW_SHOWNA);
			}
			// change screenshot_bitmap pic and description text if needed
			if (currentlyDisplayedBookmark != bookmarks.itemUnderMouse)
			{
				if (taseditorConfig.displayBranchScreenshots)
					changeScreenshotBitmap();
				if (taseditorConfig.displayBranchDescriptions)
					changeDescriptionText();
				currentlyDisplayedBookmark = bookmarks.itemUnderMouse;
			}
			if (screenshotBitmapPhase < SCREENSHOT_BITMAP_PHASE_MAX)
			{
				screenshotBitmapPhase++;
				// update alpha
				int phase_alpha = screenshotBitmapPhase;
				if (phase_alpha > SCREENSHOT_BITMAP_PHASE_ALPHA_MAX) phase_alpha = SCREENSHOT_BITMAP_PHASE_ALPHA_MAX;
				if (hwndScreenshotBitmap)
				{
					SetLayeredWindowAttributes(hwndScreenshotBitmap, 0, (255 * phase_alpha) / SCREENSHOT_BITMAP_PHASE_ALPHA_MAX, LWA_ALPHA);
					UpdateLayeredWindow(hwndScreenshotBitmap, 0, 0, 0, 0, 0, 0, &blend, ULW_ALPHA);
				}
				if (hwndNoteDescription)
				{
					SetLayeredWindowAttributes(hwndNoteDescription, 0, (255 * phase_alpha) / SCREENSHOT_BITMAP_PHASE_ALPHA_MAX, LWA_ALPHA);
					UpdateLayeredWindow(hwndNoteDescription, 0, 0, 0, 0, 0, 0, &blend, ULW_ALPHA);
				}
			}
		} else
		{
			// fade and finally hide screenshot
			if (screenshotBitmapPhase > 0)
				screenshotBitmapPhase--;
			if (screenshotBitmapPhase > 0)
			{
				// update alpha
				int phase_alpha = screenshotBitmapPhase;
				if (phase_alpha > SCREENSHOT_BITMAP_PHASE_ALPHA_MAX)
					phase_alpha = SCREENSHOT_BITMAP_PHASE_ALPHA_MAX;
				else if (phase_alpha < 0)
					phase_alpha = 0;
				if (hwndScreenshotBitmap)
				{
					SetLayeredWindowAttributes(hwndScreenshotBitmap, 0, (255 * phase_alpha) / SCREENSHOT_BITMAP_PHASE_ALPHA_MAX, LWA_ALPHA);
					UpdateLayeredWindow(hwndScreenshotBitmap, 0, 0, 0, 0, 0, 0, &blend, ULW_ALPHA);
				}
				if (hwndNoteDescription)
				{
					SetLayeredWindowAttributes(hwndNoteDescription, 0, (255 * phase_alpha) / SCREENSHOT_BITMAP_PHASE_ALPHA_MAX, LWA_ALPHA);
					UpdateLayeredWindow(hwndNoteDescription, 0, 0, 0, 0, 0, 0, &blend, ULW_ALPHA);
				}
			} else
			{
				// destroy popup windows
				screenshotBitmapPhase = 0;
				if (hwndScreenshotBitmap)
				{
					DestroyWindow(hwndScreenshotBitmap);
					hwndScreenshotBitmap = 0;
				}
				if (hwndNoteDescription)
				{
					DestroyWindow(hwndNoteDescription);
					hwndNoteDescription = 0;
				}
				// immediately redraw the window below those
				UpdateWindow(taseditorWindow.hwndTASEditor);
			}
		}
	}
}