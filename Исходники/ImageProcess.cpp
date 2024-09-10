void CImageProcess::CutImage(IplImage *source, vector<CvRect> rect, vector<IplImage*> *dst)
{
	vector<CvRect>::iterator it = rect.begin();
	for(; it != rect.end(); it++){
		CvSize size;
		size.height = it->height;
		size.width = it->width;
		IplImage *image = cvCreateImage(size,source->depth, source->nChannels);
		memset(image->imageData, 0, image->imageSize);
		CopyImage(source,image, *it);
		dst->push_back(image);
	}
}