int sc_fpclassify(float x) {
    int result;
    int kind = _fpclass((double)x);
    switch (kind)
    {
    case _FPCLASS_NINF:
        result = FP_INFINITE;
        break;
    case _FPCLASS_PINF:
        result = FP_INFINITE;
        break;
    case _FPCLASS_SNAN:
        result = FP_NAN;
        break;
    case _FPCLASS_QNAN:
        result = FP_NAN;
        break;
    case _FPCLASS_ND:
        result = FP_SUBNORMAL;
        break;
    case _FPCLASS_PD:
        result = FP_SUBNORMAL;
        break;
    default:
        result = FP_NORMAL;
    };
    return result;

}