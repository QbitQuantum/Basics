void ossimTileToIplFilter::CopyTileToIplImage(T dummyVariable, ossimRefPtr<ossimImageData> inputTile, IplImage *output, ossimIrect neighborhoodRect)
{
    ossimDataObjectStatus status = inputTile->getDataObjectStatus();

    uchar *outputData = (uchar *)output->imageData;
    int outputStep = output->widthStep/sizeof(uchar);
    int outputChannels = output->nChannels;

    ossimScalarType inputType = inputTile->getScalarType();
    double scFactor;

    if (inputType == OSSIM_UINT16)
        scFactor = 0.0039; // 255 / 65535
    else if (inputType == OSSIM_USHORT11)
        scFactor = 0.1246; //255 / 2047
    else if (inputType == OSSIM_UINT8)
        scFactor = 1;
    else
        scFactor = 1;

    int pixVal;

    if (status == OSSIM_PARTIAL)
    {
        for( int band = 0; band < outputChannels; band++) {
            T* inBuf = static_cast<T*>(inputTile->getBuf(band));
            for (long y = 0; y < output->height; ++y)
            {
                for (long x = 0; x < output->width; ++x)
                {

                    pixVal = (int)(*inBuf);

                    if ((int)round(pixVal * scFactor) > 255)
                        outputData[y * outputStep + x*outputChannels + band] = 255;
                    else if ((int)round(pixVal * scFactor) < 0)
                        outputData[y * outputStep + x*outputChannels + band] = 0;
                    else
                        outputData[y * outputStep + x*outputChannels + band] = (uchar)round(pixVal * scFactor);

                    ++inBuf;
                }
            }
        }
    }
    else
    {
        for(int band = 0; band < outputChannels; band++) {
            T* inBuf = static_cast<T*>(inputTile->getBuf(band));
            for (int y = 0; y < output->height; ++y)
            {
                for (int x = 0; x < output->width; ++x)
                {
                    pixVal = (int)(*inBuf);

                    if ((int)round(pixVal * scFactor) > 255)
                        outputData[y * outputStep + x*outputChannels + band] = 255;
                    else if ((int)round(pixVal * scFactor) < 0)
                        outputData[y * outputStep + x*outputChannels + band] = 0;
                    else
                        outputData[y * outputStep + x*outputChannels + band] = (uchar)round(pixVal * scFactor);

                    ++inBuf;
                }
            }
        }
    }
}