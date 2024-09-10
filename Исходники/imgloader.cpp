bool ImgLoader::decodeThumbnailImage(const byte *pFileData, uint fileSize, byte *&pUncompressedData, int &width, int &height, int &pitch) {
	const byte *src = pFileData + 4;	// skip header
	width = READ_LE_UINT16(src); src += 2;
	height = READ_LE_UINT16(src); src += 2;
	src++;	// version, ignored for now
	pitch = width * 4;

	uint32 totalSize = pitch * height;
	pUncompressedData = new byte[totalSize];
	uint32 *dst = (uint32 *)pUncompressedData;	// treat as uint32, for pixelformat output
	const Graphics::PixelFormat format = Graphics::PixelFormat(4, 8, 8, 8, 8, 16, 8, 0, 24);
	byte r, g, b;

	for (uint32 i = 0; i < totalSize / 4; i++) {
		r = *src++;
		g = *src++;
		b = *src++;
		*dst++ = format.RGBToColor(r, g, b);
	}

	return true;
}