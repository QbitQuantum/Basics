// Windows Vista doesn't support the NO_REPEAT_FLAG
UINT Timer::getNoRepeatFlag() const
{
    UINT flag = 0x0000;
    if (IsWindows7OrGreater()) {
        flag = 0x4000;
    }
    return flag;
}