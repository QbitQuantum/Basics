bool myVideoPlayer::presentImage(const QImage &image)
{
	QVideoFrame frame(image);

	if (!frame.isValid())
		return false;

	QVideoSurfaceFormat currentFormat = surface->surfaceFormat();

	if (frame.pixelFormat() != currentFormat.pixelFormat()
		|| frame.size() != currentFormat.frameSize()) 
	{
		QVideoSurfaceFormat format(frame.size(), frame.pixelFormat());

		if (!surface->start(format))
			return false;
	}

	if (!surface->present(frame)) 
	{
		surface->stop();

		return false;
	} 
	else
	{
		return true;
	}
}