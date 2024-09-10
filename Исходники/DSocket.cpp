/**
*      Send the VIDEO data to remote host
*
*/
void DSocket::SendVideoData(unsigned char *data,int length)
{

// Better to attach video header....
// If dynamic format is supported...
SendTo(data,length,PORT_VIDEO,remoteaddress);
	
}