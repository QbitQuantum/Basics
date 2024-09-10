int CnmpInfo::run()
{
    //DenyInterrupt();
    //创建日志组件
    m_pLogManage = CLogManage::getInstance();
    if ( m_pLogManage->setLog( GetProcessID()) < 0 )
    {
        std::cerr << __FILE__ << "  " << __LINE__ << "  " << "log error" << std::endl;
        return -1;
    }

    //创建数据库连接对象
    TOCIDatabase* pDB = Environment::getDBConn();
    if ( NULL == pDB )
    {
        LOG_DEBUG( "get db info error" );
        return -1;
    }

    m_pQry = new TOCIQuery( pDB );
    if ( NULL == m_pQry )
    {
        LOG_DEBUG( "create oci qry object error" );
        return -1;
    }

    if(init()< 0)
    {
        LOG_DEBUG( "init error" );
        return -1;
    }

    LOG_DEBUG( "NMP信息点提取开始运行..." );
    char szLog[MAX_STRING_LENGTH]= {0};
    pthread_t thread_id1;
    pthread_t thread_id2;
    int iRet = pthread_create(&thread_id1,NULL,thread_highInfo,NULL);
    if(iRet!=0)
    {
        LOG_DEBUG("create thread error");
        return -1;
    }
    iRet = pthread_create(&thread_id2,NULL,thread_lowInfo,NULL);
    if(iRet!=0)
    {
        LOG_DEBUG("create thread error");
        return -1;
    }
	
    //主线程实时检测子线程是否退出
    //如退出则进程退出
    while(true)
    {
        int pthread_kill_err =-1;
        //检查线程是否还在
        pthread_kill_err = pthread_kill(thread_id1,0);
        if(pthread_kill_err == ESRCH)
        {
            memset(szLog,0x00,sizeof(szLog));
            sprintf(szLog,"ID为0x%x的线程不存在或者已经退出",(unsigned int)thread_id1);
            LOG_DEBUG(szLog);
            return -1;
        }
        else if(pthread_kill_err == EINVAL)
        {
            LOG_DEBUG("发送信号非法");
        }
        else
        {
            memset(szLog,0x00,sizeof(szLog));
            sprintf(szLog,"ID为0x%x的线程目前仍然存活。",(unsigned int)thread_id1);
        }

        //检查线程是否还在
        pthread_kill_err = pthread_kill(thread_id2,0);
        if(pthread_kill_err == ESRCH)
        {
            memset(szLog,0x00,sizeof(szLog));
            sprintf(szLog,"ID为0x%x的线程不存在或者已经退出",(unsigned int)thread_id2);
            LOG_DEBUG(szLog);
            return -1;
        }
        else if(pthread_kill_err == EINVAL)
        {
            LOG_DEBUG("发送信号非法");
        }
        else
        {
            memset(szLog,0x00,sizeof(szLog));
            sprintf(szLog,"ID为0x%x的线程目前仍然存活。",(unsigned int)thread_id2);
        }
        usleep(99999);
    }

    return 1;

}