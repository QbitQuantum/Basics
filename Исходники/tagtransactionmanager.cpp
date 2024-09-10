bool TagTransactionManager::renameFile(const QFileInfo &from, const QFileInfo &to) const
{
   if(!QFileInfo(to.path()).isWritable() || !from.exists())
       return false;

   if(!to.exists() ||
       KMessageBox::warningContinueCancel(
           static_cast<QWidget *>(parent()),
           i18n("This file already exists.\nDo you want to replace it?"),
           i18n("File Exists"),KGuiItem(i18n("Replace"))) == KMessageBox::Continue)
   {
       kDebug() << "Renaming " << from.absoluteFilePath() << " to " << to.absoluteFilePath();
       QDir currentDir;
       return currentDir.rename(from.absoluteFilePath(), to.absoluteFilePath());
   }

   return false;
}