int strcoll (const char* s1,const char* s2)
{
    int ret;
    ret = CompareStringA(LOCALE_USER_DEFAULT,0,s1,strlen(s1),s2,strlen(s2));
    if (ret == 0)
        return 0;
    else
        return ret - 2;
    return 0;
}