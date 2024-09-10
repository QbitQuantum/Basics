void CUIListBox::OnLButtonDown(POINT point)
{
	SetFocus();
	if (m_ScrollBar.ContainsPoint(point))
	{
		m_ScrollBar.OnLButtonDown(point);
		return;
	}
	int nClicked = getItemIndexByPoint(point);
	if (nClicked!=-1)
	{
		SetPressed(true);
		m_nSelected = nClicked;

			//if(!(wParam & MK_SHIFT))??????????????????
			//	m_nSelStart = m_nSelected;??????????????????

			// If this is a multi-selection listbox, update per-item
			// selection data.

			/**if(m_dwStyle & MULTISELECTION)
			{
				// Determine behavior based on the state of Shift and Ctrl

				UIListBoxItem *pSelItem = m_Items[m_nSelected];
				if((wParam & (MK_SHIFT|MK_CONTROL)) == MK_CONTROL)
				{
					// Control click. Reverse the selection of this item.

					pSelItem->bSelected = !pSelItem->bSelected;
				}
				else if((wParam & (MK_SHIFT|MK_CONTROL)) == MK_SHIFT)
				{
					// Shift click. Set the selection for all items
					// from last selected item to the current item.
					// Clear everything else.

					int nBegin = __min(m_nSelStart, m_nSelected);
					int nEnd = __max(m_nSelStart, m_nSelected);

					for(int i = 0; i < nBegin; ++i)
					{
						UIListBoxItem *pItem = m_Items[i];
						pItem->bSelected = false;
					}

					for(int i = nEnd + 1; i < (int)m_Items.size(); ++i)
					{
						UIListBoxItem *pItem = m_Items[i];
						pItem->bSelected = false;
					}

					for(int i = nBegin; i <= nEnd; ++i)
					{
						UIListBoxItem *pItem = m_Items[i];
						pItem->bSelected = true;
					}
				}
				else if((wParam & (MK_SHIFT|MK_CONTROL)) == (MK_SHIFT|MK_CONTROL))
				{
					// Control-Shift-click.

					// The behavior is:
					//   Set all items from m_nSelStart to m_nSelected to
					//     the same state as m_nSelStart, not including m_nSelected.
					//   Set m_nSelected to selected.

					int nBegin = __min(m_nSelStart, m_nSelected);
					int nEnd = __max(m_nSelStart, m_nSelected);

					// The two ends do not need to be set here.

					bool bLastSelected = m_Items[m_nSelStart]->bSelected;
					for(int i = nBegin + 1; i < nEnd; ++i)
					{
						UIListBoxItem *pItem = m_Items[i];
						pItem->bSelected = bLastSelected;
					}

					pSelItem->bSelected = true;

					// Restore m_nSelected to the previous value
					// This matches the Windows behavior

					m_nSelected = m_nSelStart;
				}
				else
				{
					// Simple click.  Clear all items and select the clicked
					// item.


					for(int i = 0; i < (int)m_Items.size(); ++i)
					{
						UIListBoxItem *pItem = m_Items[i];
						pItem->bSelected = false;
					}

					pSelItem->bSelected = true;
				}
			}*/  // End of multi-selection case

			sendEvent(EVENT_LISTBOX_SELECTION);
	}
}