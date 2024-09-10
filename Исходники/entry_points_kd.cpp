KDfloat32 KD_APIENTRY Powf(KDfloat32 x, KDfloat32 y)
{
    EVENT("(KDfloat32 x = %f, KDfloat32 y = %f)", x, y);

    if (x == +1.0f || y == 0.0f)
    {
        return +1.0f;
    }
    else if (isnan(x) || isnan(y))
    {
        return NAN;
    }
    else if (x == +KD_INFINITY)
    {
        return (y > 0.0f) ? +KD_INFINITY : +0.0f;
    }
    else if (x == -KD_INFINITY)
    {
        const float r = remainderf(y, 2.0f);
        if (r == +1.0f) return -KD_INFINITY;
        if (r == -1.0f) return -0.0f;
        return (y > 0.0f) ? +KD_INFINITY : +0.0f;
    }
    else if (y == +KD_INFINITY)
    {
        if (x == -1.0f) return +1.0f;
        return (x > -1.0f && x < +1.0f) ? +0.0f : +KD_INFINITY;
    }
    else if (y == -KD_INFINITY)
    {
        if (x == -1.0f) return 1.0f;
        return (x > -1.0f && x < +1.0f) ? +KD_INFINITY : +0.0f;
    }
    else
    {
        return powf(x, y);
    }
}