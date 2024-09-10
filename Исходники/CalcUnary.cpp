void CCalcUnary::OnDeterminant() 
{
	// TODO: Add your control notification handler code here
        // TODO: Add your control notification handler code here
        UpdateData();
        xpMatrix  mtx;
        CWaitCursor wait;
		float ret = 0;
        //invert the matrix
        try
        {
           //CAllPages * pParent = STATIC_DOWNCAST(CAllPages, GetParent());
		   char buffer[255];
           if (getMatrix(mtx) == TRUE)
           {
              wait.Restore( );
			  m_det = gcvt(mtx.getDet(),10, buffer);
              //m_det = _gcvt(mtx.getDet());
           }
		   UpdateData(false);	
           //pParent->m_pMtx = &m_mtxResult;
           //pParent->SetActivePage(0);
           //pParent->m_calcResults.pGridCtrl->Refresh();
        }
        catch (xpException * e)
        {
           CString errMess;
           e->getErrorMessage(errMess);
           MessageBox(errMess, "Matrix Calculation Error", MB_OK);
           e->Delete();
        }
	
}