bool QCtkXipSGWidget::loadIvFile(const QString& ivFileName)
{
  if(!QFile::exists(ivFileName))
  {
    QString pwd = QDir::currentPath();
    return false;
  }

  std::string ivFileNameStr(ivFileName.toStdString());
  const char *ivStr = (const char*) ivFileNameStr.c_str();

  SoInput in;
  in.openFile(ivStr); // file
  SoSeparator *topNode = SoDB::readAll(&in);
  if (topNode)
  {
    if(mRoot)
    {
      mRoot->removeAllChildren();
      mRoot->addChild(topNode);

      return true;

    }
  }


  return false;

}