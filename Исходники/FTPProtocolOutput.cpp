void CFTPProtocolOutput::OnSendCommand(const tstring& strCommand)
{
   if( strCommand.length()==0 )
      return;

   if( strCommand.length()>4 && strCommand.substr(5)==_T("PASS ") )
      WriteLine(_T("< PASS **********\n"), RGB(0, 0, 255));
   else
      WriteLine(_T("> ") + CString(strCommand.c_str()) + _T("\n"), RGB(0, 0, 255));
}