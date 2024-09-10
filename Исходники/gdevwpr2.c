/* Open the win_pr2 driver */
static int
win_pr2_open(gx_device * dev)
{
    int code;
    int depth;
    PRINTDLG pd;
    POINT offset;
    POINT size;
    float m[4];
    FILE *pfile;
    DOCINFO docinfo;
    float ratio = 1.0;
    
    win_pr2_copy_check(wdev);

    /* get a HDC for the printer */
    if ((wdev->win32_hdevmode) &&
	(wdev->win32_hdevnames)) {
	/* The user has already had the opportunity to choose the output */
	/* file interactively. Just use the specified parameters. */
	
	LPDEVMODE devmode = (LPDEVMODE) GlobalLock(wdev->win32_hdevmode);
	LPDEVNAMES devnames = (LPDEVNAMES) GlobalLock(wdev->win32_hdevnames);
	
	const char* driver = (char*)(devnames)+(devnames->wDriverOffset);
	const char* device = (char*)(devnames)+(devnames->wDeviceOffset);
	const char* output = (char*)(devnames)+(devnames->wOutputOffset);
	
	wdev->hdcprn = CreateDC(driver, device, output, devmode);
	
	GlobalUnlock(wdev->win32_hdevmode);
	GlobalUnlock(wdev->win32_hdevnames);
	
	if (wdev->hdcprn == NULL) {
	    return gs_error_Fatal;
	}
	
    } else if (!win_pr2_getdc(wdev)) {
	/* couldn't get a printer from -sOutputFile= */
	/* Prompt with dialog box */
	
	LPDEVMODE devmode = NULL;
	memset(&pd, 0, sizeof(pd));
	
	pd.lStructSize = sizeof(pd);
	pd.hwndOwner = PARENT_WINDOW;
	pd.Flags = PD_RETURNDC;
	pd.nMinPage = wdev->doc_page_begin;
	pd.nMaxPage = wdev->doc_page_end;
	pd.nFromPage = wdev->user_page_begin;
	pd.nToPage = wdev->user_page_end;
	pd.nCopies = wdev->user_copies;
	
	if (!PrintDlg(&pd)) {
	    /* device not opened - exit ghostscript */
	    return gs_error_Fatal;	/* exit Ghostscript cleanly */
	}
	
	devmode = GlobalLock(pd.hDevMode);
	win_pr2_update_dev(wdev,devmode);
	GlobalUnlock(pd.hDevMode);
	
	if (wdev->win32_hdevmode)
	    GlobalFree(wdev->win32_hdevmode);
	if (wdev->win32_hdevnames)
	    GlobalFree(wdev->win32_hdevnames);
	
	wdev->hdcprn = pd.hDC;
	wdev->win32_hdevmode = pd.hDevMode;
	wdev->win32_hdevnames = pd.hDevNames;
	
	pd.hDevMode = NULL;
	pd.hDevNames = NULL;
    }
    if (!(GetDeviceCaps(wdev->hdcprn, RASTERCAPS) != RC_DIBTODEV)) {
	errprintf(dev->memory, "Windows printer does not have RC_DIBTODEV\n");
	DeleteDC(wdev->hdcprn);
	return gs_error_limitcheck;
    }
    /* initialise printer, install abort proc */
    wdev->lpfnAbortProc = (DLGPROC) AbortProc2;
    SetAbortProc(wdev->hdcprn, (ABORTPROC) wdev->lpfnAbortProc);

    /*
     * Some versions of the Windows headers include lpszDatatype and fwType,
     * and some don't.  Since we want to set these fields to zero anyway,
     * we just start by zeroing the whole structure.
     */
    memset(&docinfo, 0, sizeof(docinfo));
    docinfo.cbSize = sizeof(docinfo);
    docinfo.lpszDocName = wdev->doc_name;
    /*docinfo.lpszOutput = NULL;*/
    /*docinfo.lpszDatatype = NULL;*/
    /*docinfo.fwType = 0;*/

    if (docinfo.lpszDocName[0] == 0) {
	docinfo.lpszDocName = "Ghostscript output";
    }

    if (StartDoc(wdev->hdcprn, &docinfo) <= 0) {
	errprintf(dev->memory,
                  "Printer StartDoc failed (error %08x)\n", GetLastError());
	DeleteDC(wdev->hdcprn);
	return gs_error_limitcheck;
    }
    
    dev->x_pixels_per_inch = (float)GetDeviceCaps(wdev->hdcprn, LOGPIXELSX);
    dev->y_pixels_per_inch = (float)GetDeviceCaps(wdev->hdcprn, LOGPIXELSY);
    
    wdev->ratio = 1;
    
    if (wdev->max_dpi > 50) {
	
	float dpi_x = dev->x_pixels_per_inch;
	float dpi_y = dev->y_pixels_per_inch;
	
	while ((dev->x_pixels_per_inch > wdev->max_dpi)
	    || (dev->y_pixels_per_inch > wdev->max_dpi)) {
	    ratio += 1.0;
	    wdev->ratio ++;
	    dev->x_pixels_per_inch = dpi_x / ratio;
	    dev->y_pixels_per_inch = dpi_y / ratio;
	}
    }
    
    size.x = GetDeviceCaps(wdev->hdcprn, PHYSICALWIDTH);
    size.y = GetDeviceCaps(wdev->hdcprn, PHYSICALHEIGHT);
    gx_device_set_width_height(dev, (int)(size.x / ratio), (int)(size.y / ratio));
    offset.x = GetDeviceCaps(wdev->hdcprn, PHYSICALOFFSETX);
    offset.y = GetDeviceCaps(wdev->hdcprn, PHYSICALOFFSETY);
    
    /* m[] gives margins in inches */
    m[0] /*left   */ = offset.x / dev->x_pixels_per_inch / ratio;
    m[3] /*top    */ = offset.y / dev->y_pixels_per_inch / ratio;
    m[2] /*right  */ = (size.x - offset.x - GetDeviceCaps(wdev->hdcprn, HORZRES)) / dev->x_pixels_per_inch / ratio;
    m[1] /*bottom */ = (size.y - offset.y - GetDeviceCaps(wdev->hdcprn, VERTRES)) / dev->y_pixels_per_inch / ratio;
    gx_device_set_margins(dev, m, true);
    
    depth = dev->color_info.depth;
    if (depth == 0) {
	/* Set parameters that were unknown before opening device */
	/* Find out if the device supports color */
	/* We recognize 1, 4 (but use only 3), 8 and 24 bit color devices */
	depth = GetDeviceCaps(wdev->hdcprn, PLANES) * GetDeviceCaps(wdev->hdcprn, BITSPIXEL);
    }
    win_pr2_set_bpp(dev, depth);

    /* gdev_prn_open opens a temporary file which we don't want */
    /* so we specify the name now so we can delete it later */
    wdev->fname[0] = '\0';
    pfile = gp_open_scratch_file(dev->memory,
                                 gp_scratch_file_name_prefix,
				 wdev->fname, "wb");
    fclose(pfile);
    code = gdev_prn_open(dev);
    if ((code < 0) && wdev->fname[0])
        unlink(wdev->fname);

    if (!wdev->nocancel) {
	/* inform user of progress with dialog box and allow cancel */
	wdev->lpfnCancelProc = (DLGPROC) CancelDlgProc;
	wdev->hDlgModeless = CreateDialog(phInstance, "CancelDlgBox",
				    PARENT_WINDOW, wdev->lpfnCancelProc);
	ShowWindow(wdev->hDlgModeless, SW_HIDE);
    }
    return code;
};