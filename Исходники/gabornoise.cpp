    GaborParams (const NoiseParams &opt) :
        omega(opt.direction),  // anisotropy orientation
        anisotropic(opt.anisotropic),
        do_filter(opt.do_filter),
        weight(Gabor_Impulse_Weight),
        bandwidth(Imath::clamp(opt.bandwidth,0.01f,100.0f)),
        periodic(false)
    {
#if OSL_FAST_MATH
        float TWO_to_bandwidth = OIIO::fast_exp2(bandwidth);
#else
        float TWO_to_bandwidth = exp2f(bandwidth);
#endif
        static const float SQRT_PI_OVER_LN2 = sqrtf (M_PI / M_LN2);
        a = Gabor_Frequency * ((TWO_to_bandwidth - 1.0) / (TWO_to_bandwidth + 1.0)) * SQRT_PI_OVER_LN2;
        // Calculate the maximum radius from which we consider the kernel
        // impulse centers -- derived from the threshold and bandwidth.
        radius = sqrtf(-logf(Gabor_Truncate) / float(M_PI)) / a;
        radius2 = radius * radius;
        radius3 = radius2 * radius;
        radius_inv = 1.0f / radius;
        // Lambda is the impulse density.
        float impulses = Imath::clamp (opt.impulses, 1.0f, 32.0f);
        lambda = impulses / (float(1.33333 * M_PI) * radius3);
        sqrt_lambda_inv = 1.0f / sqrtf(lambda);
    }