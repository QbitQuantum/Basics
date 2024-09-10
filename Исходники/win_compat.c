struct tm * localtime_r_win32(long *clock,struct tm * res)
{
    _localtime32_s(res,clock);
    return(res);
}