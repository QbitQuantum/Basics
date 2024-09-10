static int Xnew(XFlash *Xf,int svsock){
	Connection *Conn = Xf->xf_Conn;
	int client;
	int server;

	for(;;){
		client = ACCEPT(svsock,0,-1,0);
		server = client_open("XFlash","XCFlash","127.0.0.1",6001);
		if( server < 0 ){
			continue;
		}
		FromC = ToC = client;
		FromS = ToS = server;
		Xf->xf_cstid = thread_fork(0,0,"XFlash-CS",(IFUNCP)XCS,Xf);
		Xf->xf_sctid = thread_fork(0,0,"XFlash-SC",(IFUNCP)XSC,Xf,1024);
	}
	return 0;
}