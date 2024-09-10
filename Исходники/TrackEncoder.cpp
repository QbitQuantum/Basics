/*static*/
void
AudioTrackEncoder::InterleaveTrackData(AudioChunk& aChunk,
                                       int32_t aDuration,
                                       uint32_t aOutputChannels,
                                       AudioDataValue* aOutput)
{
    switch(aChunk.mBufferFormat) {
    case AUDIO_FORMAT_S16: {
        AutoTArray<const int16_t*, 2> array;
        array.SetLength(aOutputChannels);
        for (uint32_t i = 0; i < array.Length(); i++) {
            array[i] = static_cast<const int16_t*>(aChunk.mChannelData[i]);
        }
        InterleaveTrackData(array, aDuration, aOutputChannels, aOutput, aChunk.mVolume);
        break;
    }
    case AUDIO_FORMAT_FLOAT32: {
        AutoTArray<const float*, 2> array;
        array.SetLength(aOutputChannels);
        for (uint32_t i = 0; i < array.Length(); i++) {
            array[i] = static_cast<const float*>(aChunk.mChannelData[i]);
        }
        InterleaveTrackData(array, aDuration, aOutputChannels, aOutput, aChunk.mVolume);
        break;
    }
    case AUDIO_FORMAT_SILENCE: {
        MOZ_ASSERT(false, "To implement.");
    }
    };
}