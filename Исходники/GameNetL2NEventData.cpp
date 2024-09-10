    //--------------------------------------------------------------------------------
    void GameNetL2NEventDataFactory::createGameNetSendDataBufferPtr(GameNetSendDataBufferPtr& ptr, U32 buffSize)
    {
        NetSendDataBuffer* buffObj                  = NULL;
        std::deque<NetSendDataBuffer*>* idleList    = NULL;
        GameNetSendDataBufferPool*      pool        = NULL;
        GameNetSendDataBufferPoolManager* poolMgr   = NULL;

        DWORD threadId = GetCurrentThreadId();
        poolMgr = createOrRetrieveGameNetSendDataBufferPoolManager( threadId );
        if ( poolMgr )
        {
            Bool isNormalBuff   = true;

            pool                = poolMgr->m_CreateObjectList;

            // 如果小于默认值, 则分配缓存等于默认值
            if ( buffSize <= MG_GAME_NET_PACKET_NORMAL_MAX_SIZE )
            {
                buffSize        = MG_GAME_NET_PACKET_NORMAL_MAX_SIZE;
                isNormalBuff    = true;
            }else
            if ( buffSize <= MG_GAME_NET_PACKET_BIG_MAX_SIZE )
            {
                buffSize        = MG_GAME_NET_PACKET_BIG_MAX_SIZE;
                isNormalBuff    = false;
            }else
            {
                DYNAMIC_EEXCEPT_LOG("createGameNetSendDataBufferPtr : too long buffsize ");
                return;
            }

            pool->mPoolCs.lock();
            {
                if ( isNormalBuff )
                {
                    idleList = &pool->m_IdleNormalObjectList;
                }else
                {
                    idleList = &pool->m_IdleBigObjectList;
                }

                if ( idleList->size() > 0 )
                {
                    buffObj = idleList->back();
                    idleList->pop_back();
                }else
                {
                    buffObj = mDriverMgr->mMgr->createNetSendDataBuffer( buffSize );
                }
            }
            pool->mPoolCs.unlock();


            poolMgr->mCreateCount++;

        }else
        {
            DYNAMIC_EEXCEPT_LOG("createGameNetSendDataBufferPtr: not register thread !");
        }

        if ( buffObj )
        {
            buffObj->initialize();
			buffObj->setActive( true );

            ptr.setNull();
            ptr.mFactory            = this;
            ptr.mCreateThreadID     = threadId;
            ptr.mNearestSendNetID   = -1;
            ptr.mLogicDataMaxSize   = buffSize;
            ptr.bind( buffObj );

            if ( poolMgr )
            {
                poolMgr->mNearestCreatePtr.setNull();
                poolMgr->mNearestCreatePtr = ptr;
            }
        }
    }