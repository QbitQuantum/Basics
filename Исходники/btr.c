BOOL
BtrOnProcessDetach(
	VOID
	)
{
	InterlockedExchange(&BtrUnloading, TRUE);

	if (FlagOn(BtrFeatures, FeatureLibrary)) {
		return TRUE;
	}

	if (FlagOn(BtrFeatures, FeatureLocal|FeatureRemote)) {
		if (BtrTlsIndex != TLS_OUT_OF_INDEXES) {
			TlsFree(BtrTlsIndex);
		}
	}
	return TRUE;
}