void dumpTGA(const Common::UString &fileName, const byte *data, int width, int height, PixelFormat format) {
	if ((width <= 0) || (height <= 0) || !data)
		throw Common::Exception("Invalid image data (%dx%d %d)", width, height, data != 0);

	Common::WriteFile file;

	if (!file.open(fileName))
		throw Common::Exception(Common::kOpenError);

	file.writeByte(0); // ID Length
	file.writeByte(0); // Palette size
	file.writeByte(2); // Unmapped RGB
	file.writeUint32LE(0); // Color map
	file.writeByte(0);     // Color map
	file.writeUint16LE(0); // X
	file.writeUint16LE(0); // Y

	file.writeUint16LE(width);
	file.writeUint16LE(height);

	file.writeByte(32); // Pixel depths

	file.writeByte(0);

	uint32 count = width * height;
	for (uint32 i = 0; i < count; i++)
		writePixel(file, data, format);

	file.close();
}