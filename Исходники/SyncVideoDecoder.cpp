FrameAvailableCode SyncVideoDecoder::getRenderedBmps(vector<BitmapPtr>& pBmps, 
        float timeWanted)
{
    AVG_ASSERT(getState() == DECODING);
    ScopeTimer timer(RenderToBmpProfilingZone);
    FrameAvailableCode frameAvailable;
    if (timeWanted == -1) {
        readFrame(m_pFrame);
        frameAvailable = FA_NEW_FRAME;
    } else {
        frameAvailable = readFrameForTime(m_pFrame, timeWanted);
    }
    if (frameAvailable == FA_USE_LAST_FRAME || isEOF()) {
        return FA_USE_LAST_FRAME;
    } else {
        allocFrameBmps(pBmps);
        if (pixelFormatIsPlanar(getPixelFormat())) {
            ScopeTimer timer(CopyImageProfilingZone);
            for (unsigned i = 0; i < pBmps.size(); ++i) {
                m_pFrameDecoder->copyPlaneToBmp(pBmps[i], m_pFrame->data[i],
                        m_pFrame->linesize[i]);
            }
        } else {
            m_pFrameDecoder->convertFrameToBmp(m_pFrame, pBmps[0]);
        }
        return FA_NEW_FRAME;
    }
}