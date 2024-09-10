float asincosf(const float x, const int isacos)
{
    float y, g, r;
    int i;

    static myconst float a[2]={ 0.0, QUART_PI };
    static myconst float b[2]={ HALF_PI, QUART_PI };

    y=fabsf(x);
    i=isacos;
    if (y < EPS) r=y;
    else
    {
        if (y > 0.5)
        {
            i=1-i;
            if (y > 1.0)
            {
                errno=EDOM;
                return 0.0;
            }
            g=(0.5-y)+0.5;
            g=ldexpf(g,-1);
            y=sqrtf(g);
            y=-(y+y);
        }
        else
        {
            g=y*y;
        }
        r=y+y*((P(g)*g)/Q(g));
    }
    if (isacos)
    {
        if (x < 0.0)
            r=(b[i]+r)+b[i];
        else
            r=(a[i]-r)+a[i];
    }
    else
    {
        r=(a[i]+r)+a[i];
        if (x<0.0) r=-r;
    }
    return r;
}