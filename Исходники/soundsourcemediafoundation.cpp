SINT SoundSourceMediaFoundation::seekSampleFrame(
        SINT frameIndex) {
    DEBUG_ASSERT(isValidFrameIndex(m_currentFrameIndex));

    if (frameIndex >= getMaxFrameIndex()) {
        // EOF
        m_currentFrameIndex = getMaxFrameIndex();
        return m_currentFrameIndex;
    }

    if (frameIndex > m_currentFrameIndex) {
        // seeking forward
        SINT skipFramesCount = frameIndex - m_currentFrameIndex;
        // When to prefer skipping over seeking:
        // 1) The sample buffer would be discarded before seeking anyway and
        //    skipping those already decoded samples effectively costs nothing
        // 2) After seeking we need to decode at least kNumberOfPrefetchFrames
        //    before reaching the actual target position -> Only seek if we
        //    need to decode more than  2 * kNumberOfPrefetchFrames frames
        //    while skipping
        SINT skipFramesCountMax =
                samples2frames(m_sampleBuffer.getSize()) +
                2 * kNumberOfPrefetchFrames;
        if (skipFramesCount <= skipFramesCountMax) {
            skipSampleFrames(skipFramesCount);
        }
    }
    if (frameIndex == m_currentFrameIndex) {
        return m_currentFrameIndex;
    }

    // Discard decoded samples
    m_sampleBuffer.reset();

    // Invalidate current position (end of stream)
    m_currentFrameIndex = getMaxFrameIndex();

    if (m_pSourceReader == nullptr) {
        // reader is dead
        return m_currentFrameIndex;
    }

    // Jump to a position before the actual seeking position.
    // Prefetching a certain number of frames is necessary for
    // sample accurate decoding. The decoder needs to decode
    // some frames in advance to produce the same result at
    // each position in the stream.
    SINT seekIndex = std::max(SINT(frameIndex - kNumberOfPrefetchFrames), AudioSource::getMinFrameIndex());

    LONGLONG seekPos = m_streamUnitConverter.fromFrameIndex(seekIndex);
    DEBUG_ASSERT(seekPos >= 0);
    PROPVARIANT prop;
    HRESULT hrInitPropVariantFromInt64 =
            InitPropVariantFromInt64(seekPos, &prop);
    DEBUG_ASSERT(SUCCEEDED(hrInitPropVariantFromInt64)); // never fails
    HRESULT hrSetCurrentPosition =
            m_pSourceReader->SetCurrentPosition(GUID_NULL, prop);
    PropVariantClear(&prop);
    if (SUCCEEDED(hrSetCurrentPosition)) {
        // NOTE(uklotzde): After SetCurrentPosition() the actual position
        // of the stream is unknown until reading the next samples from
        // the reader. Please note that the first sample decoded after
        // SetCurrentPosition() may start BEFORE the actual target position.
        // See also: https://msdn.microsoft.com/en-us/library/windows/desktop/dd374668(v=vs.85).aspx
        //   "The SetCurrentPosition method does not guarantee exact seeking." ...
        //   "After seeking, the application should call IMFSourceReader::ReadSample
        //    and advance to the desired position.
        SINT skipFramesCount = frameIndex - seekIndex;
        if (skipFramesCount > 0) {
            // We need to fetch at least 1 sample from the reader to obtain the
            // current position!
            skipSampleFrames(skipFramesCount);
            // Now m_currentFrameIndex reflects the actual position of the reader
            if (m_currentFrameIndex < frameIndex) {
                // Skip more samples if frameIndex has not yet been reached
                skipSampleFrames(frameIndex - m_currentFrameIndex);
            }
            if (m_currentFrameIndex != frameIndex) {
                qWarning() << kLogPreamble
                        << "Seek to frame"
                        << frameIndex
                        << "failed";
                // Jump to end of stream (= invalidate current position)
                m_currentFrameIndex = getMaxFrameIndex();
            }
        } else {
            // We are at the beginning of the stream and don't need
            // to skip any frames. Calling IMFSourceReader::ReadSample
            // is not necessary in this special case.
            DEBUG_ASSERT(frameIndex == AudioSource::getMinFrameIndex());
            m_currentFrameIndex = frameIndex;
        }
    } else {
        qWarning() << kLogPreamble
                << "IMFSourceReader::SetCurrentPosition() failed"
                << hrSetCurrentPosition;
        safeRelease(&m_pSourceReader); // kill the reader
    }

    return m_currentFrameIndex;
}