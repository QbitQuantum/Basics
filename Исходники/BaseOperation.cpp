int CBaseOperation::saveToJpeg(AVFrame *pFrame, int width, int height, char *buffer, int bufferSize){
	GdiplusInit gdiplusinit;
	CLSID imgClsid;
	int encoderClsid = GetGdiplusEncoderClsid(L"image/jpeg", &imgClsid);
	auto image = std::make_unique<Gdiplus::Bitmap>(width, height, pFrame->linesize[0], PixelFormat32bppRGB, pFrame->data[0]);
	if (encoderClsid != -1){
		IStream *stream;
		CreateStreamOnHGlobal(nullptr, TRUE, static_cast<LPSTREAM*>(&stream));
		if (image->Save(stream, &imgClsid) == Gdiplus::Ok){
			STATSTG statstg;
			stream->Stat(&statstg, STATFLAG_DEFAULT);
			ULARGE_INTEGER streamSize = statstg.cbSize;
			LARGE_INTEGER zero;
			zero.QuadPart = 0;
			if (bufferSize >= streamSize.QuadPart){
				stream->Seek(zero, STREAM_SEEK_SET, nullptr);
				stream->Read(buffer, streamSize.QuadPart, nullptr);
				stream->Release();
				return streamSize.QuadPart;
			}
			stream->Release();
			return streamSize.QuadPart*(-1);
		}
		return 3;
	}
	return 3;
}