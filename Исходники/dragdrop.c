short ddreply(short fd, char ack)
{
	if (Fwrite(fd, 1L, &ack) != 1L)
	{
		ddclose(fd);
		return(-1);
	}

	return(1);
}