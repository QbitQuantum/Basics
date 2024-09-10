void welcomeWizard::slotCheckDisabled()
{
  QString username = QString::fromLocal8Bit(getenv("LOGNAME"));

  QString filename = "/home/" + username + "/.config/hide-welcome";
  QFile tmpFile(filename);

  if ( checkDisableWelcome->isChecked() )
    system("touch " + filename.toLatin1() );
  else
    tmpFile.remove();
   
}