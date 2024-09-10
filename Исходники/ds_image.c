TW_UINT16
_get_gphoto2_file_as_DIB(
    const char *folder, const char *filename, CameraFileType type,
    HWND hwnd, HBITMAP *hDIB
) {
    const unsigned char *filedata;
    unsigned long	filesize;
    int			ret;
    CameraFile		*file;
    struct jpeg_source_mgr		xjsm;
    struct jpeg_decompress_struct	jd;
    struct jpeg_error_mgr		jerr;
    HDC 		dc;
    BITMAPINFO 		bmpInfo;
    LPBYTE		bits, oldbits;
    JSAMPROW		samprow, oldsamprow;

    if(!libjpeg_handle) {
	if(!load_libjpeg()) {
	    FIXME("Failed reading JPEG because unable to find %s\n", SONAME_LIBJPEG);
	    filedata = NULL;
	    return TWRC_FAILURE;
	}
    }

    gp_file_new (&file);
    ret = gp_camera_file_get(activeDS.camera, folder, filename, type, file, activeDS.context);
    if (ret < GP_OK) {
	FIXME("Failed to get file?\n");
	gp_file_unref (file);
	return TWRC_FAILURE;
    }
    ret = gp_file_get_data_and_size (file, (const char**)&filedata, &filesize);
    if (ret < GP_OK) {
	FIXME("Failed to get file data?\n");
	return TWRC_FAILURE;
    }

    /* FIXME: Actually we might get other types than JPEG ... But only handle JPEG for now */
    if (filedata[0] != 0xff) {
	ERR("File %s/%s might not be JPEG, cannot decode!\n", folder, filename);
    }

    /* This is basically so we can use in-memory data for jpeg decompression.
     * We need to have all the functions.
     */
    xjsm.next_input_byte	= filedata;
    xjsm.bytes_in_buffer	= filesize;
    xjsm.init_source	= _jpeg_init_source;
    xjsm.fill_input_buffer	= _jpeg_fill_input_buffer;
    xjsm.skip_input_data	= _jpeg_skip_input_data;
    xjsm.resync_to_restart	= _jpeg_resync_to_restart;
    xjsm.term_source	= _jpeg_term_source;

    jd.err = pjpeg_std_error(&jerr);
    /* jpeg_create_decompress is a macro that expands to jpeg_CreateDecompress - see jpeglib.h
     * jpeg_create_decompress(&jd); */
    pjpeg_CreateDecompress(&jd, JPEG_LIB_VERSION, (size_t) sizeof(struct jpeg_decompress_struct));
    jd.src = &xjsm;
    ret=pjpeg_read_header(&jd,TRUE);
    jd.out_color_space = JCS_RGB;
    pjpeg_start_decompress(&jd);
    if (ret != JPEG_HEADER_OK) {
	ERR("Jpeg image in stream has bad format, read header returned %d.\n",ret);
	gp_file_unref (file);
	return TWRC_FAILURE;
    }

    ZeroMemory (&bmpInfo, sizeof (BITMAPINFO));
    bmpInfo.bmiHeader.biSize = sizeof (BITMAPINFOHEADER);
    bmpInfo.bmiHeader.biWidth = jd.output_width;
    bmpInfo.bmiHeader.biHeight = -jd.output_height;
    bmpInfo.bmiHeader.biPlanes = 1;
    bmpInfo.bmiHeader.biBitCount = jd.output_components*8;
    bmpInfo.bmiHeader.biCompression = BI_RGB;
    bmpInfo.bmiHeader.biSizeImage = 0;
    bmpInfo.bmiHeader.biXPelsPerMeter = 0;
    bmpInfo.bmiHeader.biYPelsPerMeter = 0;
    bmpInfo.bmiHeader.biClrUsed = 0;
    bmpInfo.bmiHeader.biClrImportant = 0;
    *hDIB = CreateDIBSection ((dc = GetDC(hwnd)), &bmpInfo, DIB_RGB_COLORS, (LPVOID)&bits, 0, 0);
    if (!*hDIB) {
	FIXME("Failed creating DIB.\n");
	gp_file_unref (file);
	return TWRC_FAILURE;
    }
    samprow = HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,jd.output_width*jd.output_components);
    oldbits = bits;
    oldsamprow = samprow;
    while ( jd.output_scanline<jd.output_height ) {
	int i, x = pjpeg_read_scanlines(&jd,&samprow,1);
	if (x != 1) {
	    FIXME("failed to read current scanline?\n");
	    break;
	}
	/* We have to convert from RGB to BGR, see MSDN/ BITMAPINFOHEADER */
	for(i=0;i<jd.output_width;i++,samprow+=jd.output_components) {
	    *(bits++) = *(samprow+2);
	    *(bits++) = *(samprow+1);
	    *(bits++) = *(samprow);
	}
	bits = (LPBYTE)(((UINT_PTR)bits + 3) & ~3);
	samprow = oldsamprow;
    }
    if (hwnd) ReleaseDC (hwnd, dc);
    HeapFree (GetProcessHeap(), 0, samprow);
    gp_file_unref (file);
    return TWRC_SUCCESS;
}