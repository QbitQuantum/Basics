void AnimationTestDlg::closeEvent(QCloseEvent* pEvent)
{
   if (mpPlugIn != NULL)
   {
      Executable* pExecutable = dynamic_cast<Executable*>(mpPlugIn);
      if (pExecutable != NULL)
      {
         pExecutable->abort();
      }
   }

   QDialog::closeEvent(pEvent);
}