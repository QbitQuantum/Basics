void Nim::synchronize(Common::Serializer &sz) {
	if (sz.isLoading() && sz.getVersion() < 2)
		return;

	sz.syncAsByte(_playedNim);
}