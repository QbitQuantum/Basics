	void CLinkerPipe::RevOneMsg(eElectron& E){
		ePipeline* Msg = (ePipeline*)E.Get();
		
		Msg = Decrypt(Msg);

        //  Msg->AutoTypeAB();
		
		int64 ID = Msg->GetID();
        if (ID < 100) //内部控制信息
        {
			assert(ID == LINKER_FEEDBACK);
            if (ID != LINKER_FEEDBACK)
            {
				ePipeline Info;
				Info.Push_Directly(E.Release());
				m_Parent->NotifyLinkerState(this,LINKER_ILLEGAL_MSG,Info);
				return;
            }

			if(m_PendingMsgID==NULL){
				return;
			}
			
			if(m_SendState == SEND_MSG){ 
				m_SendState = WAIT_MSG;
			}

			int32 RevResult   = Msg->PopInt();
 
			if (RevResult == RECEIVE_ERROR)
			{						
				//先发送一个重置接收信息，以便对方能从错误接收状态下恢复
				ePipeline*  Pipe = new ePipeline((uint64)LINKER_RESET);

                ePipeline Info;
				Info.PushInt(LINKER_FEEDBACK);
				Info.PushInt(RevResult);
				Info.PushInt(m_PendingMsgID);
				m_Parent->NotifyLinkerState(this,LINKER_MSG_RECEIVED,Info);
				
				m_PendingMsgID = 0;//取消未决信息，让本连接能继续发送
				m_PendMsgSenderID = 0;

				FeedbackDirectly(Pipe);

			}else{
				int64 TimeStamp   = Msg->PopInt();
				int64 ReceiverID  = Msg->PopInt();

				assert(m_PendMsgSenderID == ReceiverID);
				//assert(m_PendingMsg->GetID() == TimeStamp); 可能在m_CurSendMsg.Reset()时被delete
			
                ePipeline Info;
				Info.PushInt(LINKER_FEEDBACK);
				Info.PushInt(RevResult);
				Info.PushInt(m_PendingMsgID);
				m_Parent->NotifyLinkerState(this,LINKER_MSG_RECEIVED,Info);

				m_PendingMsgID = 0;//取消未决信息，让本连接能继续发送
				m_PendMsgSenderID = 0;
			}
       } 
       else
       {

			Msg->AutoTypeAB();
			if(Msg->GetTypeAB() != 0x44400000){ //格式不正确，丢弃
				ePipeline Info;
				Info.Push_Directly(E.Release());
				m_Parent->NotifyLinkerState(this,LINKER_ILLEGAL_MSG,Info);
				return;
			}
			
			CMsg m((ePipeline*)E.Release()); //包装成标准封装格式的信息
			int64 SenderID = m.GetSenderID();
		
			int64 MsgID = m.GetMsgID();

			//首先用对方的时间戳和发信者回复一个OK
			int64 TimeStamp = Msg->GetID();	
			ePipeline* rMsg = new ePipeline(LINKER_FEEDBACK);
			rMsg->PushInt(RECEIVE_OK);
			rMsg->PushInt(TimeStamp);
			rMsg->PushInt(SenderID);
			
			FeedbackDirectly(rMsg);

			ePipeline& Receiver = m.GetReceiver(); 
			
			//assert(Receiver.Size()==0); 缺省的MSG_DIALOG_NOTIFY接受者地址size=2 

			//把接收者ID转换成本地地址
			ePipeline LocalAddress;
			bool ret = ReceiverID2LocalAddress(Receiver,LocalAddress);
			if (!ret)
			{
				ePipeline Info;
				Info.Push_Directly(m.Release());
				m_Parent->NotifyLinkerState(this,LINKER_INVALID_ADDRESS,Info);
				return;
			}
			
			
			m.SetSourceID(m_SourceID);
			m.GetReceiver() << LocalAddress;	
			m_Parent->PushCentralNerveMsg(m);			
        }

    }