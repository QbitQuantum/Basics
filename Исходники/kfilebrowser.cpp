/*=========================================================================
  cutFromClipboard 
=========================================================================*/
bool KFileBrowser::cutFromClipboard (const FileClipboard *fc)
  {
  const QStringList &names = fc->getNames();
  QMessageBox msgBox;
  msgBox.setText(tr("Confirm move"));
  if (names.count() == 1)
    msgBox.setInformativeText
        (tr("Do you want to move this item?"));
 else
    {
    char ss[20];
    sprintf (ss, "%d", names.count());
    msgBox.setInformativeText
        ((QString)tr("Do you want to move these") + " " + ss + " " 
          + tr ("items") +  "?");
    }
  msgBox.setStandardButtons(QMessageBox::Ok 
      | QMessageBox::Cancel);
  msgBox.setDefaultButton(QMessageBox::Cancel);
  int r = msgBox.exec();
  if (r != QMessageBox::Ok) return false; 

  bool ret = FALSE;
  const QString &root = fc->getRoot();
  int l = names.count();
  int itemsDone = 0;

  QProgressDialog progress (tr("Moving files..."), tr("Stop"), 
      0, l, this);
  progress.setWindowModality (Qt::WindowModal);
  progress.setMinimumDuration (0);
  progress.show();
  bool stop = false;
  QString errorMessage = "";
  for (int i = 0; i < l && !progress.wasCanceled() &&!stop; i++)
    {
    QString sourceName = root + "/" + names[i];
    QString targetName;
    if (fc->getPasteByNameOnly())
      {
      QFileInfo info (path + "/" + names[i]);
      QString shortName = info.fileName(); 
      targetName = path + "/" + shortName;
      }
    else
      targetName = path + "/" + names[i];

    errorMessage = "";

    if (sourceName == targetName)
      {
      errorMessage = tr ("Source and destination files are the same");
      }
    else
      {
      QFileInfo info (sourceName);
      if (info.isDir())
        {
        QDir dir;
        if (dir.rename (sourceName, targetName))
          itemsDone++;
        else
          errorMessage = tr("Can't move directory");
        }
      else
        {
        QFile file;
        if (file.rename (sourceName, targetName))
          itemsDone++;
        else
          errorMessage = tr("Can't move file");
        }
      }

    if (errorMessage != "")
      {
      if (i < l - 1)
        {
        QMessageBox msgBox;
        msgBox.setText(tr("Error copying file"));
        msgBox.setInformativeText
          (errorMessage + ". " + 
             tr("Do you want to coninue with the next item?"));
        msgBox.setStandardButtons(QMessageBox::Ok 
            | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        int ret = msgBox.exec();
        if (ret != QMessageBox::Ok) stop = true;
        }
      else
        error (errorMessage);
      }

    progress.setValue (i);
    }

  if (progress.wasCanceled()) message ("canceled");

  progress.setValue (l);
  ret = true;
  if (stop) ret = false;
  if (progress.wasCanceled()) ret = false;
  if (errorMessage != "") ret = false;

  emit dirContentsChanged();

  QString sm = tr("Moved");
  char ss[20];
  sprintf (ss, "%d", itemsDone);
  sm += ss;
  sm += " " + (itemsDone == 1 ? tr("items") : tr("items"));
  emit statusUpdate (sm);

  return ret;
  }