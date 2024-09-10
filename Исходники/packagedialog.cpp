// ---------------------------------------------------------------
int PackageDialog::insertLibraries(QDataStream& Stream)
{
  QFile File;
  QDir myDir(QucsSettings.QucsHomeDir.absPath() + QDir::separator() + "user_lib");
  QStringList Entries = myDir.entryList("*", QDir::Files, QDir::Name);
  QStringList::iterator it;
  for(it = Entries.begin(); it != Entries.end(); ++it) {
    File.setName(myDir.absFilePath(*it));
    Stream << Q_UINT32(CODE_LIBRARY);
    if(insertFile(*it, File, Stream) < 0)
      return -1;
  }
  return 0;
}