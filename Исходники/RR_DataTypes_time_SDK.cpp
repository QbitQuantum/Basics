_rrTime _rrTime::convertStatFileTime(const time_t &tim)
{
    if (rrTime_Start_OffSet==-1) testIfOfsetIsRight(true);
    _rrTime ret;
    ret.value=tim;
    tm conv1;
    ret.to_tm(conv1);
    ret.value=_mkgmtime64(&conv1)-rrTime_Start_OffSet;
    return ret;
}