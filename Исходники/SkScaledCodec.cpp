SkCodec::Result SkScaledCodec::onGetPixels(const SkImageInfo& requestedInfo, void* dst,
                                           size_t rowBytes, const Options& options,
                                           SkPMColor ctable[], int* ctableCount) {

    if (options.fSubset) {
        // Subsets are not supported.
        return kUnimplemented;
    } 

    Result result = fScanlineDecoder->start(requestedInfo, &options, ctable, ctableCount);
    if (kSuccess == result) {
        // native decode supported
        return fScanlineDecoder->getScanlines(dst, requestedInfo.height(), rowBytes);

    }

    if (kInvalidScale != result) {
        // no scaling requested
        return result;
    }
    
    // scaling requested
    int sampleX;
    int sampleY;
    if (!scaling_supported(requestedInfo, fScanlineDecoder->getInfo(), &sampleX, &sampleY)) {
        return kInvalidScale;
    }
    // set first sample pixel in y direction
    int Y0 = sampleY >> 1;

    int dstHeight = requestedInfo.height();
    int srcHeight = fScanlineDecoder->getInfo().height();
    
    SkImageInfo info = requestedInfo;
    // use original height as scanlineDecoder does not support y sampling natively
    info = info.makeWH(requestedInfo.width(), srcHeight);

    // update scanlineDecoder with new info
    result = fScanlineDecoder->start(info, &options, ctable, ctableCount);
    if (kSuccess != result) {
        return result;
    }
    
    const bool requiresPostYSampling = fScanlineDecoder->requiresPostYSampling();

    if (requiresPostYSampling) {
        SkAutoMalloc storage(srcHeight * rowBytes);
        uint8_t* storagePtr = static_cast<uint8_t*>(storage.get());
        result = fScanlineDecoder->getScanlines(storagePtr, srcHeight, rowBytes);
        if (kSuccess != result) {
            return result;
        }
        storagePtr += Y0 * rowBytes;
        for (int y = 0; y < dstHeight; y++) {
            memcpy(dst, storagePtr, rowBytes);
            storagePtr += sampleY * rowBytes;
            dst = SkTAddOffset<void>(dst, rowBytes);
        }
    } else {
        // does not require post y sampling
        result = fScanlineDecoder->skipScanlines(Y0);
        if (kSuccess != result) {
            return result;
        }
        for (int y = 0; y < dstHeight; y++) {
            result = fScanlineDecoder->getScanlines(dst, 1, rowBytes);
            if (kSuccess != result) {
                return result;
            }
            if (y < dstHeight - 1) {
                result = fScanlineDecoder->skipScanlines(sampleY - 1);
                if (kSuccess != result) {
                    return result;
                }
            }
            dst = SkTAddOffset<void>(dst, rowBytes);
        }
    }
    return kSuccess;
}