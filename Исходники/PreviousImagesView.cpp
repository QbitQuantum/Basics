/// \see http://stackoverflow.com/questions/3010305/programmatically-selecting-file-in-explorer
void PreviousImagesView::OpenFolder(const CString& cszImageFilename)
{
   ITEMIDLIST* pidl = ILCreateFromPath(cszImageFilename);
   if (pidl != nullptr)
   {
      SHOpenFolderAndSelectItems(pidl, 0, nullptr, 0);
      ILFree(pidl);

      return;
   }

   // workaround for systems where ILCreateFromPath() fails; opens a new explorer
   // window each time it is called.
   CString cszFolderName = Path(cszImageFilename).FolderName();

   CString cszArgs;
   cszArgs.Format(_T("/select, \"%s\""), cszImageFilename.GetString());
   ::ShellExecute(m_hWnd, _T("open"), _T("explorer.exe"), cszArgs, cszFolderName, SW_SHOWNORMAL);
}