void GameInterchange::operChanges(TCPConnection::Pointer conn, interchangeOperGoods*  oper) //交易物品变动
{

    Server* srv = Server::GetInstance();

    SessionMgr::SessionPointer sp = SessionMgr::Instance()->GetSession();

    if(oper->goodsId>=min_EquipMentId && oper->goodsId <=max_EquipMentId)
    {
        _umap_roleEqu::iterator iterRoleGoods = (*sp)[conn].m_playerEqu->find(oper->goodsId);
        if(iterRoleGoods == (*sp)[conn].m_playerEqu->end())            //玩家选择的物品在服务器中不存在属于异常情况，忽略异常情况，服务器不做响应
        {
            return;
        }

        if(iterRoleGoods->second.goods.Position == oper->position&&iterRoleGoods->second.goods.Count == oper->goodsCount) //位置信息和数量同时对应，则是找到玩家选择的物品
        {
            (*sp)[conn].m_goodsPosition[oper->position] = POS_LOCKED;       //背包中找到该物品，则设定对该物品不能做其它操作
        }
        else
        {
            return;
        }
    }
    else
    {
        _umap_roleGoods::iterator iterRoleGoods = (*sp)[conn].m_playerGoods->find(oper->goodsId);
        if(iterRoleGoods == (*sp)[conn].m_playerGoods->end())            //玩家选择的物品在服务器中不存在属于异常情况，忽略异常情况，服务器不做响应
        {
            return;
        }
        vector<STR_Goods>::iterator iterGoods = iterRoleGoods->second.begin();
        for(; iterGoods != iterRoleGoods->second.end(); ++iterGoods)
        {
            if(iterGoods->Position == oper->position&&iterGoods->Count == oper->goodsCount) //位置信息和数量同时对应，则是找到玩家选择的物品
            {
                (*sp)[conn].m_goodsPosition[oper->position] = POS_LOCKED;       //背包中找到该物品，则设定对该物品不能做其它操作
                break;
            }
        }
        if(iterGoods == iterRoleGoods->second.end())                                    //背包中未找到该物品，属于异常情况，忽略异常情况
        {
            return;
        }
    }

    boost::shared_ptr<Interchange> interchange = (*sp)[conn].m_interchage;
    if(oper->operType == Goods_Add)                        //增加物品的操作
    {
        std::vector<STR_Goods>::iterator iter = interchange->changes.begin();
        for( ;iter != interchange->changes.end(); ++iter)
        {
            if(iter->Position == oper->position)
                break;
        }
        if(iter == interchange->changes.end())              //交易筐中还没添加该位置的物品
        {
            STR_Goods goods;
            goods.Count = oper->goodsCount;
            goods.Position = oper->position;
            goods.GoodsID = oper->goodsId;
            goods.TypeID = oper->goodsType;
            goods.Source = Source_Trade;
            interchange->changes.push_back(goods);
        }
        else
        {
            return;                //交易筐中已经添加该位置的物品，属于异常情况，则忽略该次请求
        }
    }
    else  if(oper->operType == Goods_Remove)                                                       //从交易篮中删除物品
    {
       int haveValue = 0;
       std::vector<STR_Goods>::iterator iter = interchange->changes.begin();
       for(;iter != interchange->changes.end();++iter)
       {
           if(iter->Count == oper->goodsCount&&iter->Position ==  oper->position&&iter->GoodsID == oper->goodsId)
           {
               haveValue = 1;
               iter = interchange->changes.erase(iter);
                (*sp)[conn].m_goodsPosition[oper->position] = POS_NONEMPTY;       //恢复物品原来标志
               break;
           }
       }
       if(iter == interchange->changes.end()&& haveValue == 0)
       {
           return;
       }
    }

    TCPConnection::Pointer partnerConn = interchange->partnerConn;
    SessionMgr::SessionMap::iterator iter = sp->find(partnerConn);
    if(iter == sp->end())                        //对方离线 则由服务器发取消交易的包返回
    {
        interchangeOperPro resp;
        resp.operType = Operation_CancelChange;
        conn->Write_all((char*)&resp, sizeof(interchangeOperPro));
        for(std::vector<STR_Goods>::iterator iter = interchange->changes.begin(); iter != interchange->changes.end(); ++iter)    //背包位置信息恢复原来标志
        {
            (*sp)[conn].m_goodsPosition[iter->Position] = POS_NONEMPTY;
        }
        interchange->clear();           //清除交易状态  对方离线所以不用处理其状态信息
        srv->free(oper);
        return;
    }

    conn->Write_all((char*)oper, sizeof(interchangeOperGoods));
    partnerConn->Write_all((char*)oper, sizeof(interchangeOperGoods));
    srv->free(oper);
}