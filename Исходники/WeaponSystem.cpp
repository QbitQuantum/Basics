//------------------------------------------------------------------------
void CWeaponSystem::Reload()
{
	m_reloading = true;

	// cleanup current projectiles
	for (TProjectileMap::iterator pit = m_projectiles.begin(); pit != m_projectiles.end();)
	{
		//Bugfix: RemoveEntity removes projectile from map, thus invalidating iterator
		TProjectileMap::iterator next = pit;        
		next++;
		gEnv->pEntitySystem->RemoveEntity(pit->first, true);
		pit = next;
	}
	m_projectiles.clear();

	for (TAmmoTypeParams::iterator it = m_ammoparams.begin(); it != m_ammoparams.end(); ++it)
	{
		SAmmoTypeDesc &desc=it->second;
		delete desc.params;
		if (!desc.configurations.empty())
		{
			for (std::map<string, const SAmmoParams *>::iterator ait=desc.configurations.begin(); ait!=desc.configurations.end(); ait++)
				delete ait->second;
		}
	}

	m_ammoparams.clear();

	m_tracerManager.Reset();

	for (TFolderList::iterator it=m_folders.begin(); it!=m_folders.end(); ++it)
		Scan(it->c_str());

	m_reloading = false;
}