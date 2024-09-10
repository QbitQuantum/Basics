void HRTFPanner::pan(double desiredAzimuth, double elevation, const AudioBus* inputBus, AudioBus* outputBus, size_t framesToProcess)
{
    unsigned numInputChannels = inputBus ? inputBus->numberOfChannels() : 0;

    bool isInputGood = inputBus &&  numInputChannels >= 1 && numInputChannels <= 2;
    ASSERT(isInputGood);

    bool isOutputGood = outputBus && outputBus->numberOfChannels() == 2 && framesToProcess <= outputBus->length();
    ASSERT(isOutputGood);

    if (!isInputGood || !isOutputGood) {
        if (outputBus)
            outputBus->zero();
        return;
    }

    HRTFDatabase* database = m_databaseLoader->database();
    ASSERT(database);
    if (!database) {
        outputBus->zero();
        return;
    }

    // IRCAM HRTF azimuths values from the loaded database is reversed from the panner's notion of azimuth.
    double azimuth = -desiredAzimuth;

    bool isAzimuthGood = azimuth >= -180.0 && azimuth <= 180.0;
    ASSERT(isAzimuthGood);
    if (!isAzimuthGood) {
        outputBus->zero();
        return;
    }

    // Normally, we'll just be dealing with mono sources.
    // If we have a stereo input, implement stereo panning with left source processed by left HRTF, and right source by right HRTF.
    const AudioChannel* inputChannelL = inputBus->channelByType(AudioBus::ChannelLeft);
    const AudioChannel* inputChannelR = numInputChannels > 1 ? inputBus->channelByType(AudioBus::ChannelRight) : 0;

    // Get source and destination pointers.
    const float* sourceL = inputChannelL->data();
    const float* sourceR = numInputChannels > 1 ? inputChannelR->data() : sourceL;
    float* destinationL = outputBus->channelByType(AudioBus::ChannelLeft)->mutableData();
    float* destinationR = outputBus->channelByType(AudioBus::ChannelRight)->mutableData();

    double azimuthBlend;
    int desiredAzimuthIndex = calculateDesiredAzimuthIndexAndBlend(azimuth, azimuthBlend);

    // Initially snap azimuth and elevation values to first values encountered.
    if (m_azimuthIndex1 == UninitializedAzimuth) {
        m_azimuthIndex1 = desiredAzimuthIndex;
        m_elevation1 = elevation;
    }
    if (m_azimuthIndex2 == UninitializedAzimuth) {
        m_azimuthIndex2 = desiredAzimuthIndex;
        m_elevation2 = elevation;
    }

    // Cross-fade / transition over a period of around 45 milliseconds.
    // This is an empirical value tuned to be a reasonable trade-off between
    // smoothness and speed.
    const double fadeFrames = sampleRate() <= 48000 ? 2048 : 4096;

    // Check for azimuth and elevation changes, initiating a cross-fade if needed.
    if (!m_crossfadeX && m_crossfadeSelection == CrossfadeSelection1) {
        if (desiredAzimuthIndex != m_azimuthIndex1 || elevation != m_elevation1) {
            // Cross-fade from 1 -> 2
            m_crossfadeIncr = 1 / fadeFrames;
            m_azimuthIndex2 = desiredAzimuthIndex;
            m_elevation2 = elevation;
        }
    }
    if (m_crossfadeX == 1 && m_crossfadeSelection == CrossfadeSelection2) {
        if (desiredAzimuthIndex != m_azimuthIndex2 || elevation != m_elevation2) {
            // Cross-fade from 2 -> 1
            m_crossfadeIncr = -1 / fadeFrames;
            m_azimuthIndex1 = desiredAzimuthIndex;
            m_elevation1 = elevation;
        }
    }

    // This algorithm currently requires that we process in power-of-two size chunks at least RenderingQuantum.
    ASSERT(1UL << static_cast<int>(log2(framesToProcess)) == framesToProcess);
    ASSERT(framesToProcess >= RenderingQuantum);

    const unsigned framesPerSegment = RenderingQuantum;
    const unsigned numberOfSegments = framesToProcess / framesPerSegment;

    for (unsigned segment = 0; segment < numberOfSegments; ++segment) {
        // Get the HRTFKernels and interpolated delays.
        HRTFKernel* kernelL1;
        HRTFKernel* kernelR1;
        HRTFKernel* kernelL2;
        HRTFKernel* kernelR2;
        double frameDelayL1;
        double frameDelayR1;
        double frameDelayL2;
        double frameDelayR2;
        database->getKernelsFromAzimuthElevation(azimuthBlend, m_azimuthIndex1, m_elevation1, kernelL1, kernelR1, frameDelayL1, frameDelayR1);
        database->getKernelsFromAzimuthElevation(azimuthBlend, m_azimuthIndex2, m_elevation2, kernelL2, kernelR2, frameDelayL2, frameDelayR2);

        bool areKernelsGood = kernelL1 && kernelR1 && kernelL2 && kernelR2;
        ASSERT(areKernelsGood);
        if (!areKernelsGood) {
            outputBus->zero();
            return;
        }

        ASSERT(frameDelayL1 / sampleRate() < MaxDelayTimeSeconds && frameDelayR1 / sampleRate() < MaxDelayTimeSeconds);
        ASSERT(frameDelayL2 / sampleRate() < MaxDelayTimeSeconds && frameDelayR2 / sampleRate() < MaxDelayTimeSeconds);

        // Crossfade inter-aural delays based on transitions.
        double frameDelayL = (1 - m_crossfadeX) * frameDelayL1 + m_crossfadeX * frameDelayL2;
        double frameDelayR = (1 - m_crossfadeX) * frameDelayR1 + m_crossfadeX * frameDelayR2;

        // Calculate the source and destination pointers for the current segment.
        unsigned offset = segment * framesPerSegment;
        const float* segmentSourceL = sourceL + offset;
        const float* segmentSourceR = sourceR + offset;
        float* segmentDestinationL = destinationL + offset;
        float* segmentDestinationR = destinationR + offset;

        // First run through delay lines for inter-aural time difference.
        m_delayLineL.setDelayFrames(frameDelayL);
        m_delayLineR.setDelayFrames(frameDelayR);
        m_delayLineL.process(segmentSourceL, segmentDestinationL, framesPerSegment);
        m_delayLineR.process(segmentSourceR, segmentDestinationR, framesPerSegment);

        bool needsCrossfading = m_crossfadeIncr;
        
        // Have the convolvers render directly to the final destination if we're not cross-fading.
        float* convolutionDestinationL1 = needsCrossfading ? m_tempL1.data() : segmentDestinationL;
        float* convolutionDestinationR1 = needsCrossfading ? m_tempR1.data() : segmentDestinationR;
        float* convolutionDestinationL2 = needsCrossfading ? m_tempL2.data() : segmentDestinationL;
        float* convolutionDestinationR2 = needsCrossfading ? m_tempR2.data() : segmentDestinationR;

        // Now do the convolutions.
        // Note that we avoid doing convolutions on both sets of convolvers if we're not currently cross-fading.
        
        if (m_crossfadeSelection == CrossfadeSelection1 || needsCrossfading) {
            m_convolverL1.process(kernelL1->fftFrame(), segmentDestinationL, convolutionDestinationL1, framesPerSegment);
            m_convolverR1.process(kernelR1->fftFrame(), segmentDestinationR, convolutionDestinationR1, framesPerSegment);
        }

        if (m_crossfadeSelection == CrossfadeSelection2 || needsCrossfading) {
            m_convolverL2.process(kernelL2->fftFrame(), segmentDestinationL, convolutionDestinationL2, framesPerSegment);
            m_convolverR2.process(kernelR2->fftFrame(), segmentDestinationR, convolutionDestinationR2, framesPerSegment);
        }
        
        if (needsCrossfading) {
            // Apply linear cross-fade.
            float x = m_crossfadeX;
            float incr = m_crossfadeIncr;
            for (unsigned i = 0; i < framesPerSegment; ++i) {
                segmentDestinationL[i] = (1 - x) * convolutionDestinationL1[i] + x * convolutionDestinationL2[i];
                segmentDestinationR[i] = (1 - x) * convolutionDestinationR1[i] + x * convolutionDestinationR2[i];
                x += incr;
            }
            // Update cross-fade value from local.
            m_crossfadeX = x;

            if (m_crossfadeIncr > 0 && fabs(m_crossfadeX - 1) < m_crossfadeIncr) {
                // We've fully made the crossfade transition from 1 -> 2.
                m_crossfadeSelection = CrossfadeSelection2;
                m_crossfadeX = 1;
                m_crossfadeIncr = 0;
            } else if (m_crossfadeIncr < 0 && fabs(m_crossfadeX) < -m_crossfadeIncr) {
                // We've fully made the crossfade transition from 2 -> 1.
                m_crossfadeSelection = CrossfadeSelection1;
                m_crossfadeX = 0;
                m_crossfadeIncr = 0;
            }
        }
    }
}