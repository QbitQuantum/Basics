		int   
			STVideoCapture::Initialize
			( 
            HWND hwndParentWindow, // This must be non-null
            STVideoCaptureFormat videoCaptureFormat,
            int capturePeriodMilliseconds,
			STVideoCaptureClient * pSTVideoCaptureClient
			)
		{
			(*this).Clear();




            // Validate capture format
            int captureWidth = 0;
            int captureHeight = 0;
            switch (videoCaptureFormat)
            {
			case BGR320x240: { captureWidth = 320; captureHeight = 240; } break;
            }

            if ((0 == captureWidth) || (0 == captureHeight))
            {
                printf( "Invalid capture format." );
                (*this).Clear();
                return (FALSE);
            }
            (*this).mSTVideoCaptureFormat = videoCaptureFormat;




            // We create a capture window only because we are required to create
            // such a window to use the Video for Windows (VFW32) API.  We make
            // this window tiny to keep it out of the way of our application.
            // For our purposes, this window is simply a necessary interface to
            // VFW functionality.
            (*this).mHWNDCapture =
                capCreateCaptureWindowA
                (
                    "STVideoCapture Window",
                    (WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS), // style
                    0, // x
                    0, // y
                    4, // width
                    4, // height
                    hwndParentWindow, // Parent window : This must be non-null
                    0 // nID
                );



			if (((HWND)(0)) == (*this).mHWNDCapture)
			{ 
                printf( "Failed to create video capture window." );
                DestroyWindow( (*this).mHWNDCapture );
                (*this).Clear();
                return (FALSE);
			}




			(*this).mCapDriverConnectStatus = capDriverConnect( (*this).mHWNDCapture, 0 );

            if (0 == (*this).mCapDriverConnectStatus)
            {
                printf( "Failed to connect to video driver." );
                DestroyWindow( (*this).mHWNDCapture );
                (*this).Clear();
                return (FALSE);
            }



			CAPDRIVERCAPS  capdrivercaps;
			memset( (&(capdrivercaps)),   0,  sizeof(capdrivercaps) );
			capDriverGetCaps( (*this).mHWNDCapture, &(capdrivercaps), sizeof(capdrivercaps) );




			//capDlgVideoFormat( mHWNDCapture );
			//capDlgVideoSource( mHWNDCapture );  // Source; Brightness, Contrast, Saturation, Exposure



            // Allocate a local buffer to store capture data
            int bytesPerPixel = 3;
            switch (videoCaptureFormat)
            {
			case BGR320x240: { bytesPerPixel = 3; } break;
            }
            int totalImageBytes = 0;
            totalImageBytes = (captureHeight * (captureWidth * bytesPerPixel));
            (*this).mBGRData = (unsigned char *) malloc( totalImageBytes );
			memset( (*this).mBGRData,   0,  totalImageBytes );



			// Set the video stream callback function
			(*this).mpSTVideoCaptureClient = pSTVideoCaptureClient;
			capSetCallbackOnFrame( (*this).mHWNDCapture, STVideoCapture::CommonCaptureCallback );


			// Set the preview rate in milliseconds
            (*this).mCapturePeriodMilliseconds = capturePeriodMilliseconds;
            capPreviewRate( (*this).mHWNDCapture, capturePeriodMilliseconds );


			// Disable preview mode
			capPreview( (*this).mHWNDCapture, FALSE );


			// Setup the data we want returned to us
			BITMAPINFO  capbitmapinfo;
			memset( &(capbitmapinfo), 0, sizeof(BITMAPINFO) );
			capbitmapinfo.bmiHeader.biSize           = sizeof(BITMAPINFOHEADER);
			capbitmapinfo.bmiHeader.biWidth          = captureWidth;
			capbitmapinfo.bmiHeader.biHeight         = captureHeight;
			capbitmapinfo.bmiHeader.biPlanes         =  1;
			capbitmapinfo.bmiHeader.biBitCount       = 24;
			capbitmapinfo.bmiHeader.biCompression    = BI_RGB;
			capbitmapinfo.bmiHeader.biSizeImage      = totalImageBytes;
			capbitmapinfo.bmiHeader.biXPelsPerMeter  = 100;
			capbitmapinfo.bmiHeader.biYPelsPerMeter  = 100;

			BOOL setVideoFormatResult = FALSE;
			setVideoFormatResult = capSetVideoFormat( (*this).mHWNDCapture, &(capbitmapinfo), sizeof(BITMAPINFO) );

            if (FALSE == setVideoFormatResult)
            {
                printf( "Failed to set the desired video capture format." );
                capSetCallbackOnFrame( (*this).mHWNDCapture, NULL ); // disable the callback function
                DestroyWindow( (*this).mHWNDCapture );
                (*this).Clear( );
                return (FALSE);
            }


			return( TRUE );
		} 