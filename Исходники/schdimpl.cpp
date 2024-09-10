//////////////////////////////////////////////////////////////////////////
// 下载黑名单任务
void KSGTaskDownloadBlackCard::DownloadBlackCardVisitor::Visit(KSGDeviceNode& node)
{
	//if(node.GetState() == KSGDeviceNode::dsError)
	//	return;
	dev_blkcard_info_t blk_info;
	if(!node.Accept(*this))
		return;
	DEV_BLKCARD_MAP_TYPE::const_iterator curr_iter = _dev_blkcard.find(node.GetDevId());
	if(curr_iter != _dev_blkcard.end())
	{
		blk_info = curr_iter->second;
		blk_info.sleep_times++;
		if(blk_info.last_cnt == 0)
		{
			_dev_blkcard[node.GetDevId()] = blk_info;
			int intval = KsgGetGateway()->GetConfig()->_heartbeatIntval;
			if(blk_info.sleep_times < intval)
				return;
		}
	}
	else
	{
		ACE_OS::memset(&blk_info,0,sizeof blk_info);
	}
	int count;
	char blk_buf[510];
	char max_vol[13] = "";
	static const int blk_card_cnt = 50;
	static const int card_len = 10;
	try
	{
		DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
		if(!obj)
		{
			return;
		}
		if(obj->Connect())
		{
			// 连接失败
			return;
		}
		obj->SetRequestHeader(950007);
		obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
		obj->AddField(F_SCUST_LIMIT2,KsgGetGateway()->GetConfig()->_dynaKey.c_str());
		obj->AddField(F_LVOL1,blk_card_cnt);
		obj->AddField(F_LVOL5,node.GetDevId());
		if(obj->SendRequest(5000))
		{
			// 发送指令失败
			KSGThreadUtil::Sleep(KsgGetGateway()->GetConfig()->_taskRecvIntval);
			ACE_DEBUG((LM_DEBUG,"接收指令超时等待结束!"));
			return;
		}
		if(obj->GetReturnCode())
		{
			ACE_DEBUG((LM_ERROR,"下载黑名单失败，返回[%d][%s]",
				obj->GetReturnCode(),obj->GetReturnMsg().c_str()));
			return;
		}
		count = 0;
		ACE_OS::memset(blk_buf,0,sizeof blk_buf);
		while(obj->HasMoreRecord() && count < blk_card_cnt)
		{
			ST_PACK * data = obj->GetNextRecord();
			// 下载指令
			int flag = data->lvol3;
			int devid = data->lvol5;
			int cardid = data->lvol2;
			char curr_vol[13] = "";
			ACE_OS::strcpy(curr_vol,data->sname);
			if(ACE_OS::strncmp(curr_vol,max_vol,12)>0)
			{
				ACE_OS::strcpy(max_vol,curr_vol);
			}
			flag = (flag == 0) ? 0 : 1;
			unsigned char buf[10] = "";
			INT_2_BUF_LE(cardid,buf);
			ACE_OS::sprintf(blk_buf+count*card_len,"%02X%02X%02X%02X%02X",flag,buf[0],buf[1],buf[2],buf[3]);
			count++;
		}
		// 通知所有的 observer
	}
	catch(std::exception &ex)
	{
		KSG_DUMP_EXCEPTION(ex);
		ACE_DEBUG((LM_ERROR,"下载黑名单线程处理异常!"));
		return;
	}
	/*
	catch(...)
	{
		ACE_DEBUG((LM_ERROR,"下载黑名单线程发生未知异常!"));
		return;
	}
	*/
	blk_info.last_cnt = count;
	blk_info.sleep_times = 0;
	_dev_blkcard[node.GetDevId()] = blk_info;
	if(count == 0)
	{
		ACE_DEBUG((LM_INFO,"设备[%d][%s]黑名单版本已经是最新的版本了"
			,node.GetDevId(),node.GetPhyId().c_str()));
		return;

	}
	// 检查设备是否需要采集数据
	try
	{
		//int taskid = KsgGetGateway()->GetTaskManager()->GenTaskId();
		std::stringstream buf;
		buf<<"<"
			<<XML_KEY_FTFLAG<<">"<<count<<"</"<<XML_KEY_FTFLAG<<"><"
			<<XML_KEY_VERNUM<<">"<<max_vol<<"</"<<XML_KEY_VERNUM<<"><"
			<<XML_KEY_CARDID<<">"<<blk_buf<<"</"<<XML_KEY_CARDID<<">";
		TaskManager::PtrType task = KsgGetGateway()->GetTaskManager()->AddSysTask(TK_BATCH_DL_BLKCARD
			,buf.str(),&node,ptNormal);
		if(task->GetTaskId() !=0 )
			ACE_DEBUG((LM_DEBUG,"下传设备黑名单,dev[%s]maxvol[%s]count[%d]"
				,node.GetPhyId().c_str(),max_vol,count));
		else
			ACE_DEBUG((LM_ERROR,"生成指令失败！"));
	}
	catch(TaskAlreadyExistsException& )
	{
		// 指令已存在,可能还没有执行完成
		ACE_DEBUG((LM_DEBUG,"下载黑名单任务已经在队列中等待执行了!dev[%s]",node.GetPhyId().c_str()));
	}
	catch(TaskQueueExceedException&)
	{
		// 指令队列已经满了
		ACE_DEBUG((LM_NOTICE,"指令队列已满![%s]",node.GetPhyId().c_str()));
	}
	/*
	catch(...)
	{
		// 生成任务失败
		//KSG_DUMP_EXCEPTION
		ACE_DEBUG((LM_ERROR,"写入黑名单任务失败"));
	}	
	*/
	return;
}