ChighPerformanceTimer::ChighPerformanceTimer(CString p_TimerName,bool p_Periodic,LONG p_Period)
{
// 	p_TimerName 定时器名；
// 	p_Periodic 设置是否为周期性定时器；
// 	p_Period时钟周期
	g_Valid=false;
	if (p_Periodic)
	{
		g_TimerPeriod=p_Period;
		g_ManualReset=false;
	}
	else
	{
		g_TimerPeriod=0;
		g_ManualReset=true;
	}
	g_Set=false;
	g_TimerExpires.QuadPart=Int32x32To64(-10000,p_Period);
	memset(g_Name,0,MAX_PATH);
	if (! p_TimerName.IsEmpty())
		if(p_TimerName.GetLength()>MAX_PATH)
			memcpy(g_Name,p_TimerName,MAX_PATH);
		else
			memcpy(g_Name,p_TimerName,p_TimerName.GetLength());
		//如果定时器已经创建， 则使用已有的定时器；否则建立一个新的定时器
		g_TimerHandle=OpenWaitableTimer(TIMER_ALL_ACCESS | TIMER_MODIFY_STATE | SYNCHRONIZE,TRUE,(char *) g_Name);
		if (g_TimerHandle==NULL)
		{
			//建立并且初始化缺省的安全描述符和属性
			g_SecurityAttributes.lpSecurityDescriptor=&g_SecurityDescriptor;
			InitializeSecurityDescriptor(g_SecurityAttributes.lpSecurityDescriptor,SECURITY_DESCRIPTOR_REVISION);
			SetSecurityDescriptorDacl(g_SecurityAttributes.lpSecurityDescriptor,TRUE,(PACL)NULL,FALSE);
			g_SecurityAttributes.nLength = sizeof SECURITY_ATTRIBUTES;
			g_SecurityAttributes.bInheritHandle=TRUE;
			g_TimerHandle=CreateWaitableTimer(&g_SecurityAttributes,g_ManualReset,(char *)g_Name);
		}
		if(g_TimerHandle==NULL)
		{
			//ERROR AND RETURN
			return;
		}
		g_Result=g_WaitableTimer_TickOkay;//?????????
		g_Valid=true;
}