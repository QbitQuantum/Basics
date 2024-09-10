//*=================================================================================
//*原型: void Dispatch(TSmartPacket& Packet)
//*功能: 分发客户请求
//*参数: 无
//*返回: 无
//*说明: 无
//*=================================================================================
void TSmartOutThread::Dispatch(SOCKET hSocket, SOCKADDR_IN *psockAddr, TSmartPacket& Packet)
{
	long i=0; 
	while(true)
	{
		if( !strcmp(Function[i].pText, "") || 
			!strcmp(Function[i].pCmd, "") || 
			Function[i].lpFunc == NULL )
		{
			break;
		}

		if( !_strcmpi(Function[i].pCmd, Packet.GetCmd()) ) 
		{ 
			try
			{
				Function[i].lpFunc(hSocket, psockAddr, &Packet, m_pServer, this);
			}
			catch(TException& e)
			{
				WriteLog(e.GetText());
			}
			catch(...)
			{
				WriteLog("执行请求处理包时发生异常,请检查程序!");
			}
			break;
		}
		i++;
	}
}