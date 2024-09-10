int BdLogic::buildInactiveProjectList()
{
    QVariantMap resourcesMapFromJson;
    QVariantList projectListFromJson;
    QVariantMap projectFromJson;

    resourcesMapFromJson = m_boxMapParsedJson[BoxNames[DLSTATE_RESOURCES]].toMap();
    resourcesMapFromJson = resourcesMapFromJson["resources"].toMap();
    projectListFromJson = resourcesMapFromJson["projects"].toList();

    m_currentInactiveProjectDlIx = 0;
    m_inactiveProjectUUIDList.clear();

    for(int projectIx = 0; projectIx < projectListFromJson.length(); projectIx++)
    {
        projectFromJson = projectListFromJson[projectIx].toMap();

        if(projectFromJson["status"].toString() == QString("inactive"))
        {
            m_inactiveProjectUUIDList.push_back(projectFromJson["uuid"].toString());
        }
    }

    return BDLOGIC_STATUS_OK;
}