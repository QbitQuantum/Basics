//玩家上线，发送离线的添加好友请求
 void TeamFriend::SendAskAddFriend(TCPConnection::Pointer conn)
 {
     SessionMgr::SessionPointer smap = SessionMgr::Instance()->GetSession();
     hf_uint32 roleid = (*smap)[conn].m_roleid;
     StringBuilder sbd;
     sbd << "select requestroleid,requestnick from t_addFriend where addroleid = " << roleid << ";";
     Logger::GetLogger()->Debug(sbd.str());

     Server* srv = Server::GetInstance();
     vector<STR_AddFriend> addFriend;
     hf_int32 t_row = srv->getDiskDB()->GetAskAddFriend(addFriend, sbd.str());
     if(t_row > 0)
     {
         hf_char* buff = (hf_char*)srv->malloc();
         STR_PackHead t_packHead;
         t_packHead.Flag = FLAG_AddFriend;
         t_packHead.Len = t_row*sizeof(STR_AddFriend);
         hf_int32 i = 0;
         for(vector<STR_AddFriend>::iterator it = addFriend.begin(); it != addFriend.end(); it++)
         {
             memcpy(buff + sizeof(STR_PackHead) + i*sizeof(STR_AddFriend),&(*it), sizeof(STR_AddFriend));
             i++;
         }
         memcpy(buff, &t_packHead, sizeof(STR_PackHead));
         conn->Write_all(buff,t_packHead.Len + sizeof(STR_PackHead));

         srv->free(buff);

         //删除保存的离线添加请求
         sbd.Clear();
         sbd << "delete from t_addFriend where addroleid = " << roleid << ";";
         Logger::GetLogger()->Debug(sbd.str());
         t_row = srv->getDiskDB()->Set(sbd.str());
         if(t_row == 1)
         {
             Logger::GetLogger()->Debug("delete asd addfriend success");
         }
     }
 }