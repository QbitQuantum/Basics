bool AudioFormatWriter::writeFromAudioSampleBuffer (const AudioSampleBuffer& source, int startSample, int numSamples)
{
    jassert (startSample >= 0 && startSample + numSamples <= source.getNumSamples() && source.getNumChannels() > 0);

    if (numSamples <= 0)
        return true;

    HeapBlock<int> tempBuffer;
    HeapBlock<int*> chans (numChannels + 1);
    chans [numChannels] = 0;

    if (isFloatingPoint())
    {
        for (int i = (int) numChannels; --i >= 0;)
            chans[i] = reinterpret_cast<int*> (source.getSampleData (i, startSample));
    }
    else
    {
        tempBuffer.malloc (numSamples * numChannels);

        for (unsigned int i = 0; i < numChannels; ++i)
        {
            typedef AudioData::Pointer <AudioData::Int32, AudioData::NativeEndian, AudioData::NonInterleaved, AudioData::NonConst> DestSampleType;
            typedef AudioData::Pointer <AudioData::Float32, AudioData::NativeEndian, AudioData::NonInterleaved, AudioData::Const> SourceSampleType;

            DestSampleType destData (chans[i] = tempBuffer + i * numSamples);
            SourceSampleType sourceData (source.getSampleData ((int) i, startSample));
            destData.convertSamples (sourceData, numSamples);
        }
    }

    return write ((const int**) chans.getData(), numSamples);
}