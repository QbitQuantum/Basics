//发送玩家可视范围内的任务
void GameTask::SendPlayerViewTask(TCPConnection::Pointer conn)
{
    //根据任务条件和玩家信息判断玩家可接取的任务
    SessionMgr::SessionMap* smap = SessionMgr::Instance()->GetSession().get();
    STR_RoleBasicInfo* t_RoleBaseInfo = &(*smap)[conn].m_RoleBaseInfo; //得到玩家信息
    umap_taskProcess umap_playerAcceptTask = ((*smap)[conn]).m_playerAcceptTask;

    hf_int32 size = 0;
    Server* srv = Server::GetInstance();
    hf_char* buff = (hf_char*)srv->malloc();
    STR_PackHead t_packHead;

    //发送玩家所在地图上的任务
    for(_umap_taskProfile::iterator it = m_taskProfile->begin(); it != m_taskProfile->end(); it++)
    {
        _umap_taskProcess::iterator iter = umap_playerAcceptTask->find(it->first);
        if(iter == umap_playerAcceptTask->end()) //是否已接取
        {
            STR_TaskPremise t_taskpremise = (*m_taskPremise)[it->first];
            if(t_RoleBaseInfo->Level >= t_taskpremise.Level)  //等级符合
            {
                it->second.Status = 1;
                memcpy(buff + sizeof(STR_PackHead) + size*sizeof(STR_TaskProfile), &(*m_taskProfile)[it->first], sizeof(STR_TaskProfile));
                size++;
            }
        }
        if(size == (CHUNK_SIZE - sizeof(STR_PackHead))/sizeof(STR_TaskProfile))
        {
            t_packHead.Flag = FLAG_TaskProfile;
            t_packHead.Len = sizeof(STR_TaskProfile) * size;

            memcpy(buff, (hf_char*)&t_packHead, sizeof(STR_PackHead));
            //发送可接取的任务
            conn->Write_all(buff, sizeof(STR_PackHead) + t_packHead.Len);
            size = 0;
        }
    }

    if(size != (CHUNK_SIZE - sizeof(STR_PackHead))/sizeof(STR_TaskProfile) && size != 0)
    {
        t_packHead.Flag = FLAG_TaskProfile;
        t_packHead.Len = sizeof(STR_TaskProfile) * size;

        memcpy(buff, (hf_char*)&t_packHead, sizeof(STR_PackHead));
        //发送可接取的任务
        conn->Write_all(buff, sizeof(STR_PackHead) + t_packHead.Len);
    }
    srv->free(buff);
}