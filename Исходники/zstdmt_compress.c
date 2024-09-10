static size_t ZSTDMT_createCompressionJob(ZSTDMT_CCtx* zcs, size_t srcSize, unsigned endFrame)
{
    size_t const dstBufferCapacity = ZSTD_compressBound(srcSize);
    buffer_t const dstBuffer = ZSTDMT_getBuffer(zcs->buffPool, dstBufferCapacity);
    ZSTD_CCtx* const cctx = ZSTDMT_getCCtx(zcs->cctxPool);
    unsigned const jobID = zcs->nextJobID & zcs->jobIDMask;

    if ((cctx==NULL) || (dstBuffer.start==NULL)) {
        zcs->jobs[jobID].jobCompleted = 1;
        zcs->nextJobID++;
        ZSTDMT_waitForAllJobsCompleted(zcs);
        ZSTDMT_releaseAllJobResources(zcs);
        return ERROR(memory_allocation);
    }

    DEBUGLOG(4, "preparing job %u to compress %u bytes with %u preload ", zcs->nextJobID, (U32)srcSize, (U32)zcs->dictSize);
    zcs->jobs[jobID].src = zcs->inBuff.buffer;
    zcs->jobs[jobID].srcStart = zcs->inBuff.buffer.start;
    zcs->jobs[jobID].srcSize = srcSize;
    zcs->jobs[jobID].dictSize = zcs->dictSize;   /* note : zcs->inBuff.filled is presumed >= srcSize + dictSize */
    zcs->jobs[jobID].params = zcs->params;
    if (zcs->nextJobID) zcs->jobs[jobID].params.fParams.checksumFlag = 0;  /* do not calculate checksum within sections, just keep it in header for first section */
    zcs->jobs[jobID].cdict = zcs->nextJobID==0 ? zcs->cdict : NULL;
    zcs->jobs[jobID].fullFrameSize = zcs->frameContentSize;
    zcs->jobs[jobID].dstBuff = dstBuffer;
    zcs->jobs[jobID].cctx = cctx;
    zcs->jobs[jobID].firstChunk = (zcs->nextJobID==0);
    zcs->jobs[jobID].lastChunk = endFrame;
    zcs->jobs[jobID].jobCompleted = 0;
    zcs->jobs[jobID].dstFlushed = 0;
    zcs->jobs[jobID].jobCompleted_mutex = &zcs->jobCompleted_mutex;
    zcs->jobs[jobID].jobCompleted_cond = &zcs->jobCompleted_cond;

    /* get a new buffer for next input */
    if (!endFrame) {
        size_t const newDictSize = MIN(srcSize + zcs->dictSize, zcs->targetDictSize);
        zcs->inBuff.buffer = ZSTDMT_getBuffer(zcs->buffPool, zcs->inBuffSize);
        if (zcs->inBuff.buffer.start == NULL) {   /* not enough memory to allocate next input buffer */
            zcs->jobs[jobID].jobCompleted = 1;
            zcs->nextJobID++;
            ZSTDMT_waitForAllJobsCompleted(zcs);
            ZSTDMT_releaseAllJobResources(zcs);
            return ERROR(memory_allocation);
        }
        DEBUGLOG(5, "inBuff filled to %u", (U32)zcs->inBuff.filled);
        zcs->inBuff.filled -= srcSize + zcs->dictSize - newDictSize;
        DEBUGLOG(5, "new job : filled to %u, with %u dict and %u src", (U32)zcs->inBuff.filled, (U32)newDictSize, (U32)(zcs->inBuff.filled - newDictSize));
        memmove(zcs->inBuff.buffer.start, (const char*)zcs->jobs[jobID].srcStart + zcs->dictSize + srcSize - newDictSize, zcs->inBuff.filled);
        DEBUGLOG(5, "new inBuff pre-filled");
        zcs->dictSize = newDictSize;
    } else {
        zcs->inBuff.buffer = g_nullBuffer;
        zcs->inBuff.filled = 0;
        zcs->dictSize = 0;
        zcs->frameEnded = 1;
        if (zcs->nextJobID == 0)
            zcs->params.fParams.checksumFlag = 0;   /* single chunk : checksum is calculated directly within worker thread */
    }

    DEBUGLOG(3, "posting job %u : %u bytes  (end:%u) (note : doneJob = %u=>%u)", zcs->nextJobID, (U32)zcs->jobs[jobID].srcSize, zcs->jobs[jobID].lastChunk, zcs->doneJobID, zcs->doneJobID & zcs->jobIDMask);
    POOL_add(zcs->factory, ZSTDMT_compressChunk, &zcs->jobs[jobID]);   /* this call is blocking when thread worker pool is exhausted */
    zcs->nextJobID++;
    return 0;
}