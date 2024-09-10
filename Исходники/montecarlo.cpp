void LDPixelSample(int xPos, int yPos, float shutterOpen,
                   float shutterClose, int nPixelSamples, Sample *samples, float *buf,
                   RNG &rng) {
    // Prepare temporary array pointers for low-discrepancy camera samples
    float *imageSamples = buf;
    buf += 2 * nPixelSamples;
    float *lensSamples = buf;
    buf += 2 * nPixelSamples;
    float *timeSamples = buf;
    buf += nPixelSamples;

    // Prepare temporary array pointers for low-discrepancy integrator samples
    uint32_t count1D = samples[0].n1D.size();
    uint32_t count2D = samples[0].n2D.size();
    const uint32_t *n1D = count1D > 0 ? &samples[0].n1D[0] : NULL;
    const uint32_t *n2D = count2D > 0 ? &samples[0].n2D[0] : NULL;
    float **oneDSamples = ALLOCA(float *, count1D);
    float **twoDSamples = ALLOCA(float *, count2D);
    for (uint32_t i = 0; i < count1D; ++i) {
        oneDSamples[i] = buf;
        buf += n1D[i] * nPixelSamples;
    }
    for (uint32_t i = 0; i < count2D; ++i) {
        twoDSamples[i] = buf;
        buf += 2 * n2D[i] * nPixelSamples;
    }

    // Generate low-discrepancy pixel samples
    LDShuffleScrambled2D(1, nPixelSamples, imageSamples, rng);
    LDShuffleScrambled2D(1, nPixelSamples, lensSamples, rng);
    LDShuffleScrambled1D(1, nPixelSamples, timeSamples, rng);
    for (uint32_t i = 0; i < count1D; ++i)
        LDShuffleScrambled1D(n1D[i], nPixelSamples, oneDSamples[i], rng);
    for (uint32_t i = 0; i < count2D; ++i)
        LDShuffleScrambled2D(n2D[i], nPixelSamples, twoDSamples[i], rng);

    // Initialize _samples_ with computed sample values
    for (int i = 0; i < nPixelSamples; ++i) {
        samples[i].imageX = xPos + imageSamples[2*i];
        samples[i].imageY = yPos + imageSamples[2*i+1];
        samples[i].time = Lerp(timeSamples[i], shutterOpen, shutterClose);
        samples[i].lensU = lensSamples[2*i];
        samples[i].lensV = lensSamples[2*i+1];
        // Copy integrator samples into _samples[i]_
        for (uint32_t j = 0; j < count1D; ++j) {
            int startSamp = n1D[j] * i;
            for (uint32_t k = 0; k < n1D[j]; ++k)
                samples[i].oneD[j][k] = oneDSamples[j][startSamp+k];
        }
        for (uint32_t j = 0; j < count2D; ++j) {
            int startSamp = 2 * n2D[j] * i;
            for (uint32_t k = 0; k < 2*n2D[j]; ++k)
                samples[i].twoD[j][k] = twoDSamples[j][startSamp+k];
        }
    }
}