/**
Implementation of pure virtual function.
@see    MWTCacheInterface::ReadL()
*/
void CDynamicDirCache::ReadL(TInt64 aPos, TInt aLength, TDes8& aDes)
    {
#ifdef _DEBUG
    if(iCacheDisabled)
        {
        // cache is disabled for debug purposes
        __PRINT(_L("CDynamicDirCache disabled"));
        User::LeaveIfError(iDrive.ReadNonCritical(aPos, aLength, aDes));
        return;
        }
#endif //_DEBUG

    aDes.Zero();
    const TUint32 PageSz = iPageSizeInBytes;//-- cache page size

    TInt64 pageStartMedPos = CalcPageStartPos(aPos);
    const TUint32 bytesToPageEnd = (TUint32)(pageStartMedPos + PageSz - aPos); //-- number of bytes from aPos to the end of the page

//    __PRINT5(_L("CDynamicDirCache::ReadL: aPos=%lx, aLength=%x, page:%lx, pageSz:%x, bytesToPageEnd=%x"), aPos, aLength, pageStartMedPos, PageSz, bytesToPageEnd);
    // if all data needed is on a single page
    if((TUint32)aLength <= bytesToPageEnd)
        {
        ReadDataFromSinglePageL(aPos, aLength, aDes);
        }
    // or data to be read cross cache page boundary or probably we have more than 1 page to read
    else
        {
        __PRINT(_L("CDynamicDirCache::ReadL() CROSS PAGE!"));
        TUint32 dataLen(aLength);   //-- current data length
        TInt64  currMediaPos(aPos); //-- current media position

        //-- 1. read data that are already in the current page
        ReadDataFromSinglePageL(currMediaPos, bytesToPageEnd, aDes);
        dataLen -= bytesToPageEnd;
        currMediaPos += bytesToPageEnd;

        TPtr8 dataNext = aDes.MidTPtr(aDes.Length());

        //-- 2. read whole pages of data
        while (dataLen >= PageSz)
            {
            //-- find out if currMediaPos is in cache. If not, find a spare page and read data there
            ReadDataFromSinglePageL(currMediaPos, PageSz, dataNext);
            currMediaPos += PageSz;
            dataLen -= PageSz;
            dataNext = dataNext.MidTPtr(dataNext.Length());
            }

        //-- 3. read the rest of the data
        if(dataLen > 0)
            {
            ReadDataFromSinglePageL(currMediaPos, dataLen, dataNext);
            }
        } //else((TUint32)aLength <= bytesToPageEnd)
    }