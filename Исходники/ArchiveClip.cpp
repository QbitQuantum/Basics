void ArchiveClip::setup ( string videoPath )
{
    alpha = 255.0f ;
    setPixelFormat(OF_PIXELS_RGB );
    ofQTKitDecodeMode decodeMode = OF_QTKIT_DECODE_TEXTURE_ONLY;
    path = videoPath ;
}