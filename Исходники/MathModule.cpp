char *Math::decompress(Compressor::Format format, const char *cbytes, size_t compressedsize, size_t &rawsize)
{
	Compressor *compressor = Compressor::getCompressor(format);

	if (compressor == nullptr)
		throw love::Exception("Invalid compression format.");

	return compressor->decompress(format, cbytes, compressedsize, rawsize);
}