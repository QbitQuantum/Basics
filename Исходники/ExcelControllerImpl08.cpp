void ExcelControllerImpl08::WaitForWorkbookOpened(const CStdString& sFilePathName)
{
   CStdString sWorkbookName = sFilePathName;

   int iPos = sWorkbookName.ReverseFind('\\');
   if (-1 != iPos)
      sWorkbookName = sWorkbookName.Right((int)sWorkbookName.length() - iPos - 1);
   else
   {
      iPos = sWorkbookName.ReverseFind(_T('/'));
      if (-1 != iPos)
         sWorkbookName = sWorkbookName.Right((int)sWorkbookName.length() - iPos - 1);
   }

   int iTryCount = 0;
   while (200 >= iTryCount)  // about 20 seconds
   {
      try
      {
         Excel::_ApplicationPtr spApplication = GetApplication();
         Excel::_WorkbookPtr spWorkbook = spApplication->Workbooks->Item[sWorkbookName.c_str()];
         return;
      }
      catch(const Workshare::Exception&)
      {
         //ignore
      }
      catch(...)
      {
         unexpected();
      }
      ::Sleep(100);
      iTryCount++;
   }
   throw Workshare::Com::ComException(_T("Failed to open workbook [") + sFilePathName + _T("], wait time expired"), E_FAIL);
}