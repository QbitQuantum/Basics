UCHAR __GetAddressByIndex(int lana_num, ASTAT &Adapter)
{
	NCB ncb;
	UCHAR uRetCode;
	memset(&ncb, 0, sizeof(ncb) );
	ncb.ncb_command = NCBRESET;
	ncb.ncb_lana_num = lana_num;
	//指定网卡号,首先对选定的网卡发送一个NCBRESET命令,以便进行初始化
	uRetCode = Netbios(&ncb );
	memset(&ncb, 0, sizeof(ncb) );
	ncb.ncb_command = NCBASTAT;
	ncb.ncb_lana_num = lana_num;   //指定网卡号
	strcpy((char *)ncb.ncb_callname,"*      " );
	ncb.ncb_buffer = (unsigned char *)&Adapter;
	//指定返回的信息存放的变量
	ncb.ncb_length = sizeof(Adapter);
	//接着,可以发送NCBASTAT命令以获取网卡的信息
	uRetCode = Netbios(&ncb );
	return uRetCode;
}