void PhaserEffect::processChannel(const ChannelHandle& handle,
                                  PhaserGroupState* pState,
                                  const CSAMPLE* pInput, CSAMPLE* pOutput,
                                  const mixxx::EngineParameters& bufferParameters,
                                  const EffectEnableState enableState,
                                  const GroupFeatureState& groupFeatures,
                                  const EffectChainMixMode mixMode) {
    Q_UNUSED(handle);
    Q_UNUSED(mixMode);

    if (enableState == EffectEnableState::Enabling) {
        pState->clear();
    }

    CSAMPLE depth = 0;
    if (enableState != EffectEnableState::Disabling) {
        depth = m_pDepthParameter->value();
    }

    double periodParameter = m_pLFOPeriodParameter->value();
    double periodSamples;
    if (groupFeatures.has_beat_length_sec) {
        // periodParameter is a number of beats
        periodParameter = std::max(roundToFraction(periodParameter, 2.0), 1/4.0);
        if (m_pTripletParameter->toBool()) {
            periodParameter /= 3.0;
        }
        periodSamples = periodParameter * groupFeatures.beat_length_sec * bufferParameters.sampleRate();
    } else {
        // periodParameter is a number of seconds
        periodSamples = std::max(periodParameter, 1/4.0) * bufferParameters.sampleRate();
    }
    // freqSkip is used to calculate the phase independently for each channel,
    // so do not multiply periodSamples by the number of channels.
    CSAMPLE freqSkip = 1.0 / periodSamples * 2.0 * M_PI;

    CSAMPLE feedback = m_pFeedbackParameter->value();
    CSAMPLE range = m_pRangeParameter->value();
    int stages = 2 * m_pStagesParameter->value();

    CSAMPLE* oldInLeft = pState->oldInLeft;
    CSAMPLE* oldOutLeft = pState->oldOutLeft;
    CSAMPLE* oldInRight = pState->oldInRight;
    CSAMPLE* oldOutRight = pState->oldOutRight;

    // Using two sets of coefficients for left and right channel
    CSAMPLE filterCoefLeft = 0;
    CSAMPLE filterCoefRight = 0;

    CSAMPLE left = 0, right = 0;

    CSAMPLE_GAIN oldDepth = pState->oldDepth;
    const CSAMPLE_GAIN depthDelta = (depth - oldDepth)
            / bufferParameters.framesPerBuffer();
    const CSAMPLE_GAIN depthStart = oldDepth + depthDelta;

    int stereoCheck = m_pStereoParameter->value();
    int counter = 0;

    for (unsigned int i = 0;
            i < bufferParameters.samplesPerBuffer();
            i += bufferParameters.channelCount()) {
        left = pInput[i] + tanh(left * feedback);
        right = pInput[i + 1] + tanh(right * feedback);

        // For stereo enabled, the channels are out of phase
        pState->leftPhase = fmodf(pState->leftPhase + freqSkip, 2.0 * M_PI);
        pState->rightPhase = fmodf(pState->rightPhase + freqSkip + M_PI * stereoCheck, 2.0 * M_PI);

        // Updating filter coefficients once every 'updateCoef' samples to avoid
        // extra computing
        if ((counter++) % updateCoef == 0) {
                CSAMPLE delayLeft = 0.5 + 0.5 * sin(pState->leftPhase);
                CSAMPLE delayRight = 0.5 + 0.5 * sin(pState->rightPhase);

                // Coefficient computing based on the following:
                // https://ccrma.stanford.edu/~jos/pasp/Classic_Virtual_Analog_Phase.html
                CSAMPLE wLeft = range * delayLeft;
                CSAMPLE wRight = range * delayRight;

                CSAMPLE tanwLeft = tanh(wLeft / 2);
                CSAMPLE tanwRight = tanh(wRight / 2);

                filterCoefLeft = (1.0 - tanwLeft) / (1.0 + tanwLeft);
                filterCoefRight = (1.0 - tanwRight) / (1.0 + tanwRight);
        }

        left = processSample(left, oldInLeft, oldOutLeft, filterCoefLeft, stages);
        right = processSample(right, oldInRight, oldOutRight, filterCoefRight, stages);

        const CSAMPLE_GAIN depth = depthStart + depthDelta * (i / bufferParameters.channelCount());

        // Computing output combining the original and processed sample
        pOutput[i] = pInput[i] * (1.0 - 0.5 * depth) + left * depth * 0.5;
        pOutput[i + 1] = pInput[i + 1] * (1.0 - 0.5 * depth) + right * depth * 0.5;
    }

    pState->oldDepth = depth;
}