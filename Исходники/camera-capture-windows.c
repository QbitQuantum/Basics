int
camera_device_start_capturing(CameraDevice* cd,
                              uint32_t pixel_format,
                              int frame_width,
                              int frame_height)
{
    WndCameraDevice* wcd;
    HBITMAP bm_handle;
    BITMAP  bitmap;
    size_t format_info_size;
    CAPTUREPARMS cap_param;

    if (cd == NULL || cd->opaque == NULL) {
        E("%s: Invalid camera device descriptor", __FUNCTION__);
        return -1;
    }
    wcd = (WndCameraDevice*)cd->opaque;

    /* wcd->dc is an indicator of capturing: !NULL - capturing, NULL - not */
    if (wcd->dc != NULL) {
        W("%s: Capturing is already on on device '%s'",
          __FUNCTION__, wcd->window_name);
        return 0;
    }

    /* Connect capture window to the video capture driver. */
    if (!capDriverConnect(wcd->cap_window, wcd->input_channel)) {
        return -1;
    }

    /* Get current frame information from the driver. */
    format_info_size = capGetVideoFormatSize(wcd->cap_window);
    if (format_info_size == 0) {
        E("%s: Unable to get video format size: %d",
          __FUNCTION__, GetLastError());
        _camera_device_reset(wcd);
        return -1;
    }
    wcd->frame_bitmap = (BITMAPINFO*)malloc(format_info_size);
    if (wcd->frame_bitmap == NULL) {
        E("%s: Unable to allocate frame bitmap info buffer", __FUNCTION__);
        _camera_device_reset(wcd);
        return -1;
    }
    if (!capGetVideoFormat(wcd->cap_window, wcd->frame_bitmap,
                           format_info_size)) {
        E("%s: Unable to obtain video format: %d", __FUNCTION__, GetLastError());
        _camera_device_reset(wcd);
        return -1;
    }

    /* Lets see if we need to set different frame dimensions */
    if (wcd->frame_bitmap->bmiHeader.biWidth != frame_width ||
            abs(wcd->frame_bitmap->bmiHeader.biHeight) != frame_height) {
        /* Dimensions don't match. Set new frame info. */
        wcd->frame_bitmap->bmiHeader.biWidth = frame_width;
        wcd->frame_bitmap->bmiHeader.biHeight = frame_height;
        /* We need to recalculate image size, since the capture window / driver
         * will use image size provided by us. */
        if (wcd->frame_bitmap->bmiHeader.biBitCount == 24) {
            /* Special case that may require WORD boundary alignment. */
            uint32_t bpl = (frame_width * 3 + 1) & ~1;
            wcd->frame_bitmap->bmiHeader.biSizeImage = bpl * frame_height;
        } else {
            wcd->frame_bitmap->bmiHeader.biSizeImage =
                (frame_width * frame_height * wcd->frame_bitmap->bmiHeader.biBitCount) / 8;
        }
        if (!capSetVideoFormat(wcd->cap_window, wcd->frame_bitmap,
                               format_info_size)) {
            E("%s: Unable to set video format: %d", __FUNCTION__, GetLastError());
            _camera_device_reset(wcd);
            return -1;
        }
    }

    if (wcd->frame_bitmap->bmiHeader.biCompression > BI_PNG) {
        D("%s: Video capturing driver has reported pixel format %.4s",
          __FUNCTION__, (const char*)&wcd->frame_bitmap->bmiHeader.biCompression);
    }

    /* Most of the time frame bitmaps come in "bottom-up" form, where its origin
     * is the lower-left corner. However, it could be in the normal "top-down"
     * form with the origin in the upper-left corner. So, we must adjust the
     * biHeight field, since the way "top-down" form is reported here is by
     * setting biHeight to a negative value. */
    if (wcd->frame_bitmap->bmiHeader.biHeight < 0) {
        wcd->frame_bitmap->bmiHeader.biHeight =
            -wcd->frame_bitmap->bmiHeader.biHeight;
        wcd->is_top_down = 1;
    } else {
        wcd->is_top_down = 0;
    }

    /* Get DC for the capturing window that will be used when we deal with
     * bitmaps obtained from the camera device during frame capturing. */
    wcd->dc = GetDC(wcd->cap_window);
    if (wcd->dc == NULL) {
        E("%s: Unable to obtain DC for %s: %d",
          __FUNCTION__, wcd->window_name, GetLastError());
        _camera_device_reset(wcd);
        return -1;
    }

    /* Setup some capture parameters. */
    if (capCaptureGetSetup(wcd->cap_window, &cap_param, sizeof(cap_param))) {
        /* Use separate thread to capture video stream. */
        cap_param.fYield = TRUE;
        /* Don't show any dialogs. */
        cap_param.fMakeUserHitOKToCapture = FALSE;
        capCaptureSetSetup(wcd->cap_window, &cap_param, sizeof(cap_param));
    }

    /*
     * At this point we need to grab a frame to properly setup framebuffer, and
     * calculate pixel format. The problem is that bitmap information obtained
     * from the driver doesn't necessarily match the actual bitmap we're going to
     * obtain via capGrabFrame / capEditCopy / GetClipboardData
     */

    /* Grab a frame, and post it to the clipboard. Not very effective, but this
     * is how capXxx API is operating. */
    if (!capGrabFrameNoStop(wcd->cap_window) ||
        !capEditCopy(wcd->cap_window) ||
        !OpenClipboard(wcd->cap_window)) {
        E("%s: Device '%s' is unable to save frame to the clipboard: %d",
          __FUNCTION__, wcd->window_name, GetLastError());
        _camera_device_reset(wcd);
        return -1;
    }

    /* Get bitmap handle saved into clipboard. Note that bitmap is still
     * owned by the clipboard here! */
    bm_handle = (HBITMAP)GetClipboardData(CF_BITMAP);
    if (bm_handle == NULL) {
        E("%s: Device '%s' is unable to obtain frame from the clipboard: %d",
          __FUNCTION__, wcd->window_name, GetLastError());
        CloseClipboard();
        _camera_device_reset(wcd);
        return -1;
    }

    /* Get bitmap object that is initialized with the actual bitmap info. */
    if (!GetObject(bm_handle, sizeof(BITMAP), &bitmap)) {
        E("%s: Device '%s' is unable to obtain frame's bitmap: %d",
          __FUNCTION__, wcd->window_name, GetLastError());
        EmptyClipboard();
        CloseClipboard();
        _camera_device_reset(wcd);
        return -1;
    }

    /* Now that we have all we need in 'bitmap' */
    EmptyClipboard();
    CloseClipboard();

    /* Make sure that dimensions match. Othewise - fail. */
    if (wcd->frame_bitmap->bmiHeader.biWidth != bitmap.bmWidth ||
        wcd->frame_bitmap->bmiHeader.biHeight != bitmap.bmHeight ) {
        E("%s: Requested dimensions %dx%d do not match the actual %dx%d",
          __FUNCTION__, frame_width, frame_height,
          wcd->frame_bitmap->bmiHeader.biWidth,
          wcd->frame_bitmap->bmiHeader.biHeight);
        _camera_device_reset(wcd);
        return -1;
    }

    /* Create bitmap info that will be used with GetDIBits. */
    wcd->gdi_bitmap = (BITMAPINFO*)malloc(wcd->frame_bitmap->bmiHeader.biSize);
    if (wcd->gdi_bitmap == NULL) {
        E("%s: Unable to allocate gdi bitmap info", __FUNCTION__);
        _camera_device_reset(wcd);
        return -1;
    }
    memcpy(wcd->gdi_bitmap, wcd->frame_bitmap,
           wcd->frame_bitmap->bmiHeader.biSize);
    wcd->gdi_bitmap->bmiHeader.biCompression = BI_RGB;
    wcd->gdi_bitmap->bmiHeader.biBitCount = bitmap.bmBitsPixel;
    wcd->gdi_bitmap->bmiHeader.biSizeImage = bitmap.bmWidthBytes * bitmap.bmWidth;
    /* Adjust GDI's bitmap biHeight for proper frame direction ("top-down", or
     * "bottom-up") We do this trick in order to simplify pixel format conversion
     * routines, where we always assume "top-down" frames. The trick he is to
     * have negative biHeight in 'gdi_bitmap' if driver provides "bottom-up"
     * frames, and positive biHeight in 'gdi_bitmap' if driver provides "top-down"
     * frames. This way GetGDIBits will always return "top-down" frames. */
    if (wcd->is_top_down) {
        wcd->gdi_bitmap->bmiHeader.biHeight =
            wcd->frame_bitmap->bmiHeader.biHeight;
    } else {
        wcd->gdi_bitmap->bmiHeader.biHeight =
            -wcd->frame_bitmap->bmiHeader.biHeight;
    }

    /* Allocate framebuffer. */
    wcd->framebuffer = (uint8_t*)malloc(wcd->gdi_bitmap->bmiHeader.biSizeImage);
    if (wcd->framebuffer == NULL) {
        E("%s: Unable to allocate %d bytes for framebuffer",
          __FUNCTION__, wcd->gdi_bitmap->bmiHeader.biSizeImage);
        _camera_device_reset(wcd);
        return -1;
    }

    /* Lets see what pixel format we will use. */
    if (wcd->gdi_bitmap->bmiHeader.biBitCount == 16) {
        wcd->pixel_format = V4L2_PIX_FMT_RGB565;
    } else if (wcd->gdi_bitmap->bmiHeader.biBitCount == 24) {
        wcd->pixel_format = V4L2_PIX_FMT_BGR24;
    } else if (wcd->gdi_bitmap->bmiHeader.biBitCount == 32) {
        wcd->pixel_format = V4L2_PIX_FMT_BGR32;
    } else {
        E("%s: Unsupported number of bits per pixel %d",
          __FUNCTION__, wcd->gdi_bitmap->bmiHeader.biBitCount);
        _camera_device_reset(wcd);
        return -1;
    }

    D("%s: Capturing device '%s': %d bits per pixel in %.4s [%dx%d] frame",
      __FUNCTION__, wcd->window_name, wcd->gdi_bitmap->bmiHeader.biBitCount,
      (const char*)&wcd->pixel_format, wcd->frame_bitmap->bmiHeader.biWidth,
      wcd->frame_bitmap->bmiHeader.biHeight);

    /* Try to setup capture frame callback. */
    wcd->use_clipboard = 1;
    if (capSetCallbackOnFrame(wcd->cap_window, _on_captured_frame)) {
        /* Callback is set. Don't use clipboard when capturing frames. */
        wcd->use_clipboard = 0;
    }

    return 0;
}