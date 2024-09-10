/*
EW: This is part of the fix for seeking because calling SetCurrentPosition was failing.
It is now split up to set a flag that seeking needs to be done,
and we call this at a time that seems to work (in the read).
*/ 
static void Internal_DoSeek(Sound_Sample* sample)
{
	Sound_SampleInternal *internal = (Sound_SampleInternal *) sample->opaque;
	MediaFoundationFileContainer* media_foundation_file_container = (MediaFoundationFileContainer*)internal->decoder_private;
	__int64 mf_seek_target = media_foundation_file_container->seekTargetPosition;
	PROPVARIANT prop_variant;
	HRESULT hr = S_OK;

	// this doesn't fail, see MS's implementation
	hr = InitPropVariantFromInt64(mf_seek_target, &prop_variant);

	// http://msdn.microsoft.com/en-us/library/dd374668(v=VS.85).aspx
	hr = media_foundation_file_container->sourceReader->SetCurrentPosition(GUID_NULL, prop_variant);
	if(FAILED(hr))
	{
		// nothing we can do here as we can't fail (no facility to other than
		// crashing mixxx)
	//		sample->flags |= SOUND_SAMPLEFLAG_ERROR;
		// more C++ BS
		sample->flags = (SoundDecoder_SampleFlags)(sample->flags | SOUND_SAMPLEFLAG_ERROR);
		if (hr == MF_E_INVALIDREQUEST)
		{
			SNDERR("WindowsMediaFoundation failed to seek: Sample requests still pending\n");
		}
		else
		{
			SNDERR("WindowsMediaFoundation failed to seek\n");
		}
	}

	PropVariantClear(&prop_variant);
}