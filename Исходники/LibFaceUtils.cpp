IplImage* LibFaceUtils::scaledSection(const IplImage* src, const CvRect& sourceRect, const CvSize& destSize)
{
    if (destSize.width == sourceRect.width && destSize.height == sourceRect.height)
        return copyRect(src, sourceRect);

    // Create a non-const header to set the ROI
    IplImage* srcHeader  = cvCreateImageHeader(cvSize(src->width, src->height), src->depth, src->nChannels);
    srcHeader->imageData = const_cast<char*>(src->imageData);
    cvSetImageROI(srcHeader, sourceRect);

    IplImage* result = cvCreateImage(cvSize(destSize.width, destSize.height), src->depth, src->nChannels);
    cvResize(srcHeader, result);

    cvReleaseImageHeader(&srcHeader);
    return result;
}