void VideoCaptureNode::inputsUpdated( qint64 pTimeStamp )
{
	NodeControlBase::inputsUpdated( pTimeStamp );

//	if( !mNode->context()->active() )
//	{
//		return;
//	}

	if( mDevice && mDevice->timestamp() > mLastFrameTimeStamp )
	{
		fugio::Performance	P( mNode, __FUNCTION__, pTimeStamp );

		fugio::Image				Output = mValOutputImage->variant().value<fugio::Image>();

		for( int i = 0 ; i < 3 ; i++ )
		{
			Output.setBuffer( i, nullptr );
		}

		VideoFrame	VF = mDevice->frame();

		if( VF.width() != mVideoFrame.width() || VF.height() != mVideoFrame.height() || VF.pixelFormat() != mVideoFrame.pixelFormat() )
		{
			Output.setSize( VF.width(), VF.height() );

#if defined( VIDEOCAPTURE_SUPPORTED )
			switch( VF.pixelFormat() )
			{
				case CA_YUV422P:                                                             /* YUV422 Planar */
				case CA_YUVJ420P:                                                          /* YUV420 Planar Full Range (JPEG), J comes from the JPEG. (values 0-255 used) */
				case CA_YUVJ420BP:                                                          /* YUV420 Bi-Planer Full Range (JPEG), J comes fro the JPEG. (values: luma = [16,235], chroma=[16,240]) */
				case CA_JPEG_OPENDML:                                                          /* JPEG with Open-DML extensions */
				case CA_H264:                                                                  /* H264 */
					return;

				case CA_YUV420BP:                                                            /* YUV420 Bi Planar */
					Output.setFormat( fugio::ImageFormat::NV12 );
					break;

				case CA_MJPEG:                                                                /* MJPEG 2*/
					Output.setFormat( fugio::ImageFormat::YUVJ422P );
					break;

				case CA_YUV420P:                                                           /* YUV420 Planar */
					Output.setFormat( fugio::ImageFormat::YUV420P );
					break;

				case CA_UYVY422:                                                              /* Cb Y0 Cr Y1 */
					Output.setFormat( fugio::ImageFormat::UYVY422 );
					break;

				case CA_YUYV422:                                                             /* Y0 Cb Y1 Cr */
					Output.setFormat( fugio::ImageFormat::YUYV422 );
					break;

				case CA_ARGB32:                                                              /* ARGB 8:8:8:8 32bpp, ARGBARGBARGB... */
				case CA_RGBA32:                                                              /* RGBA 8:8:8:8 32bpp. */
					Output.setFormat( fugio::ImageFormat::RGBA8 );
					break;

				case CA_BGRA32:                                                             /* BGRA 8:8:8:8 32bpp, BGRABGRABGRA... */
					Output.setFormat( fugio::ImageFormat::BGRA8 );
					break;

				case CA_RGB24:                                                              /* RGB 8:8:8 24bit */
	#if defined( Q_OS_WIN )
					Output.setFormat( fugio::ImageFormat::BGR8 );
	#else
					Output.setFormat( fugio::ImageFormat::RGB8 );
	#endif
					break;
			}
#endif

			for( int i = 0 ; i < 3 ; i++ )
			{
				Output.setLineSize( i, VF.stride( i ) );
			}
		}

		if( Output.isValid() )
		{
			mVideoFrame = VF;

			for( int i = 0 ; i < 3 ; i++ )
			{
				Output.setBuffer( i, mVideoFrame.plane( i ) );
			}

			pinUpdated( mPinOutputImage );
		}

		mLastFrameTimeStamp = mDevice->timestamp();
	}
}