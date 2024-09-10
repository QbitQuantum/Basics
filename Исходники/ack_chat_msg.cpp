		AckChatMsg::AckChatMsg(InstancePtr instance, const UserID& target_uid, msg_id_t msg_id, AckChatMsg::CallbackPtr cb)
		{
			if (!msg_id)
				throw AppException("msg id is null");

			instant_messaging_server::methods::rpc::AckChatMsgRequest ack_chat_req;
			ack_chat_req.mutable_sender_usr_id()->set_uid(target_uid.uid);
			if (!target_uid.domain.empty())
				ack_chat_req.mutable_sender_usr_id()->set_domain(target_uid.domain);
			ack_chat_req.set_msg_id(msg_id);

			ConnectionPtr conn = instance->getConnection("ua");
			seq_t seq = conn->getNextSeq();

			MsgBody body;
			body.addTarget("im");
			body.addRequest(instant_messaging_server::methods::rpc::CmdID_AckChatMsg, seq, 0, ack_chat_req);

			conn->send(rpc::OP_REQUEST, body);
			conn->addRequest(seq, cb);
		}