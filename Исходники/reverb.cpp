Reverb::Reverb(ThreadSharedFloatArrayBufferList* impulseResponse, size_t impulseResponseBufferLength, size_t maxFFTSize, bool useBackgroundThreads, bool normalize, float sampleRate)
{
    float scale = 1;

    AutoTArray<const float*,4> irChannels;
    for (size_t i = 0; i < impulseResponse->GetChannels(); ++i) {
        irChannels.AppendElement(impulseResponse->GetData(i));
    }
    AutoTArray<float,1024> tempBuf;

    if (normalize) {
        scale = calculateNormalizationScale(impulseResponse, impulseResponseBufferLength, sampleRate);

        if (scale) {
            tempBuf.SetLength(irChannels.Length()*impulseResponseBufferLength);
            for (uint32_t i = 0; i < irChannels.Length(); ++i) {
                float* buf = &tempBuf[i*impulseResponseBufferLength];
                AudioBufferCopyWithScale(irChannels[i], scale, buf,
                                         impulseResponseBufferLength);
                irChannels[i] = buf;
            }
        }
    }

    initialize(irChannels, impulseResponseBufferLength,
               maxFFTSize, useBackgroundThreads);
}