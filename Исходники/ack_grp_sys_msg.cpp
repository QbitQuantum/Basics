		AckGroupSysMsg::AckGroupSysMsg(InstancePtr instance, const GroupID& group_id, const string& channel, msg_id_t sysmsg_id, AckGroupSysMsg::CallbackPtr cb)
		{
			if (!sysmsg_id)
				throw AppException("sysmsg id is null");

			group_messaging_server::methods::rpc::AckGrpSysMsgRequest ack_sys_req;
			if (!channel.empty())
				ack_sys_req.set_channel(channel);
			ack_sys_req.set_sysmsg_id(sysmsg_id);

			ConnectionPtr conn = instance->getConnection("ua");
			seq_t seq = conn->getNextSeq();

			Uri target;
			createUri(&target, "grp", group_id);

			MsgBody body;
			body.addTarget(target);
			body.addRequest(group_messaging_server::methods::rpc::CmdID_AckGrpSysMsg, seq, 0, ack_sys_req);

			conn->send(rpc::OP_REQUEST, body);
			conn->addRequest(seq, cb);
		}