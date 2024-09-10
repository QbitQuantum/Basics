float expf(float x)
{
    int n;
    float xn, g, r, z, y;
    char sign;

    if(x>=0.0)
    {
        y=x;
        sign=0;
    }
    else
    {
        y=-x;
        sign=1;
    }

    if(y<EXPEPS) return 1.0;

    if(y>BIGX)
    {
        if(sign)
        {
            errno=ERANGE;
            return XMAX;
        }
        else
        {
            return 0.0;
        }
    }

    z=y*K1;
    n=z;

    if(n<0) --n;
    if(z-n>=0.5) ++n;
    xn=n;
    g=((y-xn*C1))-xn*C2;
    z=g*g;
    r=P(z)*g;
    r=0.5+(r/(Q(z)-r));

    n++;
    z=ldexpf(r, n);
    if(sign)
        return 1.0/z;
    else
        return z;
}