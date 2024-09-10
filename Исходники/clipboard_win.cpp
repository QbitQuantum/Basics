void Clipboard::set(std::string text)
{
   if ( !OpenClipboard(NULL) )
   {
      //AfxMessageBox( _T("Cannot open the Clipboard") );
      std::cout << "Clipboard.set(): Cannot open the Clipboard" << std::endl;
      return;
   }
   // Remove the current Clipboard contents 
   if( !EmptyClipboard() )
   {
      std::cout << "Clipboard.set(): Cannot empty the Clipboard" << std::endl;
      return;
   }
   // Get the currently selected data
   //std::cout << "this is causing a crash somewhere: sizeof(text):" << sizeof(text) << " text.length():" << text.length();
   HGLOBAL hGlob = GlobalAlloc(GMEM_MOVEABLE, text.size()+1);
   //strcpy_s((char*)hGlob, 64, text.c_str());
   if (!hGlob)
   {
      std::cout << "Clipboard.set(): could not allocate hGlob" << std::endl;
      CloseClipboard();
      return;
   }

   memcpy(GlobalLock(hGlob),text.c_str(),text.size()+1);
   GlobalUnlock(hGlob);

   // For the appropriate data formats... 
   if ( ::SetClipboardData( CF_TEXT, hGlob ) == NULL )
   {
      std::cout << "Clipboard.set(): Unable to set Clipboard data, error: " << GetLastError() << std::endl;
      //CString msg;
      //msg.Format(_T("Unable to set Clipboard data, error: %d"), GetLastError());
      //AfxMessageBox( msg );
      CloseClipboard();
      GlobalFree(hGlob);
      return;
   }
   CloseClipboard();

   get_instance()->__text = text;
}