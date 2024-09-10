void cmdSysInfo( CClientSession* pSession )
{
	SERVERINFO sysinfo;
	if( pSession->ServerInfo( sysinfo ) ){
		cout<<GetHostByAddr(sysinfo.ipAddr)<<endl<<"OS:"<<sysinfo.nOpSystem<<"\t"<<"DISK:"<<sysinfo.bShareDisk<<"\t"<<"STAT:"<<sysinfo.nSysStat<<endl;
		cout<<"SESS:"<<sysinfo.nSessions<<"\t"<<"PROC:"<<sysinfo.nChildPorcs<<"\tIDLE:"<<sysinfo.bSysIdle<<endl;
	}else{
		cout<<"\tcmd failed"<<endl;
	}
}