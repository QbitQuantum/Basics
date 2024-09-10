HBITMAP ImageDecoder::loadImage(IWICBitmapDecoder *decoder)
{
	IWICBitmapFrameDecode *frame = NULL;
	if (FAILED(decoder->GetFrame(0, &frame)))
	{
		throw Exception("could not get frame");
	}

	IWICBitmapSource *bitmapSource = NULL;
	if (FAILED(WICConvertBitmapSource(GUID_WICPixelFormat32bppPBGRA, frame, &bitmapSource)))
	{
		throw Exception("could not convert bitmap");
	}

	HBITMAP bitmap = convertFrameToBitmap(frame);
	frame->Release();

	return bitmap;
}