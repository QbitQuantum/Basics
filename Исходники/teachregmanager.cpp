void TeachRegManager::addGroup(const QString &groupName)
{
	Group gr;
	gr.setParent(db);
	gr.setName(groupName);
	db->addGroup(gr);
}