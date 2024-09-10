BOOL IsFloatValid(float f)
{
#ifdef _WIN32
    int lnResult = _fpclass(f);
    switch (lnResult)
    {
    case _FPCLASS_SNAN:
    case _FPCLASS_QNAN:
    case _FPCLASS_NINF:
    case _FPCLASS_ND:
    case _FPCLASS_PD:
    case _FPCLASS_PINF:
        return FALSE;
        break;
    default:
        return TRUE;
    }
#else

    return TRUE;

#endif // _WIN32

}