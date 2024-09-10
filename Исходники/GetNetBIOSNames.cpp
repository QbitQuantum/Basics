// 获取指定LANA的网络适配器信息
// nLana, LANA编号
// pBuffer, 获取到的网络适配器缓冲区
// cbBuffer, 缓冲区长度
// szName, 主机名字
BOOL NBAdapterStatus (int nLana, PVOID pBuffer, int cbBuffer,  LPCSTR szName)
{
    NCB ncb;
    memset (&ncb, 0, sizeof (ncb));		// 清空ncb结构体
    ncb.ncb_command = NCBASTAT;			// 设置执行NCBASTAT命令，获取本地或远程网络适配器的状态
    ncb.ncb_lana_num = nLana;			// 设置LANA编号

    ncb.ncb_buffer = (PUCHAR) pBuffer;	// 将获取到的数据保存到参数pBuffer中
    ncb.ncb_length = cbBuffer;			// 设置缓冲区长度

    MakeNetbiosName ((char*) ncb.ncb_callname, szName);// 设置参数ncb.ncb_callname
    Netbios (&ncb);						// 执行NetBIOS命令
    NBCheck (ncb);						// 如果执行不成功，则输出返回值
	// 如果成功返回TRUE，否则返回FALSE
    return (NRC_GOODRET == ncb.ncb_retcode);
}