float nextafterf(const float x, const float y)
{
    int origexp, newexp;
#ifdef isnan
    if (isnan(x) || isnan(y))
        return x + y;
#endif
    if (x == y)
        return x;
    if (x == 0.0f)
        return y > 0.0 ? FLT_MIN : -FLT_MIN;
    frexpf(x, &origexp);
    if (x >= 0.0f) {
        if (y > x) {
            if (x < FLT_MIN)
                return FLT_MIN;
            return x + scalbnf(FLT_EPSILON, origexp - 1);
        } else if (x > FLT_MIN) {
            float temp = x - scalbnf(FLT_EPSILON, origexp - 1);
            frexpf(temp, &newexp);
            if (newexp == origexp)
                return temp;
            return x - scalbnf(FLT_EPSILON, origexp - 2);
        } else
            return 0.0f;
    } else {
        if (y < x) {
            if (x > -FLT_MIN)
                return -FLT_MIN;
            return x - scalbnf(FLT_EPSILON, origexp - 1);
        } else if (x < -FLT_MIN) {
            float temp = x + scalbnf(FLT_EPSILON, origexp - 1);
            frexpf(temp, &newexp);
            if (newexp == origexp)
                return temp;
            return x + scalbnf(FLT_EPSILON, origexp - 2);
        } else
            return 0.0f;
    }
}