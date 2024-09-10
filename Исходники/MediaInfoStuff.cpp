MediaOutputInfo* GetBestMediaOutput(const List<MediaOutputInfo> &outputList, UINT width, UINT height, UINT preferredType, UINT64 &frameInterval)
{
    MediaOutputInfo *bestMediaOutput = NULL;
    int bestPriority = -1;
    UINT64 closestIntervalDifference = 0xFFFFFFFFFFFFFFFFLL;
    UINT64 bestFrameInterval = 0;

    bool bUsePreferredType = preferredType != -1;

    for(UINT i=0; i<outputList.Num(); i++)
    {
        MediaOutputInfo &outputInfo = outputList[i];
        VIDEOINFOHEADER *pVih = reinterpret_cast<VIDEOINFOHEADER*>(outputInfo.mediaType->pbFormat);

        if( outputInfo.minCX <= width  && outputInfo.maxCX >= width &&
            outputInfo.minCY <= height && outputInfo.maxCY >= height)
        {
            int priority = inputPriority[(UINT)outputInfo.videoType];
            if(priority == -1)
                continue;

            if( (!bUsePreferredType && (priority >= bestPriority || !bestMediaOutput)) ||
                (bUsePreferredType && (UINT)outputInfo.videoType == preferredType))
            {
                UINT64 curInterval;
                if(frameInterval > outputInfo.maxFrameInterval)
                    curInterval = outputInfo.maxFrameInterval;
                else if(frameInterval < outputInfo.minFrameInterval)
                    curInterval = outputInfo.minFrameInterval;
                else
                    curInterval = frameInterval;

                UINT64 intervalDifference = (UINT64)_abs64(INT64(curInterval)-INT64(frameInterval));

                if(intervalDifference < closestIntervalDifference)
                {
                    closestIntervalDifference = intervalDifference;
                    bestFrameInterval = curInterval;
                    bestMediaOutput = &outputInfo;
                    bestPriority = priority;
                }
            }
        }
    }

    frameInterval = bestFrameInterval;
    return bestMediaOutput;
}