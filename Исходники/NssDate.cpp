void NssDate::marshall()
{
    HTONL(tv_sec);
    HTONL(tv_usec);
}