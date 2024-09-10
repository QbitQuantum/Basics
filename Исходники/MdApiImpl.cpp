bool MdApiImpl::GetRandSvr()
{
    srand((unsigned)time(NULL));
    size_t i=rand()% m_SvrVec.size();

    if (!m_SvrVec[i].empty())
    {
        std::string szPre = m_SvrVec[i].substr(0,3);

        if (!szPre.compare("tcp") || !szPre.compare("udp"))
        {
            if (!szPre.compare("tcp"))
            {
                m_iSockType = SOCK_STREAM;
            }
            else
            {
                m_iSockType = SOCK_DGRAM;
            }

            size_t iPos = m_SvrVec[i].rfind(':');
            size_t iPos2 = m_SvrVec[i].find("//");

            m_sFront=m_SvrVec[i].substr(iPos2+2,iPos-iPos2-2);
            m_sPort=m_SvrVec[i].substr(iPos+1);

            return true;
        }
        else
        {
            m_RspInf.ErrorID = 1;
            StringCbCopyA(m_RspInf.ErrorMsg,81,"不支持的连接类型");
            m_pSpi->OnRspError(&m_RspInf,-1,true);
        }
    }

    return false;
}