void CachingPyramidFeatureExtractor::update(shared_ptr<VersionedImage> image) {
	extractor->update(image);
	if (version != image->getVersion()) {
		buildCache();
		version = image->getVersion();
	}
}