static  int  CPU_Printf (char  *p_str, ...)
{
    va_list  param;
    int      ret;


    va_start(param, p_str);
    ret = vprintf_s(p_str, param);
    va_end(param);

    return (ret);
}