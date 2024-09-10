status_t PanoramaThread::handleMessageFinalize()
{
    LOG1("@%s", __FUNCTION__);
    status_t status = NO_ERROR;

    if (mState == PANORAMA_STARTED) {
        LOG1("@%s: nothing to finalize", __FUNCTION__);
        return status;
    }

    mPanoramaStitchThread->flush();

    int checkCnt = 0;
    // ia_panorama_check_stitch_status() should always return 0, as all remained stiching
    // is processed in flush()
    while (ia_panorama_check_stitch_status(mContext) != 0 && checkCnt < STITCH_CHECK_LIMIT) {
        LOG2("Polling ia_panorama_check_stitch_status()");
        usleep(STITCH_CHECK_INTERVAL_USEC);
        ++checkCnt;
    }

    if (checkCnt == STITCH_CHECK_LIMIT) {
        LOGE("Panorama stitching error: stitch check retries exceeded");
        return UNKNOWN_ERROR;
    }

    ia_frame *pFrame = ia_panorama_finalize(mContext);
    if (!pFrame) {
        Mutex::Autolock lock(mStitchLock);

        if (mStopInProgress) {
            LOGD("ia_panorama_finalize() aborted, because of stop panorama in progress");
            return NO_ERROR;
        } else {
            LOGE("ia_panorama_finalize() failed");
            return UNKNOWN_ERROR;
        }
    }

    mPanoramaTotalCount = 0;
    mCurrentMetadata.direction = 0;
    mCurrentMetadata.motion_blur = false;
    mCurrentMetadata.horizontal_displacement = 0;
    mCurrentMetadata.vertical_displacement = 0;

    // create AtomBuffer descriptor for panorama engine memory (ia_frame)
    AtomBuffer img = AtomBufferFactory::createAtomBuffer(ATOM_BUFFER_PANORAMA);
    img.width = pFrame->width;
    img.height = pFrame->height;
    img.bpl = pFrame->stride;
    img.fourcc = V4L2_PIX_FMT_NV12;
    img.size = frameSize(V4L2_PIX_FMT_NV12, img.bpl, img.height); // because pFrame->size from panorama is currently incorrectly zero
    img.buff = NULL;
    img.owner = this;
    img.dataPtr = pFrame->data;
    // return panorama image via callback to PostProcThread, which passes it onwards

    if (mThumbnailWidth > 0 && mThumbnailHeight > 0) {
        AtomBuffer pvImg = AtomBufferFactory::createAtomBuffer(ATOM_BUFFER_POSTVIEW);
        pvImg.width = mThumbnailWidth;
        pvImg.height = mThumbnailHeight;
        pvImg.bpl = mThumbnailWidth;
        pvImg.fourcc = V4L2_PIX_FMT_NV12;
        pvImg.size = frameSize(V4L2_PIX_FMT_NV12, pvImg.bpl, pvImg.height);
        pvImg.owner = this;
        mCallbacks->allocateMemory(&pvImg, pvImg.size);
        if (pvImg.dataPtr == NULL) {
            LOGE("Failed to allocate panorama snapshot memory.");
            return NO_MEMORY;
        }

        float thumbRatio = (float) mThumbnailWidth / mThumbnailHeight;
        float imgRatio = (float) img.width / img.height;
        int startPixel = 0; // used to skip startPixel amount of left side of image
        int skipLinesTop = 0; // used to skip top of the image
        int skipLinesBottom = 0; // used to skip bottom of the image
        int srcWidth, srcHeight;

        if (imgRatio > thumbRatio) {
            fullHeightSrcForThumb(img, srcWidth, srcHeight, startPixel);
        } else if (1 / imgRatio > thumbRatio) {
            fullWidthSrcForThumb(img, srcWidth, srcHeight, skipLinesTop, skipLinesBottom);
        } else {
            // image is rather square, choose method based on which thumbnail dimension is bigger
            if (mThumbnailWidth > mThumbnailHeight) {
                fullWidthSrcForThumb(img, srcWidth, srcHeight, skipLinesTop, skipLinesBottom);
            } else {
                fullHeightSrcForThumb(img, srcWidth, srcHeight, startPixel);
            }
        }

        ImageScaler::downScaleImage(((char *)img.dataPtr) + startPixel, pvImg.dataPtr, mThumbnailWidth,
                mThumbnailHeight, mThumbnailWidth, srcWidth, srcHeight, img.bpl, V4L2_PIX_FMT_NV12,
                skipLinesTop, skipLinesBottom);

        mPanoramaCallback->panoramaFinalized(&img, &pvImg);
    } else
        mPanoramaCallback->panoramaFinalized(&img, NULL);

    if (mState == PANORAMA_DETECTING_OVERLAP || mState == PANORAMA_WAITING_FOR_SNAPSHOT)
        handleMessageStopPanoramaCapture(); // drops state to PANORAMA_STARTED

    return status;
}