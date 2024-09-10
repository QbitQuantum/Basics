void CVolumeFunction::SeVolume()
{
    while(m_bRun)
    {
        m_lock.Lock();
        tagVolumeConf stVolumeConf = m_stVolumeConf;
        m_lock.UnLock();
        if(stVolumeConf.vecVolume.size() <= 0)
        {
            Sleep(5*1000);
            continue;;
        }

        for (vector<tagVolumeConf::_st_Volume>::iterator iter = stVolumeConf.vecVolume.begin();
                iter != stVolumeConf.vecVolume.end();
                iter++)
        {
            string strTime = "";

            time_t tn = time(0);
            string strDateNow = CBase::time2string_date(tn);
            string strTimeNow = CBase::time2string_time(tn);

            strTime = strDateNow;
            strTime += " ";
            strTime += iter->strTime;
            strTime += ":00";

            time_t tc = CBase::string2time(strTime);

            if( _abs64(tn - tc) <= 60)
            {
                CVolumeManager::GetInstance()->SetSpeakerLevel(atoi(iter->strVolume.c_str()));
                break;
            }
        }

        Sleep(5*1000);
    }
}