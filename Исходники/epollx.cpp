bool epollx::start(char* szip,unsigned short usport,int icapacity)
{
    m_capacity = icapacity;
    m_sockvec.resize(icapacity + getcpunum() + 10);
    if(!createlistener(szip,usport))
        return false;
    if(!createepfd())
    {   
        g_log.log(LOG_LV_ERROR,"createfd fail!");
        return false;
    }
    if(!createthread())
    {
        g_log.log(LOG_LV_ERROR,"createthread fail!");
        return false;
    }
    g_log.log(LOG_LV_INFO,"start succ!");
    return true;
}