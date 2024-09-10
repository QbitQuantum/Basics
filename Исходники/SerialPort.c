/*!
@brief get a char from driver, blocking mode.
*/
unsigned char GetChar_proc(struct _SerialPort *thisport)
{
#ifndef WIN32	
	unsigned char byte;
	int res, tmp;
	
	while ( (res = ReadPort(thisport->m_fd, &byte, 1, &tmp)) != SUCCESS ) ; 

	return byte;
	
#else
	return thisport->debugbuf[thisport->debugii++];
#endif
} 