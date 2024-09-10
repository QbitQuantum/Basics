void KMoneyThingMainWidget::slotSave()
{
  KTempFile temp;
  QString fileName = mCurrentFile->kurl().path();
  
  if (fileName == "")
  {
    slotSaveAs();
    return;
  }
  
  if (!mCurrentFile->kurl().isLocalFile())
  {
    fileName = temp.name();
  }
  
  emit(setStatus(i18n("Saving file...")));
  QByteArray dump = qCompress(mCurrentFile->dump());
  QFile file(fileName);
  file.open(IO_WriteOnly);
  QDataStream stream(&file);
  stream << (QString) "KMoneyThingFile" << dump;
  file.close();
  
  if (!mCurrentFile->kurl().isLocalFile())
  {
    emit(setStatus(i18n("Uploading file...")));
    if (!KIO::NetAccess::upload(fileName, mCurrentFile->kurl(), this))
      KMessageBox::error(this, i18n("Failed to upload file."));
  }
  
  temp.unlink();
  
  emit(setStatus(i18n("Ready.")));
}