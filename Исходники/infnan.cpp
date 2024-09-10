int IsInf(double x)
{
#ifdef _MSC_VER  //doesn't have isinf
    int cls = _fpclass(x);
    if(cls == _FPCLASS_PINF) return 1;
    else if(cls == _FPCLASS_NINF) return -1;
    else return 0;
#elif HAVE_DECL_ISINF
    if(isinf(x)) {
        if(x > 0) return 1;
        else return -1;
    }
    else return 0;
#elif HAVE_IEEE_COMPARISONS
    double y=x-x;
    if(IsNaN(y))
        return (x>0?1:-1);
    else return 0;
#else
#error "IsInf: Neither Microsoft's _fpclass, isinf, or IEEE comparisons defined"
    return 0;
#endif
}