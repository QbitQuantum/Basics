AEResult GameResourceManager::UnManageGameResource(uint64_t id)
{
	std::lock_guard<std::mutex> lock(m_GameResourceManagerMutex);

	if(!GameResourceExists(id))
	{
		return AEResult::NotFound;
	}

	GameResource* gameResource = m_GameResourceMap[id];
	
	std::lock_guard<std::mutex> lockResource(gameResource->m_GameResourceMutex);

	gameResource->m_Managed = false;
	gameResource->m_ReleaseCallback = nullptr;
	gameResource->m_KeepAlive = false;
	gameResource->m_StringIdentifier = L"";

	m_GameResourceMap.erase(m_GameResourceMap.find(id));

	return AEResult::Ok;
}