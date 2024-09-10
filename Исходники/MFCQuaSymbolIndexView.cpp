afx_msg void
MFCQuaSymbolIndexView::OnBeginDrag(NMHDR *pnmh, LRESULT* bHandled)
{
	cerr << "MFCQuaSymbolIndexView begin drag" << endl;
	NM_TREEVIEW* tvp = (NM_TREEVIEW*)pnmh;

	if (!draggingNow) {
		if  (tvp->itemNew.lParam > QSI_SYMBOL_LPARAM ) {
			StabEnt	*s = (StabEnt *)tvp->itemNew.lParam;
			bool	draggable = false;
			UINT	dragFormat = 0;
			switch (s->type) {
			case TypedValue::S_CLIP:	// move an instance
					draggable = true;
					dragFormat = QuaDrop::clipFormat;
					break;
				case TypedValue::S_INSTANCE:	// move an instance
					draggable = true;
					dragFormat = QuaDrop::instanceFormat;
					break;
				case TypedValue::S_SAMPLE:	// create a sample instance
					draggable = true;
					dragFormat = QuaDrop::sampleFormat;
					break;
				case TypedValue::S_VOICE:	// create a voice instance
					draggable = true;
					dragFormat = QuaDrop::voiceFormat;
					break;
			}
			if (!draggable) {
				*bHandled = TRUE;
				return;
			}

			COleDataSource srcItem;

			CTreeCtrl& tree = GetTreeCtrl();
			QuaDrop::SetSymbolSource(&srcItem, dragFormat, s);
			tree.Select(tvp->itemNew.hItem, TVGN_CARET);
			selectedItem = tvp->itemNew.hItem;
			srcItem.DoDragDrop();

		}
	}

	*bHandled = 0;
}