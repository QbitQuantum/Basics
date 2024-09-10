inline float score_student_t (
        float x,
        float nu,
        float mu,
        float lambda)
{
    // \cite{murphy2007conjugate}, Eq. 304
    float p = lgammaf(nu * 0.5f + 0.5f) - lgammaf(nu * 0.5f);
    p += 0.5f * logf(lambda / (M_PIf * nu));
    p += (-0.5f * nu - 0.5f) * logf(1.f + (lambda * sqr(x - mu)) / nu);
    return p;
}