bool UPNPNAT::tcp_connect(const char * _host,unsigned short int _port)
{
	int ret,i;
	tcp_socket_fd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in r_address;

    r_address.sin_family = AF_INET;
	r_address.sin_port=htons(_port);
    r_address.sin_addr.s_addr=inet_addr(_host);

	for(i=1;i<=time_out;i++)
	{
		if(i>1)
			_sleep(1000);

		ret=connect(tcp_socket_fd,(const struct sockaddr *)&r_address,sizeof(struct sockaddr_in) );
		if(ret==0)
		{
			status=NAT_TCP_CONNECTED;
			return true;
		}
	}

	status=NAT_ERROR;
	char temp[100];
	sprintf(temp,"Fail to connect to %s:%i (using TCP)\n",_host,_port);
	last_error=temp;

	return false;
}