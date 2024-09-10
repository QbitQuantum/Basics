float sandbox_lngammaf(float _z,
                       float * _v)
{
    float v0 = _v[0];
    float v1 = _v[1];

    // z = 10.^[-3:0.1:1];
    // t0 = log(gamma(z));
    // t1 = (1+z-0.5).*log(1+z) - (1+z) + 0.5*log(2*pi) - log(z) + 0.0405*(1-tanh(0.5*log(z)));
    //
    float g_hat = (0.5f+_z)*logf(1.0f+_z) - (1.0f+_z) + 0.5f*logf(2*M_PI) - logf(_z) +
           v0*(1.0f - tanhf(v1*logf(_z)));

    return g_hat;
}