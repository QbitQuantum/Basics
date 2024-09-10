status_t GraphicBufferSource::submitBuffer_l(
        const BufferQueue::BufferItem &item, int cbi) {
    ALOGV("submitBuffer_l cbi=%d", cbi);

    int64_t timeUs = getTimestamp(item);
    if (timeUs < 0ll) {
        return UNKNOWN_ERROR;
    }

    CodecBuffer& codecBuffer(mCodecBuffers.editItemAt(cbi));
    codecBuffer.mGraphicBuffer = mBufferSlot[item.mBuf];
    codecBuffer.mBuf = item.mBuf;
    codecBuffer.mFrameNumber = item.mFrameNumber;

    OMX_BUFFERHEADERTYPE* header = codecBuffer.mHeader;

#ifdef MTK_AOSP_ENHANCEMENT
    //error handling ALPS01556865
    if( NULL == header->pBuffer )
    {
        ALOGW("WARNING: header->pBuffer is NULL, line:%d", __LINE__);
        return OMX_ErrorBadParameter;
    }
    else if(mDumpRawFile != NULL) //try to dump if necessary
    {
        OMX_U8 *rawbuffer=NULL;
        uint32_t mWidth;
        uint32_t mHeight;
        uint32_t mStride;

        buffer_handle_t _handle = *((buffer_handle_t*)(header->pBuffer + 4));
        //GraphicBufferMapper &gbm = GraphicBufferMapper::getInstance();
        codecBuffer.mGraphicBuffer->lock(GRALLOC_USAGE_SW_READ_OFTEN, (void**)&rawbuffer);
        //gbm.lock(_handle, GRALLOC_USAGE_SW_READ_OFTEN, Rect(iSrcWidth, iSrcHeight), (void**)&rawbuffer);
        //memcpy(mEffectYUVBuffer, buffer, iSrcWidth*iSrcHeight*3/2);

        mWidth = codecBuffer.mGraphicBuffer->getWidth();
        mHeight = codecBuffer.mGraphicBuffer->getHeight();
        mStride = codecBuffer.mGraphicBuffer->getStride();
        
        ALOGD("getWidth:%d, Height:%d, Stride:%d, PixelFormat:%d", mWidth,
            mHeight, mStride,
            codecBuffer.mGraphicBuffer->getPixelFormat());

        if (NULL == rawbuffer)
        {
            codecBuffer.mGraphicBuffer->unlock();
        }
        else if ( ( 0 != codecBuffer.mGraphicBuffer->getWidth() ) && (mDumpRawFile != NULL) ) {
                size_t nWrite = fwrite(rawbuffer, 1, mWidth*mHeight*4,  mDumpRawFile);//fix ARGB, FIXME
                ALOGD("RawBuf %x, written %d bytes, %d, mRangeLength = %d, ftell = %d", 
                    rawbuffer, nWrite, mWidth*mHeight, mStride*mHeight, (int)ftell(mDumpRawFile));
        }
        if (NULL != rawbuffer)
        {
            codecBuffer.mGraphicBuffer->unlock();
        }
    }
#endif //ifdef MTK_AOSP_ENHANCEMENT

    CHECK(header->nAllocLen >= 4 + sizeof(buffer_handle_t));
    OMX_U8* data = header->pBuffer;
    buffer_handle_t handle;
    if (!mUseGraphicBufferInMeta) {
        const OMX_U32 type = kMetadataBufferTypeGrallocSource;
        handle = codecBuffer.mGraphicBuffer->handle;
        memcpy(data, &type, 4);
        memcpy(data + 4, &handle, sizeof(buffer_handle_t));
    } else {
        // codecBuffer holds a reference to the GraphicBuffer, so
        // it is valid while it is with the OMX component
        const OMX_U32 type = kMetadataBufferTypeGraphicBuffer;
        memcpy(data, &type, 4);
        // passing a non-reference-counted graphicBuffer
        GraphicBuffer *buffer = codecBuffer.mGraphicBuffer.get();
        handle = buffer->handle;
        memcpy(data + 4, &buffer, sizeof(buffer));
    }

    status_t err = mNodeInstance->emptyDirectBuffer(header, 0,
            4 + sizeof(buffer_handle_t), OMX_BUFFERFLAG_ENDOFFRAME,
            timeUs);
    if (err != OK) {
        ALOGW("WARNING: emptyDirectBuffer failed: 0x%x", err);
        codecBuffer.mGraphicBuffer = NULL;
        return err;
    }

    ALOGV("emptyDirectBuffer succeeded, h=%p p=%p bufhandle=%p",
            header, header->pBuffer, handle);
    return OK;
}