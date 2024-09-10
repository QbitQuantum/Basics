Texture1d::Texture1d(Renderer& renderer, const Image& image) {
	Configuration config;
	config.width = image.size().first;
	config.arraySize = image.arraySize();
	config.mipLevels = image.mipLevels();
	config.pixelFormat = image.pixelFormat();
	config.allowModifications = false;
	config.allowCPURead = false;
	config.allowGPUWrite = false;
	config.purposeFlags = CreationPurpose::SHADER_RESOURCE;
	config.initialData = image.pixels();

	initialise(renderer, config);
}