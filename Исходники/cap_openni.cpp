inline void getBGRImageFromMetaData( const xn::ImageMetaData& imageMetaData, cv::Mat& bgrImage )
{
    if( imageMetaData.PixelFormat() != XN_PIXEL_FORMAT_RGB24 )
        CV_Error( CV_StsUnsupportedFormat, "Unsupported format of grabbed image\n" );

    cv::Mat rgbImage( imageMetaData.YRes(), imageMetaData.XRes(), CV_8UC3 );
    const XnRGB24Pixel* pRgbImage = imageMetaData.RGB24Data();

    // CV_Assert( 3*sizeof(uchar) == sizeof(XnRGB24Pixel) );
    memcpy( rgbImage.data, pRgbImage, rgbImage.total()*sizeof(XnRGB24Pixel) );
    cv::cvtColor( rgbImage, bgrImage, CV_RGB2BGR );
}