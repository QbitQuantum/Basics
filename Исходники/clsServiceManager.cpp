bool ServiceManager::StopService(LPCSTR p_serviceID)
{
	ATOM serviceID = FindAtomA(p_serviceID);
	TRACE("Stopping %s", p_serviceID);
	return m_serviceList.end() != std::find_if(m_serviceList.begin(), m_serviceList.end(), std::bind2nd(std::mem_fun(&Service::Stop), serviceID));
}