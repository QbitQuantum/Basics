HRESULT MediaInfo::InternalInitVideo(IMFMediaType* mediaType, StreamInfo& info)
{
	MFGetAttributeSize(mediaType, MF_MT_FRAME_SIZE, &info.video.width, &info.video.height);
	MFGetAttributeRatio(mediaType, MF_MT_PIXEL_ASPECT_RATIO, &info.video.pixelAR0, &info.video.pixelAR1);

	UINT32 fps_den = 0, fps_num = 0;
	MFGetAttributeRatio(mediaType, MF_MT_FRAME_RATE, &fps_num, &fps_den);
	info.video.frameRate = float(fps_num) / float(fps_den);
	info.video.fps_den = fps_den;
	info.video.fps_num = fps_num;

	info.video.profile = MFGetAttributeUINT32(mediaType, MF_MT_MPEG2_PROFILE, 0);
	info.video.profileLevel = MFGetAttributeUINT32(mediaType, MF_MT_MPEG2_LEVEL, 0);
	return S_OK;
}