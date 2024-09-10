//---------------------------------------------------------------------------
BOOL ReportView::OnPreparePrinting(CPrintInfo* pInfo)
{
	if(pInfo->m_bPreview) {
		return this->DoPreparePrinting(pInfo);
	}
	
	//if(!mPrintMultiple) {

		pInfo->m_bDirect = this->mPrintDirect;

		this->GetParentFrame()->SetActiveWindow();
		this->GetParentFrame()->BringWindowToTop();
		//this->SetActiveWindow();
		//this->BringWindowToTop();
		return this->DoPreparePrinting(pInfo);
	//}


	// printing from print multiple reports


   C_Main_Frame* lMainFramePtr = MainFramePtr();

   if (mDibViewPtr == NULL) {
		mDibViewPtr = lMainFramePtr->Create_Dib_Window();
   }

   CWnd* lFramePtr = this->GetParent();
   ASSERT( lFramePtr != NULL );

   //--- Save existing placement ---
   
   WINDOWPLACEMENT   lSavePlacement;
   lFramePtr->GetWindowPlacement( & lSavePlacement );

   //--- Compute and set print placement ---

   /*lFramePtr->ShowWindow( SW_RESTORE );
   this->ResizeParentToFit( FALSE );*/

   WINDOWPLACEMENT   lPrintPlacement;
   lFramePtr->GetWindowPlacement( & lPrintPlacement );

 // JTK - Commented out to fix print preview issue  
   /*lPrintPlacement.rcNormalPosition.right  -= lPrintPlacement.rcNormalPosition.left;
   lPrintPlacement.rcNormalPosition.bottom -= lPrintPlacement.rcNormalPosition.top ;

   lPrintPlacement.rcNormalPosition.left  = 0;
   lPrintPlacement.rcNormalPosition.top   = 0;
   lFramePtr->MoveWindow(&lPrintPlacement.rcNormalPosition);
   lFramePtr->SetWindowPlacement( & lPrintPlacement );*/
   
   //--- Create the DIB ---
   lFramePtr->SetActiveWindow();
   lFramePtr->BringWindowToTop();
   lFramePtr->UpdateWindow();
   mDibViewPtr->LoadDib(lFramePtr);
   
   //--- Call normal printing ---
   
   pInfo->m_bDirect = mPrintDirect;
   BOOL lPrintResult = mDibViewPtr->OnPreparePrinting( pInfo );  
   
   //--- Restore the window ---

   lFramePtr->SetWindowPlacement( & lSavePlacement );
   lFramePtr->ShowWindow( lSavePlacement.showCmd );
   lFramePtr->UpdateWindow();
   
   return lPrintResult;  
}