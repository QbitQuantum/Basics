static float RdIntegral(float alphap, float A) {
    float sqrtTerm = sqrtf(3.f * (1.f - alphap));
    return alphap / 2.f * (1.f + expf(-4.f/3.f * A * sqrtTerm)) *
        expf(-sqrtTerm);
}