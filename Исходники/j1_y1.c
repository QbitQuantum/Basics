/*
 * @implemented
 */
double _y1(double num)
{
    double retval;
    int fpclass = _fpclass(num);

    if (!_finite(num) || fpclass == _FPCLASS_NN ||
            fpclass == _FPCLASS_ND || fpclass == _FPCLASS_NZ)
        *_errno() = EDOM;

    retval  = __ieee754_y1(num);
    if (_fpclass(retval) == _FPCLASS_NINF)
    {
        *_errno() = EDOM;
        retval = sqrt(-1);
    }
    return retval;
}