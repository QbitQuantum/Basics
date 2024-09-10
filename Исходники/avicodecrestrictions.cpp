bool AviCodecRestrictions::canWriteMovie(const std::wstring &codecName, const TDimension &resolution)
{
	if (codecName == L"Uncompressed") {
		return true;
	}
	//find the codec
	int bpp;
	HIC hic = getCodec(codecName, bpp);
	if (!hic)
		return false;

	bool test = canWork(hic, resolution, bpp);

	ICClose(hic);
	return test;
}