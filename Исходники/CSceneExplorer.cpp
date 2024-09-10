QStandardItem *CSceneExplorer::createItem(int id, const ENodeType type, const QString &label)
{
	QIcon *icon = 0;
	QStandardItem *item = 0;

	if(type == ENT_PROP_MODEL)            { icon = &m_propIcon; }
	else if(type == ENT_PROP_POWERUP)     { icon = &m_powerupIcon; }
	else if(type == ENT_PROP_PARTICLE)    { icon = &m_particleIcon; }
	else if(type == ENT_LIGHT)            { icon = &m_lightIcon; }
	else if(type == ENT_LOGIC_CAMERA)     { icon = &m_cameraIcon; }
	else if(type == ENT_LOGIC_TRIGGER)    { icon = &m_logicIcon; }
	else if(type == ENT_LOGIC_VECTOR)     { icon = &m_logicIcon; }
	else if(type == ENT_LOGIC_CONSTRAINT) { icon = &m_logicIcon; }
	else if(type == ENT_MAP)              { icon = &m_mapIcon; }

	if(icon)
	{
		item = new QStandardItem(*icon, label);
		item->setData(QVariant(id), Qt::UserRole + 1);
		item->setFlags(item->flags() & ~Qt::ItemIsEditable);
	}

	return item;
}