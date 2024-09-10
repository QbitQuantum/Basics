void DeferredImageDecoder::prepareLazyDecodedFrames()
{
    if (!s_enabled
        || !m_actualDecoder
        || !m_actualDecoder->isSizeAvailable()
        || m_actualDecoder->filenameExtension() == "ico")
        return;

    activateLazyDecoding();

    const size_t previousSize = m_lazyDecodedFrames.size();
    m_lazyDecodedFrames.resize(m_actualDecoder->frameCount());

    // We have encountered a broken image file. Simply bail.
    if (m_lazyDecodedFrames.size() < previousSize)
        return;

    for (size_t i = previousSize; i < m_lazyDecodedFrames.size(); ++i) {
        OwnPtr<ImageFrame> frame(adoptPtr(new ImageFrame()));
        frame->setSkBitmap(createBitmap(i));
        frame->setDuration(m_actualDecoder->frameDurationAtIndex(i));
        frame->setStatus(m_actualDecoder->frameIsCompleteAtIndex(i) ? ImageFrame::FrameComplete : ImageFrame::FramePartial);
        m_lazyDecodedFrames[i] = frame.release();
    }

    // The last lazy decoded frame created from previous call might be
    // incomplete so update its state.
    if (previousSize) {
        const size_t lastFrame = previousSize - 1;
        m_lazyDecodedFrames[lastFrame]->setStatus(m_actualDecoder->frameIsCompleteAtIndex(lastFrame) ? ImageFrame::FrameComplete : ImageFrame::FramePartial);

        // If data has changed then create a new bitmap. This forces
        // Skia to decode again.
        if (m_dataChanged) {
            m_dataChanged = false;
            m_lazyDecodedFrames[lastFrame]->setSkBitmap(createBitmap(lastFrame));
        }
    }

    if (m_allDataReceived) {
        m_repetitionCount = m_actualDecoder->repetitionCount();
        m_actualDecoder.clear();
        m_data = nullptr;
    }
}