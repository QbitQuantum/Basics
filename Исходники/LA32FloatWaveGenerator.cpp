float LA32WaveGenerator::generateNextSample(const Bit32u ampVal, const Bit16u pitch, const Bit32u cutoffRampVal) {
    if (!active) {
        return 0.0f;
    }

    this->amp = amp;
    this->pitch = pitch;

    float sample = 0.0f;

    // SEMI-CONFIRMED: From sample analysis:
    // (1) Tested with a single partial playing PCM wave 77 with pitchCoarse 36 and no keyfollow, velocity follow, etc.
    // This gives results within +/- 2 at the output (before any DAC bitshifting)
    // when sustaining at levels 156 - 255 with no modifiers.
    // (2) Tested with a special square wave partial (internal capture ID tva5) at TVA envelope levels 155-255.
    // This gives deltas between -1 and 0 compared to the real output. Note that this special partial only produces
    // positive amps, so negative still needs to be explored, as well as lower levels.
    //
    // Also still partially unconfirmed is the behaviour when ramping between levels, as well as the timing.

    float amp = EXP2F(ampVal / -1024.0f / 4096.0f);
    float freq = EXP2F(pitch / 4096.0f - 16.0f) * SAMPLE_RATE;

    if (isPCMWave()) {
        // Render PCM waveform
        int len = pcmWaveLength;
        int intPCMPosition = (int)pcmPosition;
        if (intPCMPosition >= len && !pcmWaveLooped) {
            // We're now past the end of a non-looping PCM waveform so it's time to die.
            deactivate();
            return 0.0f;
        }
        float positionDelta = freq * 2048.0f / SAMPLE_RATE;

        // Linear interpolation
        float firstSample = getPCMSample(intPCMPosition);
        // We observe that for partial structures with ring modulation the interpolation is not applied to the slave PCM partial.
        // It's assumed that the multiplication circuitry intended to perform the interpolation on the slave PCM partial
        // is borrowed by the ring modulation circuit (or the LA32 chip has a similar lack of resources assigned to each partial pair).
        if (pcmWaveInterpolated) {
            sample = firstSample + (getPCMSample(intPCMPosition + 1) - firstSample) * (pcmPosition - intPCMPosition);
        } else {
            sample = firstSample;
        }

        float newPCMPosition = pcmPosition + positionDelta;
        if (pcmWaveLooped) {
            newPCMPosition = fmod(newPCMPosition, (float)pcmWaveLength);
        }
        pcmPosition = newPCMPosition;
    } else {
        // Render synthesised waveform
        wavePos *= lastFreq / freq;
        lastFreq = freq;

        float resAmp = EXP2F(1.0f - (32 - resonance) / 4.0f);
        {
            //static const float resAmpFactor = EXP2F(-7);
            //resAmp = EXP2I(resonance << 10) * resAmpFactor;
        }

        // The cutoffModifier may not be supposed to be directly added to the cutoff -
        // it may for example need to be multiplied in some way.
        // The 240 cutoffVal limit was determined via sample analysis (internal Munt capture IDs: glop3, glop4).
        // More research is needed to be sure that this is correct, however.
        float cutoffVal = cutoffRampVal / 262144.0f;
        if (cutoffVal > MAX_CUTOFF_VALUE) {
            cutoffVal = MAX_CUTOFF_VALUE;
        }

        // Wave length in samples
        float waveLen = SAMPLE_RATE / freq;

        // Init cosineLen
        float cosineLen = 0.5f * waveLen;
        if (cutoffVal > MIDDLE_CUTOFF_VALUE) {
            cosineLen *= EXP2F((cutoffVal - MIDDLE_CUTOFF_VALUE) / -16.0f); // found from sample analysis
        }

        // Start playing in center of first cosine segment
        // relWavePos is shifted by a half of cosineLen
        float relWavePos = wavePos + 0.5f * cosineLen;
        if (relWavePos > waveLen) {
            relWavePos -= waveLen;
        }

        // Ratio of positive segment to wave length
        float pulseLen = 0.5f;
        if (pulseWidth > 128) {
            pulseLen = EXP2F((64 - pulseWidth) / 64.0f);
            //static const float pulseLenFactor = EXP2F(-192 / 64);
            //pulseLen = EXP2I((256 - pulseWidthVal) << 6) * pulseLenFactor;
        }
        pulseLen *= waveLen;

        float hLen = pulseLen - cosineLen;

        // Ignore pulsewidths too high for given freq
        if (hLen < 0.0f) {
            hLen = 0.0f;
        }

        // Ignore pulsewidths too high for given freq and cutoff
        float lLen = waveLen - hLen - 2 * cosineLen;
        if (lLen < 0.0f) {
            lLen = 0.0f;
        }

        // Correct resAmp for cutoff in range 50..66
        if ((cutoffVal >= 128.0f) && (cutoffVal < 144.0f)) {
            resAmp *= sin(FLOAT_PI * (cutoffVal - 128.0f) / 32.0f);
        }

        // Produce filtered square wave with 2 cosine waves on slopes

        // 1st cosine segment
        if (relWavePos < cosineLen) {
            sample = -cos(FLOAT_PI * relWavePos / cosineLen);
        } else

            // high linear segment
            if (relWavePos < (cosineLen + hLen)) {
                sample = 1.f;
            } else

                // 2nd cosine segment
                if (relWavePos < (2 * cosineLen + hLen)) {
                    sample = cos(FLOAT_PI * (relWavePos - (cosineLen + hLen)) / cosineLen);
                } else {

                    // low linear segment
                    sample = -1.f;
                }

        if (cutoffVal < 128.0f) {

            // Attenuate samples below cutoff 50
            // Found by sample analysis
            sample *= EXP2F(-0.125f * (128.0f - cutoffVal));
        } else {

            // Add resonance sine. Effective for cutoff > 50 only
            float resSample = 1.0f;

            // Resonance decay speed factor
            float resAmpDecayFactor = Tables::getInstance().resAmpDecayFactor[resonance >> 2];

            // Now relWavePos counts from the middle of first cosine
            relWavePos = wavePos;

            // negative segments
            if (!(relWavePos < (cosineLen + hLen))) {
                resSample = -resSample;
                relWavePos -= cosineLen + hLen;

                // From the digital captures, the decaying speed of the resonance sine is found a bit different for the positive and the negative segments
                resAmpDecayFactor += 0.25f;
            }

            // Resonance sine WG
            resSample *= sin(FLOAT_PI * relWavePos / cosineLen);

            // Resonance sine amp
            float resAmpFadeLog2 = -0.125f * resAmpDecayFactor * (relWavePos / cosineLen); // seems to be exact
            float resAmpFade = EXP2F(resAmpFadeLog2);

            // Now relWavePos set negative to the left from center of any cosine
            relWavePos = wavePos;

            // negative segment
            if (!(wavePos < (waveLen - 0.5f * cosineLen))) {
                relWavePos -= waveLen;
            } else

                // positive segment
                if (!(wavePos < (hLen + 0.5f * cosineLen))) {
                    relWavePos -= cosineLen + hLen;
                }

            // To ensure the output wave has no breaks, two different windows are appied to the beginning and the ending of the resonance sine segment
            if (relWavePos < 0.5f * cosineLen) {
                float syncSine = sin(FLOAT_PI * relWavePos / cosineLen);
                if (relWavePos < 0.0f) {
                    // The window is synchronous square sine here
                    resAmpFade *= syncSine * syncSine;
                } else {
                    // The window is synchronous sine here
                    resAmpFade *= syncSine;
                }
            }

            sample += resSample * resAmp * resAmpFade;
        }

        // sawtooth waves
        if (sawtoothWaveform) {
            sample *= cos(FLOAT_2PI * wavePos / waveLen);
        }

        wavePos++;

        // wavePos isn't supposed to be > waveLen
        if (wavePos > waveLen) {
            wavePos -= waveLen;
        }
    }

    // Multiply sample with current TVA value
    sample *= amp;
    return sample;
}