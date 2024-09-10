void CJevView::OnEditPaste()
{
	// TODO: Add your command handler code here
	TRACE( "Entering OnEditPaste()\n" );
	
	CJournalEntry JE;
	CJevDoc* pDoc;
	CString sText;

	
	pDoc = GetDocument();
	
	OpenClipboard();
	HGLOBAL hClipMemory = GetClipboardData( CF_TEXT );
	if( hClipMemory == NULL ) {
		TRACE( "OnEditPaste: GetClipboardData == NULL, Clip board empty\n" );
		CloseClipboard();
		return;
	}	
	
	HGLOBAL hGlobalMemory = GlobalAlloc( GHND, GlobalSize( hClipMemory ) );
	if( hGlobalMemory == NULL ) {
		TRACE( "OnEditPaste: GlobalAlloc on Clipboard Data Failed\n" );
		CloseClipboard();
		return;
	}	
		
	LPSTR lpClipMemory = (LPSTR) GlobalLock( hClipMemory );
	LPSTR lpGlobalMemory = (LPSTR) GlobalLock( hGlobalMemory );
	lstrcpy( lpGlobalMemory, lpClipMemory );
	GlobalUnlock( hClipMemory );	
	CloseClipboard();
	
/*	if( JE.Convert( lpGlobalMemory ) ) {
		pDoc->InsertAfterActiveRecord( JE );
	} else {
		TRACE( "OnEditPaste(): Paste failed.  Invalid Journal Entry Record\n");
	}
*/
	CString sClip, jeRecord;
	int retcode, i;

	sClip = lpGlobalMemory;
	while( (i = sClip.Find( "\r\n" ) ) >= 0 ) {
		jeRecord = sClip.Left( i );
		TRACE("OnEditPaste: jeRecord='%s'\n", jeRecord );
		retcode = JE.Convert( jeRecord );
		TRACE("OnEditPaste: JE.Convert() retcode=%d\n", retcode);
		if(retcode == 0) {
			TRACE( "OnEditPaste(): Paste failed.  Invalide Journal Entry Record\n");
			break;
		} else {
			pDoc->InsertAfterActiveRecord( JE );
		}
		sClip = sClip.Mid( i+2 );
	}
	
	GlobalUnlock( hGlobalMemory ); 
	
    CUpdateHint hint;
	pDoc->UpdateAllViews( NULL, HINT_INSERT_ACTIVE_RECORD, &hint );

			
	TRACE( "Leaving OnEditPaste()\n" );
	
}