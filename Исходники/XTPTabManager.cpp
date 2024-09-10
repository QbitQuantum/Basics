void CXTPTabManager::ReOrder(HWND hWnd, CPoint pt, CXTPTabManagerItem* pItem)
{
	CXTPTabManagerItem* pSelected = m_pSelected;
	m_pSelected = pItem;

	if (GetPaintManager()->m_bHotTracking)
		m_pHighlighted = pItem;

	Reposition();

	CArray<CRect, CRect&> arrRects;

	for (int j = 0; j < GetItemCount(); j++)
	{
		CRect rc = GetItem(j)->GetRect();
		arrRects.Add(rc);
	}

	int nIndex = pItem->GetIndex();

	::SetCapture(hWnd);

	while (::GetCapture() == hWnd)
	{
		MSG msg;
		VERIFY(::GetMessage(&msg, NULL, 0, 0));

		if (::GetCapture() != hWnd)
		{
			DispatchMessage (&msg);
			break;
		}
		switch (msg.message)
		{
			case WM_MOUSEMOVE:
				{
					pt = CPoint((short signed)LOWORD(msg.lParam), (short signed)HIWORD(msg.lParam));

					for (int i = 0; i < arrRects.GetSize(); i++)
					{
						if (i != pItem->GetIndex() && arrRects[i].PtInRect(pt))
						{

							while (i != pItem->GetIndex())
							{
								int j = i < pItem->GetIndex() ? pItem->GetIndex() - 1 : pItem->GetIndex() + 1;

								CXTPTabManagerItem* p1 = pItem;
								CXTPTabManagerItem* p2 = m_arrItems[pItem->GetIndex()] = m_arrItems[j];
								m_arrItems[j] = p1;

								OnItemsChanged();

								OnSwitchItem(p1, p2);
							}
							break;
						}
					}
				}

				break;

			case WM_KEYDOWN:
				if (msg.wParam != VK_ESCAPE)
					break;
			case WM_CANCELMODE:
			case WM_LBUTTONUP:
			case WM_RBUTTONDOWN:
				goto ExitLoop;

			default:
				DispatchMessage (&msg);
				break;
		}
	}

ExitLoop:
	ReleaseCapture();
	PerformMouseMove(hWnd, pt);

	m_pSelected = pSelected;
	OnItemClick(pItem);

	if (nIndex != pItem->GetIndex())
	{
		OnItemOrderChanged(pItem, nIndex, pItem->GetIndex());
	}
}