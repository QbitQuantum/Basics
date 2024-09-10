unsigned int CEvSockets::Accept(unsigned int lsocket)
{
	SOCKET polaczony;
	polaczony = accept(lsocket,(struct sockaddr *)&sinS, &rozmiarS);
	return polaczony;
}