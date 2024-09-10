void CEx24dView::OnExceloleExecute() 
{
   LPDISPATCH pRange, pWorkbooks;
    
   CWnd* pWnd = CWnd::FindWindow("XLMAIN", NULL);
   if (pWnd != NULL) {
     TRACE("Excel window found\n");
     pWnd->ShowWindow(SW_SHOWNORMAL);
     pWnd->UpdateWindow();
     pWnd->BringWindowToTop();
   }

   m_app.SetSheetsInNewWorkbook(1);
   
   VERIFY(pWorkbooks = m_app.GetWorkbooks());
   m_workbooks.AttachDispatch(pWorkbooks);

   LPDISPATCH pWorkbook = NULL;
   if (m_workbooks.GetCount() == 0) {
      // Add returns a Workbook pointer, but we
      //  don't have a Workbook class
      pWorkbook = m_workbooks.Add(); // Save the pointer for
                                     //  later release
   }
   LPDISPATCH pWorksheets = m_app.GetWorksheets();
   ASSERT(pWorksheets != NULL);
   m_worksheets.AttachDispatch(pWorksheets);
   LPDISPATCH pWorksheet = m_worksheets.GetItem(COleVariant((short) 1));

   m_worksheet.AttachDispatch(pWorksheet);
   m_worksheet.Select();

   VERIFY(pRange = m_worksheet.GetRange(COleVariant("A1")));
   m_range[0].AttachDispatch(pRange);

   VERIFY(pRange = m_worksheet.GetRange(COleVariant("A2")));
   m_range[1].AttachDispatch(pRange);
   
   VERIFY(pRange = m_worksheet.GetRange(COleVariant("A3")));
   m_range[2].AttachDispatch(pRange);

   VERIFY(pRange = m_worksheet.GetRange(COleVariant("A3"), 
	   COleVariant("C5")));
   m_range[3].AttachDispatch(pRange);

   VERIFY(pRange = m_worksheet.GetRange(COleVariant("A6")));
   m_range[4].AttachDispatch(pRange);
   
   m_range[4].SetValue(COleVariant(COleDateTime(1994, 4, 24, 15, 47, 8)));
   // retrieve the stored date and print it as a string
   COleVariant vaTimeDate = m_range[4].GetValue();
   TRACE("returned date type = %d\n", vaTimeDate.vt);
   COleVariant vaTemp;
   vaTemp.ChangeType(VT_BSTR, &vaTimeDate);
   CString str = vaTemp.bstrVal;
   TRACE("date = %s\n", (const char*) str);

   m_range[0].SetValue(COleVariant("test string"));
   
   COleVariant vaResult0 = m_range[0].GetValue();
   if (vaResult0.vt == VT_BSTR) {
     CString str = vaResult0.bstrVal;
     TRACE("vaResult0 = %s\n", (const char*) str);
   }

   m_range[1].SetValue(COleVariant(3.14159));
   
   COleVariant vaResult1 = m_range[1].GetValue();
   if (vaResult1.vt == VT_R8) {
     TRACE("vaResult1 = %f\n", vaResult1.dblVal);
   }
   
   m_range[2].SetFormula(COleVariant("=$A2*2.0"));
   
   COleVariant vaResult2 = m_range[2].GetValue();
   if (vaResult2.vt == VT_R8) {
     TRACE("vaResult2 = %f\n", vaResult2.dblVal);
   }

   COleVariant vaResult2a = m_range[2].GetFormula();
   if (vaResult2a.vt == VT_BSTR) {
     CString str = vaResult2a.bstrVal;
     TRACE("vaResult2a = %s\n", (const char*) str);
   }
   
   m_range[3].FillRight();
   m_range[3].FillDown();
   
// cleanup  
    if (pWorkbook != NULL) {
	    pWorkbook->Release();
   }
}