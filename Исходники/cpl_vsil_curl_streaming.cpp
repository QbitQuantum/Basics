size_t VSICurlStreamingHandle::Read( void *pBuffer, size_t nSize, size_t nMemb )
{
    GByte* pabyBuffer = (GByte*)pBuffer;
    size_t nBufferRequestSize = nSize * nMemb;
    if (nBufferRequestSize == 0)
        return 0;
    size_t nRemaining = nBufferRequestSize;

    AcquireMutex();
    int bHastComputedFileSizeLocal = bHastComputedFileSize;
    vsi_l_offset fileSizeLocal = fileSize;
    ReleaseMutex();

    if (bHastComputedFileSizeLocal && curOffset >= fileSizeLocal)
    {
        CPLDebug("VSICURL", "Read attempt beyond end of file");
        bEOF = TRUE;
    }
    if (bEOF)
        return 0;

    if (curOffset < nRingBufferFileOffset)
        PutRingBufferInCache();

    if (ENABLE_DEBUG)
        CPLDebug("VSICURL", "Read [" CPL_FRMT_GUIB ", " CPL_FRMT_GUIB "[ in %s",
                 curOffset, curOffset + nBufferRequestSize, pszURL);

#ifdef notdef
    if( pCachedData != NULL && nCachedSize >= 1024 &&
        nRecomputedChecksumOfFirst1024Bytes == 0 )
    {
        for(size_t i = 0; i < 1024 / sizeof(int); i ++)
        {
            int nVal;
            memcpy(&nVal, pCachedData + i * sizeof(int), sizeof(int));
            nRecomputedChecksumOfFirst1024Bytes += nVal;
        }

        if( bHastComputedFileSizeLocal )
        {
            poFS->AcquireMutex();
            CachedFileProp* cachedFileProp = poFS->GetCachedFileProp(pszURL);
            if( cachedFileProp->nChecksumOfFirst1024Bytes == 0 )
            {
                cachedFileProp->nChecksumOfFirst1024Bytes = nRecomputedChecksumOfFirst1024Bytes;
            }
            else if( nRecomputedChecksumOfFirst1024Bytes != cachedFileProp->nChecksumOfFirst1024Bytes )
            {
                CPLDebug("VSICURL", "Invalidating previously cached file size. First bytes of file have changed!");
                AcquireMutex();
                bHastComputedFileSize = FALSE;
                cachedFileProp->bHastComputedFileSize = FALSE;
                cachedFileProp->nChecksumOfFirst1024Bytes = 0;
                ReleaseMutex();
            }
            poFS->ReleaseMutex();
        }
    }
#endif

    /* Can we use the cache ? */
    if( pCachedData != NULL && curOffset < nCachedSize )
    {
        size_t nSz = MIN(nRemaining, (size_t)(nCachedSize - curOffset));
        if (ENABLE_DEBUG)
            CPLDebug("VSICURL", "Using cache for [%d, %d[ in %s",
                     (int)curOffset, (int)(curOffset + nSz), pszURL);
        memcpy(pabyBuffer, pCachedData + curOffset, nSz);
        pabyBuffer += nSz;
        curOffset += nSz;
        nRemaining -= nSz;
    }

    /* Is the request partially covered by the cache and going beyond file size ? */
    if ( pCachedData != NULL && bHastComputedFileSizeLocal &&
         curOffset <= nCachedSize &&
         curOffset + nRemaining > fileSizeLocal &&
         fileSize == nCachedSize )
    {
        size_t nSz = (size_t) (nCachedSize - curOffset);
        if (ENABLE_DEBUG && nSz != 0)
            CPLDebug("VSICURL", "Using cache for [%d, %d[ in %s",
                    (int)curOffset, (int)(curOffset + nSz), pszURL);
        memcpy(pabyBuffer, pCachedData + curOffset, nSz);
        pabyBuffer += nSz;
        curOffset += nSz;
        nRemaining -= nSz;
        bEOF = TRUE;
    }

    /* Has a Seek() being done since the last Read() ? */
    if (!bEOF && nRemaining > 0 && curOffset != nRingBufferFileOffset)
    {
        /* Backward seek : we need to restart the download from the start */
        if (curOffset < nRingBufferFileOffset)
            StopDownload();

        StartDownload();

#define SKIP_BUFFER_SIZE    32768
        GByte* pabyTmp = (GByte*)CPLMalloc(SKIP_BUFFER_SIZE);

        CPLAssert(curOffset >= nRingBufferFileOffset);
        vsi_l_offset nBytesToSkip = curOffset - nRingBufferFileOffset;
        while(nBytesToSkip > 0)
        {
            vsi_l_offset nBytesToRead = nBytesToSkip;

            AcquireMutex();
            if (nBytesToRead > oRingBuffer.GetSize())
                nBytesToRead = oRingBuffer.GetSize();
            if (nBytesToRead > SKIP_BUFFER_SIZE)
                nBytesToRead = SKIP_BUFFER_SIZE;
            oRingBuffer.Read(pabyTmp, (size_t)nBytesToRead);

            /* Signal to the producer that we have ingested some bytes */
            CPLCondSignal(hCondConsumer);
            ReleaseMutex();

            if (nBytesToRead)
                AddRegion(nRingBufferFileOffset, (size_t)nBytesToRead, pabyTmp);

            nBytesToSkip -= nBytesToRead;
            nRingBufferFileOffset += nBytesToRead;

            if (nBytesToRead == 0 && nBytesToSkip != 0)
            {
                if (ENABLE_DEBUG)
                    CPLDebug("VSICURL", "Waiting for writer to produce some bytes...");

                AcquireMutex();
                while(oRingBuffer.GetSize() == 0 && bDownloadInProgress)
                    CPLCondWait(hCondProducer, hRingBufferMutex);
                int bBufferEmpty = (oRingBuffer.GetSize() == 0);
                ReleaseMutex();

                if (bBufferEmpty && !bDownloadInProgress)
                    break;
            }
        }

        CPLFree(pabyTmp);

        if (nBytesToSkip != 0)
        {
            bEOF = TRUE;
            return 0;
        }
    }

    if (!bEOF && nRemaining > 0)
    {
        StartDownload();
        CPLAssert(curOffset == nRingBufferFileOffset);
    }

    /* Fill the destination buffer from the ring buffer */
    while(!bEOF && nRemaining > 0)
    {
        AcquireMutex();
        size_t nToRead = oRingBuffer.GetSize();
        if (nToRead > nRemaining)
            nToRead = nRemaining;
        oRingBuffer.Read(pabyBuffer, nToRead);

        /* Signal to the producer that we have ingested some bytes */
        CPLCondSignal(hCondConsumer);
        ReleaseMutex();

        if (nToRead)
            AddRegion(curOffset, nToRead, pabyBuffer);

        nRemaining -= nToRead;
        pabyBuffer += nToRead;
        curOffset += nToRead;
        nRingBufferFileOffset += nToRead;

        if (nToRead == 0 && nRemaining != 0)
        {
            if (ENABLE_DEBUG)
                CPLDebug("VSICURL", "Waiting for writer to produce some bytes...");

            AcquireMutex();
            while(oRingBuffer.GetSize() == 0 && bDownloadInProgress)
                CPLCondWait(hCondProducer, hRingBufferMutex);
            int bBufferEmpty = (oRingBuffer.GetSize() == 0);
            ReleaseMutex();

            if (bBufferEmpty && !bDownloadInProgress)
                break;
        }
    }

    if (ENABLE_DEBUG)
        CPLDebug("VSICURL", "Read(%d) = %d",
                (int)nBufferRequestSize, (int)(nBufferRequestSize - nRemaining));
    size_t nRet = (nBufferRequestSize - nRemaining) / nSize;
    if (nRet < nMemb)
        bEOF = TRUE;

    return nRet;
}