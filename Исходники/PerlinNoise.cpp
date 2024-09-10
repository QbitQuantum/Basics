// パーリンノイズ算出
float PerlinNoise2D::Noise(float x, float y)
{
#if 0
    int ix = int(x) & 255;
    int iy = int(y) & 255;
    float fx = x - int(x);
    float fy = y - int(y);
    float ret;
    
    if (interpType_ == Interp_Cubic)
    {
        float w[4];
        for (int i = 0; i < 4; i++) {
            float v0 = IntNoise(ix-1, iy-1 + i);
            float v1 = IntNoise(ix,   iy-1 + i);
            float v2 = IntNoise(ix+1, iy-1 + i);
            float v3 = IntNoise(ix+2, iy-1 + i);
            w[i] = CubicInterporate(v0, v1, v2, v3, fx);
        }
        ret = CubicInterporate(w[0], w[1], w[2], w[3], fy);
    }
    else
    {
        printf("%d %d %f %f\n", ix, iy, fx, fy);
        const float to0_1 = 1.f / 255.f;
        int A = permutation_[ix  ] + iy;
        int B = permutation_[ix+1] + iy;
        float v0 = permutation_[A] * to0_1;
        float v1 = permutation_[B] * to0_1;
        float v2 = permutation_[A+1] * to0_1;
        float v3 = permutation_[B+1] * to0_1;
        float (*fade)(float) = pFadeFuncs[interpType_];
        float f = fade(fx);
        v0 = Lerp(v0, v1, f);
        v1 = Lerp(v2, v3, f);
        ret = Lerp(v0, v1, fade(fy));
    }
    return ret;
#else
    float ret = (float)noise(x, y, 0);
    //printf("%f\n", ret);
    return ret;
#endif
}