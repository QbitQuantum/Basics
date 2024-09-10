disp_gcvt(double dblIn, int ndigits, OLECHAR FAR* pchOut, int bufSize)
{
    char buf[40];

    _gcvt(dblIn, ndigits, buf);
    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, buf, -1, pchOut, bufSize);
}