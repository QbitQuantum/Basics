void SuperSpreadAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& /*midiMessages*/)
{
    unsigned int csr = _mm_getcsr();
    _mm_setcsr(csr | 0x8040);
    AudioProcessorParameter* mixParam = parameterState->getParameter("Mix");
    const NormalisableRange<float> mixRange(parameterState->getParameterRange("Mix"));

    const float spread0 = parameterState->getParameter("Spread")->getValue();
    const float mix = mixRange.convertFrom0to1(mixParam->getValue());
    const float detuneFade = jmin(spread0/0.1f, 1.f);

    const float detunedGain = mix >= 100.f ? 1.f : mix / 100.f;
    const float dryGain = mix <= 100.f ? 1.f : detuneFade < 1.f ? jmax(0.5f * (1.f - detuneFade), (200.f - mix) / 100.f) : (200.f - mix) / 100.f;
    const float spreadGain = detunedGain * detuneFade;


    const float spread = 0.5f * spread0*spread0;

    const int numChannels = buffer.getNumChannels();
    const int numSamples = buffer.getNumSamples();
    float* chL = buffer.getWritePointer(0);
    float* chR = numChannels == 2 ? buffer.getWritePointer(1) : nullptr;

    for (int i=0; i<12 / 2; ++i)
    {
        pitchBuffer.copyFrom(i, 0, chL, numSamples);

        if (chR != nullptr)
            pitchBuffer.copyFrom(6 + i, 0, chR, numSamples);
    }

    mainDelay.processBlock(chL, chR, numSamples);
    buffer.applyGain(dryGain);

    const float maxPitches[6] = {0.893f, 0.939f, 0.98f, 1.02f, 1.064f, 1.11f}; 

    for (int i=0; i<6; ++i)
    {
        shifter[i]->setPitch(std::pow(maxPitches[i], spread));
        shifter[i+6]->setPitch(std::pow(1.f / maxPitches[i], spread));

        float* procL = pitchBuffer.getWritePointer(i);
        float* procR = pitchBuffer.getWritePointer(i+6);

        shifter[i]->processBlock(procL, numSamples);
        buffer.addFrom(0, 0, procL, numSamples, spreadGain/* * gain*/);

        if (numChannels == 2)
        {
            shifter[i+6]->processBlock(procR, numSamples);
            buffer.addFrom(1, 0, procR, numSamples, spreadGain/* * gain*/);
        }
    }

    const float totalGain = spreadGain == 0.f ? 1.f : 1.41f / (1.f + std::sqrt(6.f) * spreadGain);

    buffer.applyGain(totalGain);

    _mm_setcsr(csr);
}