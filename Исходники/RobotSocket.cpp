/*
 *  创建指定type的套接字
 * */
bool RobotSocket::create(NetType type)
{
	//创建TCP套接字
	if ((type == TCP) && ((myFD = socket(AF_INET, SOCK_STREAM, 0)) < 0))
	{
		myErrorStr = "[socket]创建TCP套接字失败";
		perror(myErrorStr.c_str());
		return(false);
	}
	//创建UDP套接字
	else if ((type == UDP) && ((myFD = socket(AF_INET, SOCK_DGRAM, 0)) < 0))
	{
		myErrorStr = "[socket]创建UDP套接字失败";
		perror(myErrorStr.c_str());
		return(false);
	}
	//保存套接字类型
	myType = type;
	//获取与该套接字关联的套接字结构体和测试该套接字是否建立有效
	if (getSockName())
		return(true);
	else
		return(false);
}