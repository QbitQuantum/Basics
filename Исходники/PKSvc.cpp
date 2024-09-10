void PKSvc::ProcessPKReq(Session& session,Packet& packet)
{
	UInt32	RetCode = 0;
	DataBuffer	serbuffer(1024);
	char szSql[1024];
	Connection con;
	DBOperate dbo;
	int iRet = 0;
	PKBriefList pkList;
	
	UInt32 roleID = packet.RoleID;
	Byte creatureFlag;
	UInt32 creatureID;

	ArchvRolePKInfo pkInfo;
	List<ArchvRolePKInfo> lrpki;

	UInt32 pkID = 0;
	ArchvCreatureStatus cs;
	List<ArchvCreatureStatus> lcs;
	list<TeamRole> roleIDitor; 
	list<TeamRole>::iterator itor;
	list<UInt32> roleID1,roleID2;
	list<UInt32>::iterator it;
	Team team;
	ArchvPosition posMid;
	ArchvPosition posPKOrigin;
	int iTmp = 0;
	list<SenceMonster> monsterrs; 
	list<SenceMonster>::iterator itor1;
	Byte Status=0;
	RolePtr srcRole = _mainSvc->GetCoreData()->ProcessGetRolePtr(roleID);
	RolePtr desRole;
	Monster desMonster;
	ArchvPosition pos1;
	ArchvPosition pos2;
	int pp=-1;
	int j=1;
 
	//序列化类
	Serializer s(packet.GetBuffer());
	s>>creatureFlag>>creatureID;
	if( s.GetErrorCode()!= 0 )
	{
		RetCode = ERR_SYSTEM_SERERROR;
		LOG(LOG_ERROR,__FILE__,__LINE__,"serial error" );
		goto EndOf_Process;
	}

	//获取DB连接
/*	con = _cp->GetConnection();
	dbo.SetHandle(con.GetHandle());
	*/

LOG(LOG_ERROR,__FILE__,__LINE__,"creatureFlag[%d],creatureID[%d]  ", creatureFlag, creatureID );
	
	//生物标志校验
	if( creatureFlag <=0 || creatureFlag > 4 )
	{
		RetCode = ERR_APP_DATA;
		LOG(LOG_ERROR,__FILE__,__LINE__,"creatureFlag error!! creatureFlag[%d] ", creatureFlag );
		goto EndOf_Process;
	}
	//会发生角色无法PK得状态,可以使用定时放开PK限制
	pkID=_mainSvc->GetCoreData()->IfRoleInPK(roleID);


	if(pkID!=0)
	{
		LOG(LOG_DEBUG,__FILE__,__LINE__,"111111111111 pkID=%d  roleID=%d", pkID, roleID  );
		
		RetCode = 2011;//角色的上场战斗没有结束
		LOG(LOG_ERROR,__FILE__,__LINE__,"role status error!! role is in the pk  RoleId=%d", roleID  );
		goto EndOf_Process;
	}



	if( 0 == srcRole->ID() )
	{
		RetCode = ERR_APP_ROLENOTEXISTS;
		LOG(LOG_ERROR,__FILE__,__LINE__,"ProcessGetRole error,roleID[%d]", roleID  );
		goto EndOf_Process;
	}

	
		if(srcRole->TeamFlag()==0)
		{
			//单独作战，跳过
		}
		else
		{

				if(srcRole->TeamFlag()!=2)
				{
					//失败，不是队长
					RetCode = ERR_APP_ROLENOTEXISTS;
					LOG(LOG_ERROR,__FILE__,__LINE__,"ProcessGetRole error,roleID[%d]", roleID  );
					goto EndOf_Process;
				}
				team=_mainSvc->GetCoreData()->GetTeams(srcRole->TeamID());
				roleIDitor=team.GetMemberRoleID();
				if(roleIDitor.size()>1)
				{
					//队伍的人数
						for(itor=roleIDitor.begin();itor!=roleIDitor.end();itor++)
						{
							//队伍成员
								if(itor->status==1)
								{
									//队员处于归队状态				
										roleID1.push_back(itor->roleId);
								
								}
								
						}//end for

							pkList.player1=roleID1;//队员，不包括自己
				
			 }//end if
		}//end if else

	pos1 = srcRole->Pos();

	//获取被攻击者信息
	if( 1 == creatureFlag )
	{//被攻击者为角色
	
		//获取被攻击角色的信息
		desRole = _mainSvc->GetCoreData()->ProcessGetRolePtr(creatureID);
		if( 0 == desRole->ID() )
		{
			RetCode = ERR_APP_ROLENOTEXISTS;
			LOG(LOG_ERROR,__FILE__,__LINE__,"ProcessGetRole error,creatureID[%d]", creatureID  );
			goto EndOf_Process;
		}

		//判断是否同一地图
		if( srcRole->MapID() != desRole->MapID() )
		{
			RetCode = ERR_APP_DATA;
			LOG(LOG_ERROR,__FILE__,__LINE__,"error MapID,srcRole->MapID()[%d],desRole->MapID()[%d] ", srcRole->MapID(), desRole->MapID()  );
			goto EndOf_Process;
		}
		if(desRole->TeamFlag()==0||desRole->TeamFlag()==1)
		{
			//单独作战，跳过
		}
		else
		{
				roleIDitor.clear();
				team=_mainSvc->GetCoreData()->GetTeams(desRole->TeamID());
				roleIDitor=team.GetMemberRoleID();
				if(roleIDitor.size()>1)
				{
					//队伍的人数
					for(itor=roleIDitor.begin();itor!=roleIDitor.end();itor++)
					{
						//队伍成员
							if(itor->status==1||itor->status==2)
							{
								//队员处于归队状态
								if(itor->roleId!=creatureID)
								{
									roleID2.push_back(itor->roleId);
									
								}
								
							}
							
					}
						pkList.player2=roleID2;//队员，不包括自己
				
			 }
		}
		pos2 = desRole->Pos();

	}
	else if( 2 == creatureFlag )
	{//被攻击者为怪

		//获取怪信息
		pos2=_mainSvc->GetCoreData()->GetSenceMonster(srcRole->MapID(),creatureID,monsterrs);
		if(monsterrs.size()==0)
		{
			RetCode = ERR_APP_ROLENOTEXISTS;
			LOG(LOG_ERROR,__FILE__,__LINE__,"ProcessGetMonster error,creatureID[%d]", creatureID  );
			goto EndOf_Process;
		}
		desMonster = _mainSvc->GetCoreData()->ProcessGetMonster( srcRole->MapID(), creatureID );
		if( 0 == desMonster.ID() )
		{
			RetCode = ERR_APP_ROLENOTEXISTS;
			LOG(LOG_ERROR,__FILE__,__LINE__,"ProcessGetMonster error,creatureID[%d]", creatureID  );
			goto EndOf_Process;
		}
		desMonster.ID(creatureID);
		
	}

	//获取pk 双方间直线中点坐标
  posMid = GetMidpoint( pos1, pos2 );


	//计算相对坐标原点位置
	//posPKOrigin = CalcPKOrigin( posMid );
	
LOG(LOG_DEBUG,__FILE__,__LINE__,"----------->>>>posMid x[%d],y[%d], srcRole->currPos x[%d],y[%d], desRole->currPos x[%d],y[%d], posPKOrigin x[%d],y[%d]  ",
	posMid.X, posMid.Y, pos1.X, pos1.Y, pos2.X, pos2.Y, posPKOrigin.X, posPKOrigin.Y );

	//组建 S_S pk 请求包: pk发起者
	if(pos1.X-posMid.X>0)//在右边,暂时没有获取对方的位置
	{
		pos1.X=PKSCREEN_XLENGTH/2-10;
		pos1.Y=PKSCREEN_YLENGTH/2;
	}
	else
	{
		pos1.X=PKSCREEN_XLENGTH/2+10;
		pos1.Y=PKSCREEN_YLENGTH/2;
	}
	if(roleID1.size()%2==0)
	{
		pos1.Y=pos1.Y-1;
	}
		iRet = MakeSSPkgForRole( pos1, srcRole, lrpki,1);
	
	if(iRet)
	{
		RetCode = ERR_APP_OP;
		LOG(LOG_ERROR,__FILE__,__LINE__,"MakeSSPkgForRole error!! srcRole->ID()[%d] ", srcRole->ID() );
		goto EndOf_Process;
	}
	//队伍队员

	for(it=roleID1.begin();it!=roleID1.end();it++)
	{
		pp=-1*pp;
		srcRole = _mainSvc->GetCoreData()->ProcessGetRolePtr(*it);
		if( 0 == srcRole->ID() )
		{
			RetCode = ERR_APP_ROLENOTEXISTS;
			LOG(LOG_ERROR,__FILE__,__LINE__,"ProcessGetRole error,creatureID[%d]", creatureID  );
			goto EndOf_Process;
		}
		pos1.Y=pos1.Y+2*j*pp;
		j++;
	//	posPKOrigin.X=
		iRet = MakeSSPkgForRole( pos1, srcRole, lrpki,1);
		if(iRet)
		{
			RetCode = ERR_APP_OP;
			LOG(LOG_ERROR,__FILE__,__LINE__,"MakeSSPkgForRole error!! srcRole->ID()[%d] ", srcRole->ID() );
			goto EndOf_Process;
		}
	}

	//组建 S_S pk 请求包: 被攻击者
	if( 1 == creatureFlag )
	{
			if(pos2.X-posMid.X>0)//在右边,暂时没有获取对方的位置
			{
				pos2.X=PKSCREEN_XLENGTH/2-10;
				pos2.Y=PKSCREEN_YLENGTH/2;
			}
			else
			{
				pos2.X=PKSCREEN_XLENGTH/2+10;
				pos2.Y=PKSCREEN_YLENGTH/2;
			}
		iRet = MakeSSPkgForRole(  pos2, desRole, lrpki,2); //被攻击者为角色
			 pp=-1;
			 j=1;
		for(it=roleID2.begin();it!=roleID2.end();it++)
		{
				pp=-1*pp;
				desRole = _mainSvc->GetCoreData()->ProcessGetRolePtr(*it);
				if( 0 == desRole->ID() )
				{
					RetCode = ERR_APP_ROLENOTEXISTS;
					LOG(LOG_ERROR,__FILE__,__LINE__,"ProcessGetRole error,creatureID[%d]", creatureID  );
					goto EndOf_Process;
				}
			//	posPKOrigin.X=
				pos2.Y=pos2.Y+2*j*pp;
				j++;
		
				iRet = MakeSSPkgForRole( pos1, desRole, lrpki,2);
				if(iRet)
				{
					RetCode = ERR_APP_OP;
					LOG(LOG_ERROR,__FILE__,__LINE__,"MakeSSPkgForRole error!! srcRole->ID()[%d] ", srcRole->ID() );
					goto EndOf_Process;
				}
		}
		
	}
	else if( 2 == creatureFlag )
	{
		pp=1;
		if(pos2.X-posMid.X>0)//在右边,暂时没有获取对方的位置
			{
				pos2.X=PKSCREEN_XLENGTH/2-5;
				pos2.Y=PKSCREEN_YLENGTH/2;
				pp=-1;
			}
			else
			{
				pos2.X=PKSCREEN_XLENGTH/2+5;
				pos2.Y=PKSCREEN_YLENGTH/2;
				pp=-1;
			}
    iRet = MakeSSPkgForMonster(  pos2, desMonster, lrpki,1); //怪
		UInt32 i=1;
			 j=1;
		if(monsterrs.size()>1)
		{		
				itor1=monsterrs.begin();
				itor1++;//跳过第一条数据
				for(;itor1!=monsterrs.end();itor1++)
				{		
					pos2.X=pos2.X-j*pp*2;
					 desMonster=_mainSvc->GetCoreData()->ProcessGetMonster( desMonster.MapID(), itor1->MonsterType);
						desMonster.ID(creatureID+i);
						iRet = MakeSSPkgForMonster(  pos2, desMonster, lrpki,itor1->num); //怪
						i=itor1->num+i;
				}
	  }
	}
	if(iRet)
	{
		RetCode = ERR_APP_OP;
		LOG(LOG_ERROR,__FILE__,__LINE__,"MakeSSPkgForRole error!! desRole->ID()[%d] ", desRole->ID() );
		goto EndOf_Process;
	}


	
	//pk 拉人功能，根据组队、坐标范围来拉人进入pk

	pkID=roleID;

	pkList.player1.push_back(roleID);//队员，不包括自己
	pkList.player2.push_back(creatureID);//队员，不包括自己
	pkList.pkID=pkID;
	_mainSvc->GetCoreData()->AddPKBrif(pkID,pkList);

	//ss 消息处理
	
	Status=_mainSvc->GetCoreData()->ProcessGetRolePtr(roleID)->Status();
	if(Status!=1)
	{
		RetCode = ERR_APP_ROLENOTEXISTS;
		LOG(LOG_ERROR,__FILE__,__LINE__,"ProcessGetRole error,roleID[%d]", roleID  );
		goto EndOf_Process;
	}
	else
	{
		srcRole->Status(2);
	}
	iRet = _mainSvc->GetSSClientManager()->ProcessPkReq( srcRole->MapID(), posMid.X, posMid.Y, lrpki, pkID);
	if(iRet)
	{
		RetCode = iRet;
		LOG(LOG_ERROR,__FILE__,__LINE__,"ProcessPkReq error ,RetCode[%d]", RetCode );		
		goto EndOf_Process;
	}

	
EndOf_Process:

	//状态的重置
	if(RetCode)
	{
		srcRole->Status(1);		//重置为非pk状态
		_mainSvc->GetCoreData()->EraseRolePKID(roleID);				//删除 PKID

		LOG(LOG_DEBUG,__FILE__,__LINE__,"222222222 _mainSvc->GetCoreData()->IfRoleInPK(roleID) [%d]", _mainSvc->GetCoreData()->IfRoleInPK(roleID) );
	}

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
//		s<<11;
	}	

	p.UpdatePacketLength();
	
	//发送应答数据
	if( session.Send(&serbuffer) )
	{
		LOG(LOG_ERROR,__FILE__,__LINE__,"session.Send error ");
	}
	
DEBUG_PRINTF1( "C_S ack pkg ----- MsgType[%d]  \n", packet.MsgType );
	DEBUG_SHOWHEX( serbuffer.GetReadPtr(), serbuffer.GetDataSize(), 0, __FILE__, __LINE__ );


	//--------------------------------------------------------------------------
	//成功处理，则修改生物状态
	if( 0 == RetCode )
	{
		GetCtStatus( lrpki, lcs );
		_mainSvc->GetCoreData()->ChangeCreatureStatus( srcRole->MapID(), lcs);
	}
		
	
}