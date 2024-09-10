void VideoReader::init()
{
	// analyse InputFile
	avtranscoder::NoDisplayProgress p;
	_inputFile->analyse( p );
	_streamProperties = &_inputFile->getProperties().getStreamPropertiesWithIndex(_streamIndex);
	_videoStreamProperties = static_cast<const VideoProperties*>(_streamProperties);
	_inputFile->activateStream( _streamIndex );

	// setup decoder
	_decoder = new VideoDecoder( _inputFile->getStream( _streamIndex ) );
	_decoder->setupDecoder();

	// create src frame
	_srcFrame = new VideoFrame( _inputFile->getStream( _streamIndex ).getVideoCodec().getVideoFrameDesc() );
	VideoFrame* srcFrame = static_cast<VideoFrame*>(_srcFrame);
	// create dst frame
	if( _width == 0 )
		_width = srcFrame->desc().getWidth();
	if( _height == 0 )
		_height = srcFrame->desc().getHeight();
	VideoFrameDesc videoFrameDescToDisplay( _width, _height, getPixelFormat() );
	_dstFrame = new VideoFrame( videoFrameDescToDisplay );

	// create transform
	_transform = new VideoTransform();
}