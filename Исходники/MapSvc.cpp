//@brief	[MsgType:0201]进入场景
void MapSvc::ProcessEnterMap(Session& session,Packet& packet)
{
	UInt32	RetCode = 0;
	DataBuffer	serbuffer(1024);
	char szSql[1024];
	Connection con;
	DBOperate dbo;
	int iRet = 0;

	UInt32 roleID = packet.RoleID;
	UInt32 mapID = 0;
	UInt16 x;
	UInt16 y;
	UInt32 Time = 0;

	//序列化类
	Serializer s(packet.GetBuffer());
	s>>mapID>>x>>y;
	if( s.GetErrorCode()!= 0 )
	{
		RetCode = ERR_SYSTEM_SERERROR;
		LOG(LOG_ERROR,__FILE__,__LINE__,"serial error" );
		goto EndOf_Process;
	}

//DEBUG_PRINTF4( " ProcessEnterMap--roleID[%d],MapID[%d],.X[%d],.Y[%d]  \n", roleID, mapID, x, y );
	//业务处理
	iRet = _mainSvc->GetCoreData()->ProcessRoleEnterMap( roleID, mapID, x, y);
	if( iRet == -1)
	{
		RetCode = ERR_APP_OP;
		LOG(LOG_ERROR,__FILE__,__LINE__,"GetCoreData()->ProcessRoleEnterMap error");
		goto EndOf_Process;
	}
	if(iRet == 1)
	{
		RetCode = ERR_APP_ALREADYINMAP;
		LOG(LOG_ERROR,__FILE__,__LINE__,"GetCoreData()->ProcessRoleEnterMap error");
		goto EndOf_Process;

	}

EndOf_Process:
	//应答包时间字段
	Time = time(NULL);

	//组应答数据
	Packet p(&serbuffer);
	s.SetDataBuffer(&serbuffer);
	serbuffer.Reset();

	p.CopyHeader(packet);
	p.Direction = DIRECT_C_S_RESP;
	p.PackHeader();

	s<<RetCode;
	if( 0 == RetCode )
	{//RetCode 为0 才会返回包体剩下内容
		s<<Time;
	}

	p.UpdatePacketLength();

	//发送应答数据
	if( session.Send(&serbuffer) )
	{
		LOG(LOG_ERROR, __FILE__, __LINE__, "session->Send() error,errno[%d],strerror[%s]", errno, strerror(errno) );
	}

//DEBUG_PRINTF1( "C_S ack pkg ----- MsgType[%d]  \n", packet.MsgType );
//	DEBUG_SHOWHEX( serbuffer.GetReadPtr(), serbuffer.GetDataSize(), 0, __FILE__, __LINE__ );
	if(RetCode==0)
	{
		RolePtr pRole=_mainSvc->GetCoreData()->ProcessGetRolePtr(roleID);
		//[MsgType:0202]（单播）进入场景，场景所有其他角色的列表
		_mainSvc->GetCoreData()->NotifyAllRoleInfo(roleID);

		//s-c205进入地图
		//NotifyEnterMap(roleID,mapID,x,y);
		if(pRole->TeamFlag()==1)
		{
			NotifyTeamLeader(roleID,pRole->LeaderRoleID());
		}

 LOG(LOG_DEBUG,__FILE__,__LINE__,"ProcessEnterMap OK!!roleID[%d],mapID[%d], EnterMapNum[%d]", pRole->ID(), mapID, pRole->EnterMapNum());

		//角色登陆进地图的未完成的挂机数据
		_mainSvc->GetOffLineUpdateSvc()->OnRoleLoginNotify(roleID);

		if(pRole->EnterMapNum() == 1)
		{
			//角色登录的符文使用数据
		    List<RoleRune> lic;
		    pRole->PopulateRoleRuneList(lic);

			if(lic.size()>0){
				NotifyActRuneListOnLogin(roleID, lic);
			}
		}
	}

	return;
}