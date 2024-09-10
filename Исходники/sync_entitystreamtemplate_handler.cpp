//-------------------------------------------------------------------------------------
bool SyncEntityStreamTemplateHandler::process()
{
	Components::COMPONENTS& cts = Components::getSingleton().getComponents(DBMGR_TYPE);
	Network::Channel* pChannel = NULL;

	if(cts.size() > 0)
	{
		Components::COMPONENTS::iterator ctiter = cts.begin();
		if((*ctiter).pChannel == NULL)
			return true;

		pChannel = (*ctiter).pChannel;
	}

	if(pChannel == NULL)
		return true;

	MemoryStream accountDefMemoryStream;

	ENGINE_COMPONENT_INFO& dbcfg = g_kbeSrvConfig.getDBMgr();

	ScriptDefModule* scriptModule = EntityDef::findScriptModule(dbcfg.dbAccountEntityScriptType);
	if(scriptModule == NULL)
	{
		delete this;
		return false;
	}

	ScriptDefModule::PROPERTYDESCRIPTION_MAP& propertyDescrs = scriptModule->getPersistentPropertyDescriptions();
	ScriptDefModule::PROPERTYDESCRIPTION_MAP::const_iterator iter = propertyDescrs.begin();

	if(scriptModule->hasCell())
	{
		Vector3 pos, dir;
		ADD_POSDIR_TO_STREAM(accountDefMemoryStream, pos, dir);
	}

	for(; iter != propertyDescrs.end(); ++iter)
	{
		PropertyDescription* propertyDescription = iter->second;
		accountDefMemoryStream << propertyDescription->getUType();
		propertyDescription->addPersistentToStream(&accountDefMemoryStream, NULL);
	}

	Network::Bundle* pBundle = Network::Bundle::ObjPool().createObject();

	(*pBundle).newMessage(DbmgrInterface::syncEntityStreamTemplate);
	(*pBundle).append(accountDefMemoryStream);
	pChannel->send(pBundle);
	delete this;
	return false;
}