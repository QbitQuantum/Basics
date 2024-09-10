bool MgFeatureNumericFunctions::IsInf(double x)
{
    bool isInfinity = false;
#ifdef _WIN32
    int code = _fpclass(x);
    if ((code == _FPCLASS_NINF) || (code == _FPCLASS_PINF))
    {
        isInfinity = true;
    }
#else
    isInfinity = isinf(x);
#endif

    return isInfinity;
}