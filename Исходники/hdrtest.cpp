Surface process(const Surface & src, int method) {
    Surface dst;

    float rMin, rMax, gMin, gMax, bMin, bMax;
    src.range(0, &rMin, &rMax);
    src.range(1, &gMin, &gMax);
    src.range(2, &bMin, &bMax);

    if (method == 0) {
        // Only clamp.
        dst = src;

        dst.scaleBias(0, 1.0f / 4, 0);
        dst.scaleBias(1, 1.0f / 4, 0);
        dst.scaleBias(2, 1.0f / 4, 0);

        dst.clamp(0, 0, 1);
        dst.clamp(1, 0, 1);
        dst.clamp(2, 0, 1);

        dst.toGamma(0, 2);
        dst.toGamma(1, 2);
        dst.toGamma(2, 2);

        dst.quantize(0, 10, /*exactEndPoints*/true, false);
        dst.quantize(1, 10, /*exactEndPoints*/true, false);
        dst.quantize(2, 10, /*exactEndPoints*/true, false);

        dst.toLinear(0, 2);
        dst.toLinear(1, 2);
        dst.toLinear(2, 2);

        dst.scaleBias(0, 4, 0);
        dst.scaleBias(1, 4, 0);
        dst.scaleBias(2, 4, 0);
    }
    else if (method == 1) {
        // Scale and bias. Use full range.
        dst = src;

        float gamma = 3;

        dst.scaleBias(0, 1.0f / rMax, 0);
        dst.scaleBias(1, 1.0f / gMax, 0);
        dst.scaleBias(2, 1.0f / bMax, 0);

        dst.clamp(0, 0, 1);
        dst.clamp(1, 0, 1);
        dst.clamp(2, 0, 1);

        dst.toGamma(0, gamma);
        dst.toGamma(1, gamma);
        dst.toGamma(2, gamma);

        dst.quantize(0, 10, /*exactEndPoints*/true, false);
        dst.quantize(1, 10, /*exactEndPoints*/true, false);
        dst.quantize(2, 10, /*exactEndPoints*/true, false);

        dst.toLinear(0, gamma);
        dst.toLinear(1, gamma);
        dst.toLinear(2, gamma);

        dst.scaleBias(0, rMax, 0);
        dst.scaleBias(1, gMax, 0);
        dst.scaleBias(2, bMax, 0);
    }
    else if (method == 2) {
        // Scale and bias. Use full range.
        dst = src;

        // @@ Experiment with log/exp transform!
        float gamma = 2.2f;

        dst.scaleBias(0, 1.0f / rMax, 0);
        dst.scaleBias(1, 1.0f / gMax, 0);
        dst.scaleBias(2, 1.0f / bMax, 0);

        dst.clamp(0, 0, 1);
        dst.clamp(1, 0, 1);
        dst.clamp(2, 0, 1);

        //dst.toGamma(0, gamma);
        //dst.toGamma(1, gamma);
        //dst.toGamma(2, gamma);
        dst.toLogScale(0, 2);
        dst.toLogScale(1, 2);
        dst.toLogScale(2, 2);

        dst.quantize(0, 10, /*exactEndPoints*/true, false);
        dst.quantize(1, 10, /*exactEndPoints*/true, false);
        dst.quantize(2, 10, /*exactEndPoints*/true, false);

        dst.fromLogScale(0, 2);
        dst.fromLogScale(1, 2);
        dst.fromLogScale(2, 2);

        //dst.toLinear(0, gamma);
        //dst.toLinear(1, gamma);
        //dst.toLinear(2, gamma);

        dst.scaleBias(0, rMax, 0);
        dst.scaleBias(1, gMax, 0);
        dst.scaleBias(2, bMax, 0);
    }
    else if (method == 3) {
        // Scale and bias. Use full range.
        dst = src;

        // @@ Experiment with log/exp transform!
        float gamma = 0.5;

        dst.scaleBias(0, 1.0f / rMax, 0);
        dst.scaleBias(1, 1.0f / gMax, 0);
        dst.scaleBias(2, 1.0f / bMax, 0);

        dst.clamp(0, 0, 1);
        dst.clamp(1, 0, 1);
        dst.clamp(2, 0, 1);

        dst.toGamma(0, gamma);
        dst.toGamma(1, gamma);
        dst.toGamma(2, gamma);

        dst.toLogScale(0, 2);
        dst.toLogScale(1, 2);
        dst.toLogScale(2, 2);

        dst.quantize(0, 8, /*exactEndPoints*/true, false);
        dst.quantize(1, 8, /*exactEndPoints*/true, false);
        dst.quantize(2, 8, /*exactEndPoints*/true, false);

        dst.fromLogScale(0, 2);
        dst.fromLogScale(1, 2);
        dst.fromLogScale(2, 2);

        dst.toLinear(0, gamma);
        dst.toLinear(1, gamma);
        dst.toLinear(2, gamma);

        dst.scaleBias(0, rMax, 0);
        dst.scaleBias(1, gMax, 0);
        dst.scaleBias(2, bMax, 0);
    }

    return dst;
}