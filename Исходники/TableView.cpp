  bool TableView::addFile(const QString& alias, openstudio::SqlFile sqlFile)
  {
    if (alias.isEmpty() || !sqlFile.connectionOpen()) return false;

    setSortingEnabled(false);

    detail::DataDictionaryTable ddTable = sqlFile.dataDictionary();

    detail::DataDictionaryTable::iterator iter;
    for (iter=ddTable.begin();iter!=ddTable.end();++iter)
    {
      // skip runPeriod
      if (sqlFile.reportingFrequencyFromDB((*iter).reportingFrequency)
          && *(sqlFile.reportingFrequencyFromDB((*iter).reportingFrequency)) != ReportingFrequency::RunPeriod)
      {

        int row = addRow();
        item(row, m_slHeaders.indexOf("Alias"))->setText(alias);
        item(row, m_slHeaders.indexOf("File"))->setText(openstudio::toQString(sqlFile.energyPlusSqliteFile()));
        item(row, m_slHeaders.indexOf("Environment Period"))->setText(openstudio::toQString((*iter).envPeriod));
        item(row, m_slHeaders.indexOf("Reporting Frequency"))->setText(openstudio::toQString((*iter).reportingFrequency));
        item(row, m_slHeaders.indexOf("Key Value"))->setText(openstudio::toQString((*iter).keyValue));
        item(row, m_slHeaders.indexOf("Variable Name"))->setText(openstudio::toQString((*iter).name));
        item(row, m_slHeaders.indexOf("File"))->setData(Qt::UserRole, RVD_TIMESERIES);
      } // end skip runPeriod
    }

    /* illuminance maps */
    std::vector<std::string> mapNames(sqlFile.illuminanceMapNames());
    std::vector<std::string>::iterator nameIter;
    for (nameIter=mapNames.begin(); nameIter!=mapNames.end(); ++nameIter)
    {
      // retrieve mapIndex for map name to retrieve environment period and zone name
      QString envPeriod = "";
      QString keyValue = "";
      boost::optional<int> mapIndex = sqlFile.illuminanceMapIndex(*nameIter);
      if (mapIndex)
      {
        boost::optional<std::string> strValue;
        boost::optional<int> intValue;
        std::stringstream s;
        s << "select Environment from daylightmaps where MapNumber=" << *mapIndex;
        strValue = sqlFile.execAndReturnFirstString(s.str());
        if (strValue) envPeriod = openstudio::toQString(*strValue);
        s.str("");
        s << "select Zone from daylightmaps where MapNumber=" << *mapIndex;
        intValue = sqlFile.execAndReturnFirstInt(s.str());
        if (intValue)
        {
          s.str("");
          s << "select ZoneName from zones where ZoneIndex=" << *intValue;
          strValue = sqlFile.execAndReturnFirstString(s.str());
          if (strValue) keyValue = openstudio::toQString(*strValue);
        }
      }
      int row = addRow();
      item(row, m_slHeaders.indexOf("Alias"))->setText(alias);
      item(row, m_slHeaders.indexOf("File"))->setText(openstudio::toQString(sqlFile.energyPlusSqliteFile()));
      item(row,  m_slHeaders.indexOf("Environment Period"))->setText(envPeriod); // environment period
      /* update based on email from Dan 8/10/10
         item(row, 3)->setText("Illuminance"); // reporting frequency
         item(row, 4)->setText(keyValue); // illuminance zone?
         item(row, 5)->setText(openstudio::toQString(*nameIter));
         */
      item(row, m_slHeaders.indexOf("Reporting Frequency"))->setText("Hourly"); // reporting frequency
      item(row, m_slHeaders.indexOf("Key Value"))->setText(keyValue); // illuminance zone
      item(row, m_slHeaders.indexOf("Variable Name"))->setText("Illuminance Map"); // Variable Name
      item(row, m_slHeaders.indexOf("File"))->setData(Qt::UserRole, RVD_ILLUMINANCEMAP);
      item(row, m_slHeaders.indexOf("Alias"))->setData(Qt::UserRole, openstudio::toQString(*nameIter)); // map name for retrieving from database
    }

    resizeColumnToContents(m_slHeaders.indexOf("Alias"));
    hideColumn(m_slHeaders.indexOf("File"));
    resizeColumnToContents(m_slHeaders.indexOf("Variable Name"));
    resizeColumnToContents(m_slHeaders.indexOf("Key Value"));
    resizeColumnToContents(m_slHeaders.indexOf("Reporting Frequency"));
    //  resizeColumnToContents(5);

    setSortingEnabled(true);

    emit( fileAdded() );

    return true;
  }