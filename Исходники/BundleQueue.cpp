void BundleQueue::addBundle(BundlePtr& aBundle) noexcept {
	bundles[aBundle->getToken()] = aBundle;

	if (aBundle->filesCompleted()) {
		aBundle->setStatus(Bundle::STATUS_COMPLETED);
		return;
	}

	aBundle->setStatus(Bundle::STATUS_QUEUED);
	aBundle->setDownloadedBytes(0); //sets to downloaded segments

	addSearchPrio(aBundle);
}