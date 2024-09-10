bool FFmpegDecodeServices::VerifyVideoMediaType(IMFMediaType* pMediaType)
{
	GUID subType = GUID_NULL;
	pMediaType->GetGUID(MF_MT_SUBTYPE, &subType);

	UINT32 width = 0, height = 0;
	MFGetAttributeSize(pMediaType, MF_MT_FRAME_SIZE, &width, &height);
	if (width == 0 ||
		height == 0)
		return false;

	if (subType == MFVideoFormat_H264 || subType == MFVideoFormat_HEVC ||
		subType == MFVideoFormat_MPG1 || subType == MFVideoFormat_MPEG2) {
		if ((MFGetAttributeUINT32(pMediaType, MF_MT_MPEG2_PROFILE, 0) == 0 ||
			MFGetAttributeUINT32(pMediaType, MF_MT_MPEG2_LEVEL, 0) == 0) &&
			subType != MFVideoFormat_MPG1)
			return false;

		UINT32 seqSize = 0;
		pMediaType->GetBlobSize(MF_MT_MPEG_SEQUENCE_HEADER, &seqSize);
		if (seqSize == 0)
			return false;
	}
	return true;
}