bool MediaConverter::imgs2media(LPRImage *pRawImages[], size_t imgCount, EventMedia &eventMedia)
{
	if (imgCount == 0)
	{
		printf("Input is empty.\n");
		return true;
	}
	//////////////////////////////////////////////////////////////////////////
	if(!initialize(pRawImages[0], "temp.avi"))
	{
		printf("Failed to initialize.\n");
		return false;
	}
	//////////////////////////////////////////////////////////////////////////
	if (!(mOutputFormatCtxPtr->flags & AVFMT_NOFILE))
	{
		/*if (avio_open(&mOutputFormatCtxPtr->pb, mediaName.c_str(), AVIO_FLAG_WRITE) < 0)
		{
		printf("Could not open %s.\n", mediaName.c_str());
		return false;
		}*/
		if (avio_open_dyn_buf(&mOutputFormatCtxPtr->pb) < 0)
		{
			printf("Could not open avio buff.\n");
			return false;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	// Output
	avformat_write_header(mOutputFormatCtxPtr, NULL);
	for (size_t i = 0; i < imgCount; ++ i)
		outputFrame(pRawImages[i]);
	flushFrames();
	av_write_trailer(mOutputFormatCtxPtr);
	//////////////////////////////////////////////////////////////////////////
	if (!(mOutputFormatCtxPtr->flags & AVFMT_NOFILE))
	{
		//avio_close(mOutputFormatCtxPtr->pb);
		eventMedia.mBufferSize = avio_close_dyn_buf(mOutputFormatCtxPtr->pb, &eventMedia.mBufferPtr);
	}
	//////////////////////////////////////////////////////////////////////////
	// 清理环境
	uninitialize();

	return true;
}