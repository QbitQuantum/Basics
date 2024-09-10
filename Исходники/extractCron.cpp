int	extractCron::do_job(char *jobdesc)
{
	ACE_SOCK_Connector conn;
	ACE_SOCK_Stream  peer;
	ACE_Time_Value tv(3, 0);
	ACE_INET_Addr	addr(harvestPort, harvestIPaddr);
	char	urlbuff[1024];
	StrStream	httpreq;
	int	ret;

	printf("JobDesc: %s\n", jobdesc);
	CGI::escape(urlbuff, jobdesc);
	httpreq.init(2); // 2 kilobytes buff
	httpreq.rawadd("GET /harvest?expr=");
	httpreq.rawadd(urlbuff);
	httpreq.rawadd(" HTTP/1.1\n\n");

	httpreq.print();
	
	if ( conn.connect(peer, addr) < 0) {
		printf("conn failed!\n");
		return 0;
	}

	ret = peer.send( httpreq.str(), httpreq.len() );
	return 0;
	
}