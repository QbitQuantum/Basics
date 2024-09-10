//
// Based on ideas at:
// http://www.dsprelated.com/showarticle/42.php
//
OEVector OEVector::chebyshevWindow(OEInt n, float sidelobeDb)
{
    OEInt m = n - 1;
    
    OEVector w;
    w.data.resize(m);
    
    float alpha = coshf(acoshf(powf(10, sidelobeDb / 20)) / m);
    
    for (OEInt i = 0; i < m; i++)
    {
        float a = fabsf(alpha * cosf((float) M_PI * i / m));
        if (a > 1)
            w.data[i] = powf(-1, i) * coshf(m * acoshf(a));
        else
            w.data[i] = powf(-1, i) * cosf(m * acosf(a));
    }
    
    w = w.realIDFT();
    
    w.data.resize(n);
    w.data[0] /= 2;
    w.data[n - 1] = w.data[0];
    
    float max = 0;
    
    for (OEInt i = 0; i < n; i++)
        if (fabs(w.data[i]) > max)
            max = fabsf(w.data[i]);
    
    for (OEInt i = 0; i < n; i++)
        w.data[i] /= max;
    
    return w;
}