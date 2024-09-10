//----------------------------------------------------------------------------
void ctkPluginStorageSQL::updateDB()
{
  QSqlDatabase database = getConnection();
  QSqlQuery query(database);

  beginTransaction(&query, Write);

  // 1. Get the state information of all plug-ins (it is assumed that
  //    plug-ins marked as UNINSTALLED (startlevel == -2) are already removed

  QString statement = "SELECT ID,MAX(Generation),Location,LocalPath,Timestamp,StartLevel,AutoStart,K "
                      "FROM " PLUGINS_TABLE " GROUP BY ID";

  QList<int> outdatedIds;
  QList<QSharedPointer<ctkPluginArchiveSQL> > updatedPluginArchives;
  try
  {
    executeQuery(&query, statement);

    // 2. Check the timestamp for each plug-in

    while (query.next())
    {
      QFileInfo pluginInfo(query.value(EBindIndex3).toString());
      QDateTime pluginLastModified = pluginInfo.lastModified();
      // Make sure the QDateTime has the same accuracy as the one in the database
      pluginLastModified = getQDateTimeFromString(getStringFromQDateTime(pluginLastModified));

      if (pluginLastModified > getQDateTimeFromString(query.value(EBindIndex4).toString()))
      {
        QSharedPointer<ctkPluginArchiveSQL> updatedPA(
              new ctkPluginArchiveSQL(this,
                                      query.value(EBindIndex2).toUrl(),    // plug-in location url
                                      query.value(EBindIndex3).toString(), // plugin local path
                                      query.value(EBindIndex).toInt(),     // plugin id
                                      query.value(EBindIndex5).toInt(),    // start level
                                      QDateTime(),                         // last modififed
                                      query.value(EBindIndex6).toInt())    // auto start setting
              );
        updatedPA->key = query.value(EBindIndex7).toInt();
        updatedPluginArchives << updatedPA;

        // remember the plug-in ids for deletion
        outdatedIds << query.value(EBindIndex).toInt();
      }
    }
  }
  catch (...)
  {
    rollbackTransaction(&query);
    throw;
  }

  query.finish();
  query.clear();

  if (!outdatedIds.isEmpty())
  {
    // 3. Remove all traces from outdated plug-in data. Due to cascaded delete,
    //    it is sufficient to remove the records from the main table

    statement = "DELETE FROM " PLUGINS_TABLE " WHERE ID IN (%1)";
    QString idStr;
    foreach(int id, outdatedIds)
    {
      idStr += QString::number(id) + ",";
    }