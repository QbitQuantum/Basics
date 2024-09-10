void FImage::CopyTo(FImage& DestImage, ERawImageFormat::Type DestFormat, bool DestSRGB) const
{
	DestImage.SizeX = SizeX;
	DestImage.SizeY = SizeY;
	DestImage.NumSlices = NumSlices;
	DestImage.Format = DestFormat;
	DestImage.bSRGB = DestSRGB;
	InitImageStorage(DestImage);
	CopyImage(*this, DestImage);
}