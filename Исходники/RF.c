void filtering(float** channel, float** dIcdx, float** dHdyT, int h, int w, float num_iterations) {
    float N = num_iterations;

    for (int i = 1; i <= num_iterations; i++) {
        float sigma_H = sigma_s;
        float sigma_H_i = sigma_H * sqrtf(3) * exp2f(N - i) / sqrtf(powf(4, N) - 1);

        TDRF_H(channel, dIcdx, sigma_H_i, h, w);
        channel = transpose(channel, h, w);

        TDRF_H(channel, dHdyT, sigma_H_i, w, h);
        channel = transpose(channel, w, h);
    }
}