// Initialize camera input
bool CvCaptureCAM_VFW::open( int wIndex )
{
    char szDeviceName[80];
    char szDeviceVersion[80];
    HWND hWndC = 0;

    close();

    if( (unsigned)wIndex >= 10 )
        wIndex = 0;

    for( ; wIndex < 10; wIndex++ )
    {
        if( capGetDriverDescriptionA( wIndex, szDeviceName,
            sizeof (szDeviceName), szDeviceVersion,
            sizeof (szDeviceVersion)))
        {
            hWndC = capCreateCaptureWindowA ( "My Own Capture Window",
                WS_POPUP | WS_CHILD, 0, 0, 320, 240, 0, 0);
            if( capDriverConnect (hWndC, wIndex))
                break;
            DestroyWindow( hWndC );
            hWndC = 0;
        }
    }

    if( hWndC )
    {
        capWnd = hWndC;
        hdr = 0;
        hic = 0;
        fourcc = (DWORD)-1;

        memset( &caps, 0, sizeof(caps));
        capDriverGetCaps( hWndC, &caps, sizeof(caps));
        CAPSTATUS status = {};
        capGetStatus(hWndC, &status, sizeof(status));
        ::SetWindowPos(hWndC, NULL, 0, 0, status.uiImageWidth, status.uiImageHeight, SWP_NOZORDER|SWP_NOMOVE);
        capSetUserData( hWndC, (size_t)this );
        capSetCallbackOnFrame( hWndC, frameCallback );
        CAPTUREPARMS p;
        capCaptureGetSetup(hWndC,&p,sizeof(CAPTUREPARMS));
        p.dwRequestMicroSecPerFrame = 66667/2; // 30 FPS
        capCaptureSetSetup(hWndC,&p,sizeof(CAPTUREPARMS));
        //capPreview( hWndC, 1 );
        capPreviewScale(hWndC,FALSE);
        capPreviewRate(hWndC,1);

        // Get frame initial parameters.
        const DWORD size = capGetVideoFormatSize(capWnd);
        if( size > 0 )
        {
            unsigned char *pbi = new unsigned char[size];
            if( pbi )
            {
                if( capGetVideoFormat(capWnd, pbi, size) == size )
                {
                    BITMAPINFOHEADER& vfmt = ((BITMAPINFO*)pbi)->bmiHeader;
                    widthSet = vfmt.biWidth;
                    heightSet = vfmt.biHeight;
                    fourcc = vfmt.biCompression;
                }
                delete []pbi;
            }
        }
        // And alternative way in case of failure.
        if( widthSet == 0 || heightSet == 0 )
        {
            widthSet = status.uiImageWidth;
            heightSet = status.uiImageHeight;
        }

    }
    return capWnd != 0;
}