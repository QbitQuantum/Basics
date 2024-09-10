IImage* CImageLoaderWAL::loadImage(irr::io::IReadFile* file) const
{
	// Try to get the color palette from elsewhere (usually in a pak along with the WAL).
	// If this fails we use the DefaultPaletteQ2.
	static s32 * palette = 0;
#if TRY_LOADING_PALETTE_FROM_FILE
	s32 loadedPalette[256];
#endif
	if (!palette)
	{
#if TRY_LOADING_PALETTE_FROM_FILE
		IImage * paletteImage;
		// Look in a couple different places...
		paletteImage = createImageFromFile("pics/colormap.pcx");
		if (!paletteImage)
			paletteImage = createImageFromFile("pics/colormap.tga");
		if (!paletteImage)
			paletteImage = createImageFromFile("colormap.pcx");
		if (!paletteImage)
			paletteImage = createImageFromFile("colormap.tga");
		if (paletteImage && (paletteImage->getDimension().Width == 256) ) {
			palette = &loadedPalette;
			for (u32 i = 0; i < 256; ++i) {
				palette[i] = paletteImage->getPixel(i, 0).color;
			}
		} else {
			//FIXME: try reading a simple palette from "wal.pal"
			palette = DefaultPaletteQ2;
		}
		if (paletteImage)
			paletteImage->drop();
#endif
	}
	else
	{
		palette = DefaultPaletteQ2;
	}

	SWALHeader header;

	file->seek(0);
	if (file->read(&header, sizeof(SWALHeader)) != sizeof(SWALHeader) )
		return 0;

	if (file->getSize() < header.MipmapOffset[0])
		return 0;
	file->seek(header.MipmapOffset[0]);

	// read image

	const u32 imageSize = header.ImageHeight * header.ImageWidth;
	if (file->getSize() < (long)(imageSize + header.MipmapOffset[0]))
		return 0;

	u8* data = new u8[imageSize];
	file->read(data, imageSize);

	IImage* image = 0;

	image = new CImage(ECF_A1R5G5B5,
		core::dimension2d<u32>(header.ImageWidth, header.ImageHeight));

	// I wrote an 8 to 32 converter, but this works with released Irrlicht code.
	CColorConverter::convert8BitTo16Bit(data,
		(s16*)image->lock(), header.ImageWidth, header.ImageHeight, palette);
	image->unlock();

	delete [] data;

	return image;
}