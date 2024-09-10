void MediaStreamer::Initialize(_In_ const WCHAR* url)
{
    Microsoft::WRL::ComPtr<IMFMediaType> outputMediaType;
    Microsoft::WRL::ComPtr<IMFMediaType> mediaType;

    DX::ThrowIfFailed(
        MFStartup(MF_VERSION)
        );

    DX::ThrowIfFailed(
        MFCreateSourceReaderFromURL(url, nullptr, &m_reader)
        );

    // Set the decoded output format as PCM.
    // XAudio2 on Windows can process PCM and ADPCM-encoded buffers.
    // When this sample uses Media Foundation, it always decodes into PCM.

    DX::ThrowIfFailed(
        MFCreateMediaType(&mediaType)
        );

    DX::ThrowIfFailed(
        mediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio)
        );

    DX::ThrowIfFailed(
        mediaType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM)
        );

    DX::ThrowIfFailed(
        m_reader->SetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, mediaType.Get())
        );

    // Get the complete WAVEFORMAT from the Media Type.
    DX::ThrowIfFailed(
        m_reader->GetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, &outputMediaType)
        );

    uint32 formatSize = 0;
    WAVEFORMATEX* waveFormat;
    DX::ThrowIfFailed(
        MFCreateWaveFormatExFromMFMediaType(outputMediaType.Get(), &waveFormat, &formatSize)
        );
    CopyMemory(&m_waveFormat, waveFormat, sizeof(m_waveFormat));
    CoTaskMemFree(waveFormat);

    // Get the total length of the stream, in bytes.
    PROPVARIANT var;
    DX::ThrowIfFailed(
        m_reader->GetPresentationAttribute(MF_SOURCE_READER_MEDIASOURCE, MF_PD_DURATION, &var)
        );

    // duration is in 100ns units; convert to seconds, and round up
    // to the nearest whole byte.
    ULONGLONG duration = var.uhVal.QuadPart;
    m_maxStreamLengthInBytes =
        static_cast<unsigned int>(
            ((duration * static_cast<ULONGLONG>(m_waveFormat.nAvgBytesPerSec)) + 10000000) /
            10000000
            );
}