// Main interface with NVTT
void NVTTProcessor::process( osg::Image& image, nvtt::Format format, bool generateMipMap, bool resizeToPowerOfTwo, CompressionMethod method, CompressionQuality quality)
{
    // Fill input options
    nvtt::InputOptions inputOptions;
    inputOptions.setTextureLayout(nvtt::TextureType_2D, image.s(), image.t() );
    inputOptions.setNormalMap(false);
    inputOptions.setConvertToNormalMap(false);
    inputOptions.setGamma(2.2f, 2.2f);
    inputOptions.setNormalizeMipmaps(false);
    inputOptions.setWrapMode(nvtt::WrapMode_Clamp);
    if (resizeToPowerOfTwo)
    {
        inputOptions.setRoundMode(nvtt::RoundMode_ToNearestPowerOfTwo);
    }
    inputOptions.setMipmapGeneration(generateMipMap);

    if (image.getPixelFormat() == GL_RGBA)
    {
        inputOptions.setAlphaMode( nvtt::AlphaMode_Transparency );
    }
    else
    {
        inputOptions.setAlphaMode( nvtt::AlphaMode_None );
    }
    std::vector<unsigned char> imageData( image.s() * image.t() * 4 );
    if (image.getPixelFormat() == GL_RGB)
    {
        convertRGBToBGRA( imageData, image );
    }
    else
    {
        convertRGBAToBGRA( imageData, image );
    }
    inputOptions.setMipmapData(&imageData[0],image.s(),image.t());

    // Fill compression options
    nvtt::CompressionOptions compressionOptions;
    switch(quality)
    {
      case FASTEST:
        compressionOptions.setQuality( nvtt::Quality_Fastest );
        break;
      case NORMAL:
        compressionOptions.setQuality( nvtt::Quality_Normal );
        break;
      case PRODUCTION:
        compressionOptions.setQuality( nvtt::Quality_Production);
        break;
      case HIGHEST:
        compressionOptions.setQuality( nvtt::Quality_Highest);
        break;
    }
    compressionOptions.setFormat( format );
    //compressionOptions.setQuantization(false,false,false);
    if (format == nvtt::Format_RGBA)
    {
        if (image.getPixelFormat() == GL_RGB)
        {
            compressionOptions.setPixelFormat(24,0xff,0xff00,0xff0000,0);
        }
        else
        {
            compressionOptions.setPixelFormat(32,0xff,0xff00,0xff0000,0xff000000);
        }
    }

    // Handler
    OSGImageOutputHandler outputHandler(format,image.getPixelFormat() == GL_RGB);
    VPBErrorHandler errorHandler;

    // Fill output options
    nvtt::OutputOptions outputOptions;
    outputOptions.setOutputHandler(&outputHandler);
    outputOptions.setErrorHandler(&errorHandler);
    outputOptions.setOutputHeader(false);

    // Process the compression now
    nvtt::Compressor compressor;
    if(method == USE_GPU)
    {
        compressor.enableCudaAcceleration(true);
        if(!compressor.isCudaAccelerationEnabled())
        {
            OSG_WARN<< "CUDA acceleration was enabled but it is not available. CPU will be used."<<std::endl;
        }
    }
    else
    {
        compressor.enableCudaAcceleration(false);
    }

    compressor.process(inputOptions,compressionOptions,outputOptions);

    outputHandler.assignImage(image);
}