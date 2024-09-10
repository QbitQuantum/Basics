bool KMiniEdit::saveFile(KURL newurl)
{
  if (newurl.isEmpty())
    newurl = KFileDialog::getSaveURL();

  if (newurl.isEmpty())
    return false;

  if (newurl.isMalformed())
  {
    QString text = i18n("<b>THe URL %1 is not correct!</b>");
    KMessageBox::sorry(this, text.arg(newurl.prettyURL()));
    return false;
  }

  if (newurl.isLocalFile())
  {
    QFile file(newurl.path());
    file.open(IO_WriteOnly);
    saveToLocalFile(&file);
  }

  else
  {
    KTempFile tempfile;
    saveToLocalFile(tempfile.file());
    if (!KIO::NetAccess::upload(tempfile.name(), newurl))
    {
      QString text = i18n("<b>Error uploading %1!</b>");
      KMessageBox::sorry(this, text.arg(newurl.prettyURL()));
      tempfile.unlink();
      return false;
    }

    tempfile.unlink();
  }

  url = newurl;
  
  addURLtoRecent();
  
  resetEdited();
  return true;
}