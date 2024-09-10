unsigned int getLocalTime() {
    //watchout for 23:59:59.999 -> 0:0:0.000
    SYSTEMTIME now;
    GetSystemTime(&now);
    return(((now.wHour * 60 + now.wMinute) * 60 + now.wSecond) * 1000 + now.wMilliseconds);
}