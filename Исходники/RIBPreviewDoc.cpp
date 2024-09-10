void CRIBPreviewDoc::OnFileReload()
{
	// TODO: Add your command handler code here

	if ( !m_strPathName.empty() && m_strPathName[0] != '\0' ) {
		TRi *ri = ((CRIBPreviewApp *)AfxGetApp())->GetRenderer();
		if ( ri && m_contextHandle != NULL ) {
			try {
				ri->context(m_contextHandle);
				ri->end();
			} catch (TRendererError &t) {
				m_invalid = TRUE;
				t.displayMessage();
			} catch ( ... ) {
				m_invalid = TRUE;
				::MessageBox(NULL, "Error while reloading, RiEnd()/RiBegin()", "ERROR", MB_ICONEXCLAMATION|MB_OK) ;
			}

			if ( m_invalid ) {
				try {
					ri->synchronize(ri->RI_ABORT);
				} catch (TRendererError &t) {
					t.displayMessage();
				} catch ( ... ) {
					::MessageBox(NULL, "Error while reloading, RiESynchronize()", "ERROR", MB_ICONEXCLAMATION|MB_OK) ;
				}
			}
		}

		m_contextHandle = NULL;
		m_invalid = false;

		if ( ri ) {
			try {
				ri->begin();
				m_contextHandle = ri->getContext();
				m_invalid = m_contextHandle == NULL;
				ri->errorHandler(((CRIBPreviewApp *)AfxGetApp())->errorPrint);
			} catch (TRendererError &t) {
				m_invalid = TRUE;
				t.displayMessage();
				ri->synchronize(ri->RI_ABORT);
			} catch ( ... ) {
				m_invalid = TRUE;
				::MessageBox(NULL, "Error while reloading, RiEnd()/RiBegin()", "ERROR", MB_ICONEXCLAMATION|MB_OK) ;
			}
			if ( m_invalid ) {
				try {
					ri->synchronize(ri->RI_ABORT);
				} catch (TRendererError &t) {
					t.displayMessage();
				} catch ( ... ) {
					::MessageBox(NULL, "Error while reloading, RiEnd()/RiBegin()", "ERROR", MB_ICONEXCLAMATION|MB_OK) ;
				}
			}
			((CRIBPreviewApp *)AfxGetApp())->ClearLog();
		}
	}

	// Display views
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL) {
		CView* pView = GetNextView(pos);
		if ( pView ) {
			pView->InvalidateRect(NULL);
			pView->UpdateWindow();
		}
	}   
}