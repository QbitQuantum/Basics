unsigned int Decompressor::Private::getHeader(void* buffer, const unsigned int bufferSize, const InputOptions::Private & inputOptions, const CompressionOptions::Private & compressionOptions)
{
	if( bufferSize < DECOMPRESSOR_MIN_HEADER_SIZE )
	{
		return 0;
	}

	DDSHeader header;

	inputOptions.computeTargetExtents();

	header.setWidth(inputOptions.targetWidth);
	header.setHeight(inputOptions.targetHeight);

	int mipmapCount = inputOptions.realMipmapCount();
	nvDebugCheck(mipmapCount > 0);

	header.setMipmapCount(mipmapCount);

	if (inputOptions.textureType == TextureType_2D) {
		header.setTexture2D();
	}
	else if (inputOptions.textureType == TextureType_Cube) {
		header.setTextureCube();
	}		

	uint p = inputOptions.targetWidth * ((compressionOptions.bitcount + 7) / 8);
		// Align to 32 bits.
	uint pitch = ((p + 3) / 4) * 4;

	if (compressionOptions.format == Format_RGBA)
	{
		
		header.setPitch(pitch);
		header.setPixelFormat(compressionOptions.bitcount, compressionOptions.rmask, compressionOptions.gmask, compressionOptions.bmask, compressionOptions.amask);
	}
	else
	{
		
		uint lineralSize = 0;
		if (compressionOptions.format == Format_RGBA)
		{
			lineralSize = inputOptions.targetDepth * inputOptions.targetHeight * pitch;
		}
		else 
		{
			uint blockSize = 0;
			if (compressionOptions.format == Format_DXT1 || compressionOptions.format == Format_DXT1a || compressionOptions.format == Format_BC4) 
			{
				blockSize = 8;
			}
			else 
			{
				blockSize = 16;
			}
			

			lineralSize = ((inputOptions.targetWidth + 3) / 4) * ((inputOptions.targetHeight + 3) / 4) * blockSize;
		}

		header.setLinearSize(lineralSize);

		if (compressionOptions.format == Format_DXT1 || compressionOptions.format == Format_DXT1a) {
			header.setFourCC('D', 'X', 'T', '1');
			if (inputOptions.isNormalMap) header.setNormalFlag(true);
		}
		else if (compressionOptions.format == Format_DXT3) {
			header.setFourCC('D', 'X', 'T', '3');
		}
		else if (compressionOptions.format == Format_DXT5) {
			header.setFourCC('D', 'X', 'T', '5');
		}
		else if (compressionOptions.format == Format_DXT5n) {
			header.setFourCC('D', 'X', 'T', '5');
			if (inputOptions.isNormalMap) header.setNormalFlag(true);
		}
		else if (compressionOptions.format == Format_BC4) {
			header.setFourCC('A', 'T', 'I', '1');
		}
		else if (compressionOptions.format == Format_BC5) {
			header.setFourCC('A', 'T', 'I', '2');
			if (inputOptions.isNormalMap) header.setNormalFlag(true);
		}
		else if (compressionOptions.format == Format_ATC_RGB) {
			header.setFourCC('A', 'T', 'C', ' ');
		}
		else if (compressionOptions.format == Format_ATC_RGBA_EXPLICIT_ALPHA) {
			header.setFourCC('A', 'T', 'C', 'I');
		}
		else if (compressionOptions.format == Format_ATC_RGBA_INTERPOLATED_ALPHA) {
			header.setFourCC('A', 'T', 'C', 'A');
		}
	}

	// Swap bytes if necessary.
	header.swapBytes();

	uint headerSize = 128;
	if (header.hasDX10Header())
	{
		nvStaticCheck(sizeof(DDSHeader) == 128 + 20);
		headerSize = 128 + 20;
	}

	
	memcpy( buffer, &header, headerSize);
	return headerSize;
}