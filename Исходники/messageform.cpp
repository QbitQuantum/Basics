//---------------------------------------------------------------------------
void ReportMess2(String fmt, ...)
{
#ifndef SYSTEMSERVICE
  va_list argptr;
  va_start(argptr, fmt);
  String s;
  s.vprintf(fmt.c_str(), argptr);
  ShowMessage2(Screen->ActiveForm,
			   s,
			   Application->Title,
			   true,  // Modal
			   false); //Error
  va_end(argptr);
#endif
}