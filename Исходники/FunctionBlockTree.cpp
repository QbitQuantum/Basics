void FunctionBlockTree::OnTvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult)
{

	INXString csIconName = "";
	INXString csBlockName = "";

	//	if ( GetChildItem(m_hItemLeftClicked)== NULL) {
//			SetItemState( m_hItemLeftClicked, TVIS_SELECTED, TVIS_SELECTED );
	//	}

	if( !leafIsSelected() )
		// If he hasn't selected something draggable, don't let him carry 
		// on wasting his time.
		return;
	else{

	for (int i=0; i<m_iL2MenuSize; i++) {
		SetItemState( secondlev[i], !TVIS_SELECTED, TVIS_SELECTED );
	}

	// next check if a level3 item is selected
	for (int i=0; i<m_iL3MenuSize; i++) {
		SetItemState( thirdlev[i], !TVIS_SELECTED, TVIS_SELECTED );
	}
	// next check if a level3 item is selected
	for (int i=0; i<m_iL4MenuSize; i++) {
		SetItemState( forthlev[i], !TVIS_SELECTED, TVIS_SELECTED );
	}
	
	//if(m_hPrevItemClicked)
	//	SetItemState( m_hPrevItemClicked, !TVIS_SELECTED, TVIS_SELECTED );


	if(m_hItemClicked)
		SetItemState( m_hItemClicked, TVIS_SELECTED, TVIS_SELECTED );

		for (int i=0; i<m_iL2MenuSize; i++) {
			if (m_hItemClicked==secondlev[i]) {
				csIconName = m_csaL2IconName.GetAt(i);
				csBlockName = m_csaL2MenuName.GetAt(i);
			}
		}

		// next check if a level3 item is selected
		for (int i=0; i<m_iL3MenuSize; i++) {
			if (m_hItemClicked==thirdlev[i]) {
				csIconName = m_csaL3IconName.GetAt(i);
				csBlockName = m_csaL3MenuName.GetAt(i); // Needs to be set to trigger a subsystem drop action
			}
		}

		// next check if a level3 item is selected
		for (int i=0; i<m_iL4MenuSize; i++) {
			if (m_hItemClicked==forthlev[i]) {
				csIconName = m_csaL4IconName.GetAt(i);
				csBlockName = m_csaL4MenuName.GetAt(i);// Needs to be set to trigger a subsystem drop action
			}
		}


		LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

		//NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
		*pResult = 0;
#ifdef  LEGACY
		// Create the drag&drop source and data objects
		COleDropSource *pDropSource = new COleDropSource;
		COleDataSource *pDataSource = new COleDataSource;
#endif
		// now determine which rows are selected
		// here it's a dirty copy from the CodeGurus's 
		// CListCtrl section
		//int idx = GetSelectedItem(); 

		// nothing selected (must be for dragging)
		// or error while registering the clipboard format
		if (/*idx == -1 ||*/ !m_DragDropFormat) 
		{
			ASSERT(FALSE);
			return;
		}

		// now grab the data (here: the count and text)
		// and serialize it into an clipboard archive
		INXString Data;

		// getting the column count, thanks Zafir!
	//	CHeaderCtrl* pHeader = (CHeaderCtrl*)m_Table.GetDlgItem(0);

		//int number = m_Table.GetSelectedCount(),
		//	colCou = pHeader?pHeader->GetItemCount():0;
/* This is some rubbish serialisation that is needed to retrieve data from files in the draw windows etc.. !!! */
		TRY
		{
			CSharedFile file(GMEM_ZEROINIT|GMEM_DDESHARE|GMEM_MOVEABLE);
			TRY
			{
				CArchive ar(&file, CArchive::store);
				TRY
				{
					INXString format = AfxGetApp()->GetProfileString("DragDrop", "Clipformat", "Common");
					if (format == "Private")
					{
						ar << (CString)csIconName;
						ar << (CString)csBlockName;
					}
					else // common data format
					{
						ar.WriteString( csIconName + "\n" + csBlockName + "\n" );
					}
					ar.Close();
				}
				CATCH_ALL(eInner)
				{
					// exception while writing into or closing the archive
					ASSERT(FALSE);
				}
				END_CATCH_ALL;
			}
			CATCH_ALL(eMiddle)
			{
				// exception in the destructor of ar
				ASSERT(FALSE);
			}
			END_CATCH_ALL;

			// put the file object into the data object
#ifdef LEGACY
			pDataSource->CacheGlobalData(m_DragDropFormat, file.Detach());
			pDataSource->DoDragDrop(DROPEFFECT_MOVE|DROPEFFECT_COPY, NULL, pDropSource);
#endif
		}
		CATCH_ALL(eOuter)
		{
			// exception while destructing the file
			ASSERT(FALSE);
		}
		END_CATCH_ALL;
#ifdef LEGACY
		delete pDropSource;
		delete pDataSource;
#endif
		*pResult = 0;

	} //	if( leafIsSelected() )
}