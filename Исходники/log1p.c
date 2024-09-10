_WMRTLINK double log1p(double x)
{
double array[] = {ALNRCS1,  ALNRCS2,  ALNRCS3,  ALNRCS4,  ALNRCS5,
                  ALNRCS6,  ALNRCS7,  ALNRCS8,  ALNRCS9,  ALNRCS10,
                  ALNRCS11, ALNRCS12, ALNRCS13, ALNRCS14, ALNRCS15,
                  ALNRCS16, ALNRCS17, ALNRCS18, ALNRCS19, ALNRCS20,
                  ALNRCS21, ALNRCS22, ALNRCS23};

    if(x == -1.0)
        return XINF;
    else if(x < -1.0)
        return nan("ignore");
        
    if(fabs(x) <= 0.375) 
        return x * (1.0 - x*_Chebyshev_Evaluate(x/0.375, array, 23));
    else
        return log(1.0 + x);
}