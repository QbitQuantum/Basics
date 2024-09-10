void CSharedFilesCtrl::OnDrawItem( int item, wxDC* dc, const wxRect& rect, const wxRect& rectHL, bool highlighted )
{
	CKnownFile *file = (CKnownFile*)GetItemData(item);
	wxASSERT( file );

	if ( highlighted ) {
		CMuleColour newcol(GetFocus() ? wxSYS_COLOUR_HIGHLIGHT : wxSYS_COLOUR_BTNSHADOW);	
		dc->SetBackground(newcol.Blend(125).GetBrush());
		dc->SetTextForeground( CMuleColour(wxSYS_COLOUR_HIGHLIGHTTEXT));
		// The second blending goes over the first one.
		dc->SetPen(newcol.Blend(65).GetPen());
	} else {
		dc->SetBackground( CMuleColour(wxSYS_COLOUR_LISTBOX).GetBrush() );
		dc->SetTextForeground(CMuleColour(wxSYS_COLOUR_WINDOWTEXT));
		dc->SetPen(*wxTRANSPARENT_PEN);
	}
	
	dc->SetBrush(dc->GetBackground());
	dc->DrawRectangle(rectHL);
	dc->SetPen(*wxTRANSPARENT_PEN);

	// Offset based on the height of the fonts
	const int textVOffset = ( rect.GetHeight() - dc->GetCharHeight() ) / 2;
	// Empty space to each side of a column
	const int SPARE_PIXELS_HORZ	= 4;

	// The leftmost position of the current column
	int columnLeft = 0;
	
	for ( int i = 0; i < GetColumnCount(); ++i ) {
		const int columnWidth = GetColumnWidth(i);

		if (columnWidth > 2*SPARE_PIXELS_HORZ) {
			wxRect columnRect(
				columnLeft + SPARE_PIXELS_HORZ, rect.y,
				columnWidth - 2 * SPARE_PIXELS_HORZ, rect.height);
			
			wxDCClipper clipper(*dc, columnRect);
			
			wxString textBuffer;
			switch ( i ) {
				case ID_SHARED_COL_NAME:
					textBuffer = file->GetFileName().GetPrintable();

					if (file->GetFileRating() || file->GetFileComment().Length()) {
						int image = Client_CommentOnly_Smiley;
						if (file->GetFileRating()) {
							image = Client_InvalidRating_Smiley + file->GetFileRating() - 1;
						}	
							
						wxASSERT(image >= Client_InvalidRating_Smiley);
						wxASSERT(image <= Client_CommentOnly_Smiley);

						int imgWidth = 16;
						
						theApp->amuledlg->m_imagelist.Draw(image, *dc, columnRect.x,
								columnRect.y + 1, wxIMAGELIST_DRAW_TRANSPARENT);

						// Move the text to the right
						columnRect.x += (imgWidth + 4);
					}

					break;
				
				case ID_SHARED_COL_SIZE:
					textBuffer = CastItoXBytes(file->GetFileSize());
					break;

				case ID_SHARED_COL_TYPE:
					textBuffer = GetFiletypeByName(file->GetFileName());
					break;

				case ID_SHARED_COL_PRIO:
					textBuffer = PriorityToStr(file->GetUpPriority(), file->IsAutoUpPriority());
					break;

				case ID_SHARED_COL_ID:
					textBuffer = file->GetFileHash().Encode();
					break;
				
				case ID_SHARED_COL_REQ:
					textBuffer = CFormat(wxT("%u (%u)"))
							% file->statistic.GetRequests()
							% file->statistic.GetAllTimeRequests();
					break;

				case ID_SHARED_COL_AREQ:
					textBuffer = CFormat(wxT("%u (%u)"))
							% file->statistic.GetAccepts()
							% file->statistic.GetAllTimeAccepts();
					break;

				case ID_SHARED_COL_TRA:
					textBuffer = CastItoXBytes(file->statistic.GetTransferred())
						+ wxT(" (") + CastItoXBytes(file->statistic.GetAllTimeTransferred()) + wxT(")");
					break;
					
				case ID_SHARED_COL_RTIO:
					textBuffer = CFormat(wxT("%.2f")) %	((double)file->statistic.GetAllTimeTransferred() / file->GetFileSize());
					break;
				
				case ID_SHARED_COL_PART:
					if ( file->GetPartCount() ) {
						wxRect barRect(columnRect.x, columnRect. y + 1, 
							columnRect.width, columnRect.height - 2);
						
						DrawAvailabilityBar(file, dc, barRect);
					}
					break;
				
				case ID_SHARED_COL_CMPL:
					if ( file->m_nCompleteSourcesCountLo == 0 ) {
						if ( file->m_nCompleteSourcesCountHi ) {
							textBuffer = CFormat(wxT("< %u")) % file->m_nCompleteSourcesCountHi;
						} else {
							textBuffer = wxT("0");
						}
					} else if (file->m_nCompleteSourcesCountLo == file->m_nCompleteSourcesCountHi) {
						textBuffer = CFormat(wxT("%u")) % file->m_nCompleteSourcesCountLo;
					} else {
						textBuffer = CFormat(wxT("%u - %u")) % file->m_nCompleteSourcesCountLo % file->m_nCompleteSourcesCountHi;
					}
					
					break;				
				
				case ID_SHARED_COL_PATH:
					if ( file->IsPartFile() ) {
						textBuffer = _("[PartFile]");
					} else {
						textBuffer = file->GetFilePath().GetPrintable();
					}
			}

			if (!textBuffer.IsEmpty()) {
				dc->DrawText(textBuffer, columnRect.x, columnRect.y + textVOffset);
			}
		}

		// Move to the next column
		columnLeft += columnWidth;
	}
}