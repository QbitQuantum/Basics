  bool ResultsViewerData::isFileOpen(openstudio::SqlFile sqlFile)
  {
    if (!sqlFile.connectionOpen()) return false;
    if (m_sqlFileMap.size() == 0) return false;

    bool isOpen = false;
    std::map<openstudio::SqlFile, QString>::iterator iter;
    for(iter=m_sqlFileMap.begin(); iter!=m_sqlFileMap.end(); ++iter) {
      if (sqlFile.energyPlusSqliteFile() == (*iter).first.energyPlusSqliteFile()) {
        isOpen = true;
        break;
      }
    }
    return isOpen;
  }