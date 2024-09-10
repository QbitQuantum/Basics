EXPORT_C void CMMFDevVideoPlay::FindDecodersL(const TDesC8& aMimeType, TUint32 aPostProcType, RArray<TUid>& aDecoders, TBool aExactMatch)
	{
#ifdef SYMBIAN_MULTIMEDIA_CODEC_API
	// find PU based plugins
	RImplInfoPtrArray codecPlugins;
	CleanupResetAndDestroyPushL(codecPlugins);
	DevVideoUtilities::FindVideoDecoderPluginsL(aMimeType, codecPlugins);	

	aDecoders.Reset();
	for (TInt i = 0; i < codecPlugins.Count();i++)
		{
		aDecoders.AppendL(codecPlugins[i]->ImplementationUid());
		}
		
	CleanupStack::PopAndDestroy(&codecPlugins);
#endif // SYMBIAN_MULTIMEDIA_CODEC_API
	RImplInfoPtrArray plugins;
	CleanupResetAndDestroyPushL(plugins);

	MmPluginUtils::FindImplementationsL(KUidDevVideoDecoderHwDevice, plugins);

	DevVideoUtilities::SelectPluginBasedOnMatchType(aMimeType, plugins);
		
	DevVideoUtilities::MatchPrePostProcessorCapabilitiesL(plugins, aPostProcType, aDecoders);

	// Perform the extra processing required if an exact match was requested
	if (aExactMatch)
		{
		// We now need to go through each of the plugins returned (which may have been matched using
		// a wildcard), instantiate each one, and perform an exact mime-type match.
		// Any plugins that don't support the desired mime type exactly will be removed from aDecoders.
		CCompressedVideoFormat* format = CCompressedVideoFormat::NewL(aMimeType);
		CleanupStack::PushL(format);

		for (TInt i=aDecoders.Count()-1; i>=0; i--)
			{
			TUid pluginUid = aDecoders[i];
			CVideoDecoderInfo* info = NULL;
			TRAPD(err, info = VideoDecoderInfoLC(pluginUid); CleanupStack::Pop(info););
			if (err == KErrNone)
				{
				if (!info->SupportsFormat(*format))
					{
					// The decoder doesn't support the format, so remove it from the list
					aDecoders.Remove(i);
					}
				delete info;
				}
			else if (err==KErrNotFound)
				{
				// we have a bogus UID so remove it from the list
				aDecoders.Remove(i);
				}
			else
				{
				User::Leave(err);
				}
			}

		CleanupStack::PopAndDestroy(format);
		}