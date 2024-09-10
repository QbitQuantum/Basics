IMFMediaType* MFDecoderSourceReader::setSource(IMFMediaSource *source, const QAudioFormat &audioFormat)
{
    IMFMediaType *mediaType = NULL;
    if (m_source == source)
        return mediaType;
    if (m_source) {
        m_source->Release();
        m_source = NULL;
    }
    if (m_sourceReader) {
        m_sourceReader->Release();
        m_sourceReader = NULL;
    }
    if (!source)
        return mediaType;
    IMFAttributes *attr = NULL;
    MFCreateAttributes(&attr, 1);
    if (SUCCEEDED(attr->SetUnknown(MF_SOURCE_READER_ASYNC_CALLBACK, this))) {
        if (SUCCEEDED(MFCreateSourceReaderFromMediaSource(source, attr, &m_sourceReader))) {
            m_source = source;
            m_source->AddRef();
            m_sourceReader->SetStreamSelection(DWORD(MF_SOURCE_READER_ALL_STREAMS), FALSE);
            m_sourceReader->SetStreamSelection(DWORD(MF_SOURCE_READER_FIRST_AUDIO_STREAM), TRUE);
            IMFMediaType *pPartialType = NULL;
            MFCreateMediaType(&pPartialType);
            pPartialType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);

            if (audioFormat.sampleType() == QAudioFormat::Float) {
                pPartialType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_Float);
            } else {
                pPartialType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM);
            }

            m_sourceReader->SetCurrentMediaType(DWORD(MF_SOURCE_READER_FIRST_AUDIO_STREAM), NULL, pPartialType);
            pPartialType->Release();
            m_sourceReader->GetCurrentMediaType(DWORD(MF_SOURCE_READER_FIRST_AUDIO_STREAM), &mediaType);
            // Ensure the stream is selected.
            m_sourceReader->SetStreamSelection(DWORD(MF_SOURCE_READER_FIRST_AUDIO_STREAM), TRUE);
        }
        attr->Release();
    }
    return mediaType;
}