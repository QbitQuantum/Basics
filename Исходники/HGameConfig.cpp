void HGameTime::setServerTime(int stime)
{    
    m_deltaTime = getLocalTime() -stime;
}