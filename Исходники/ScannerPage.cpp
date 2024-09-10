void ScannerPage::runScanner ()
{
  QString s;
  config.getData(Config::ScannerPath, s);
  QString s2("*");
  SymbolDialog *dialog = new SymbolDialog(this,
                                          s,
  					  s,
					  s2,
					  Q3FileDialog::ExistingFiles);
  dialog->setCaption(tr("Select scanners to run"));

  int rc = dialog->exec();

  if (rc == QDialog::Accepted)
  {
    QStringList l = dialog->selectedFiles();
    int loop;
    QDir dir;
    for (loop = 0; loop < (int) l.count(); loop++)
    {
      QFileInfo fi(l[loop]);
      Scanner *sdialog = new Scanner(fi.fileName(), chartIndex);
      connect(sdialog, SIGNAL(exitScanner()), this, SLOT(refreshList()));
      connect(sdialog, SIGNAL(message(QString)), this, SIGNAL(message(QString)));
      sdialog->show();
      sdialog->scan();
      delete sdialog;
    }
  }

  delete dialog;
}