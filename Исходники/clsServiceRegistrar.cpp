ServiceRegistrar::ServiceRegistrar(LPCSTR p_serviceName, fnServiceCreator p_creator)
{
	m_serviceAtom = AddAtomA(p_serviceName);
	ServiceManager::KnownService(m_serviceAtom,  p_creator);

}