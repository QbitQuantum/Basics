int CSocket::setReuse(bool bReuse)
{
	int iReuseAddr = 0;
    if(bReuse){
        iReuseAddr = 1;
    }

    return setSockOpt(SO_REUSEADDR, (const void *)&iReuseAddr, sizeof(int), SOL_SOCKET);
}