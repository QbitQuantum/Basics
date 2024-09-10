/*----------------------------------------------------------------------------------------------
	Notifications
----------------------------------------------------------------------------------------------*/
bool NetworkTreeView::OnNotifyThis(int id, NMHDR * pnmh, long & lnRet)
{
	AssertPtr(pnmh);
	Assert(pnmh->hwndFrom == m_hwnd);

	switch (pnmh->code)
	{
	// The user has clicked to expand a tree item. If the item is a Group in the network,
	// we need to populate that node of the tree before showing it to the user.
	case TVN_ITEMEXPANDING:
		{
			NMTREEVIEW * pntv = reinterpret_cast<NMTREEVIEW *>(pnmh);
			if (TVE_EXPAND == pntv->action)
			{
				if (!m_fNetworkPopulated && m_hTreeNeighborhood && m_hTreeEntireNetwork)
				{
					m_fNetworkPopulated = true;
					// Enumerate that Network Neighborhood node and insert into the tree
					HANDLE hEnum;
					if (WNetOpenEnum(RESOURCE_CONTEXT, RESOURCETYPE_ANY, 0, NULL, &hEnum) ==
						NO_ERROR)
					{
						DWORD dwCount = 1;
						char szBuffer[kMax];
						char *psz = szBuffer;
						DWORD dwBufferSize = sizeof(szBuffer);

						achar szEntireNetwork[kMax];
						LoadString(ModuleEntry::GetModuleHandle(), kridNetEntireNetwork,
							szEntireNetwork, sizeof(szEntireNetwork));

						while (WNetEnumResource(hEnum, &dwCount, &szBuffer, &dwBufferSize) ==
							NO_ERROR)
						{
							NETRESOURCE * pnetResource = (NETRESOURCE*)psz;

							// Recognize the Entire Network node and populate it.
							if (pnetResource->lpComment && !_tcscmp(szEntireNetwork,
								pnetResource->lpComment))
							{
								_PopulateWorkgroups(m_hTreeEntireNetwork, pnetResource);
							}

							// Otherwise populate the machines in this local context
							else if (pnetResource->lpRemoteName && *pnetResource->lpRemoteName)
							{
								InsertItem(m_hTreeNeighborhood,
									_CreateDisplayableNetworkName(pnetResource->lpRemoteName),
									kridImageComputer);
							}
							dwBufferSize = sizeof(szBuffer);
						}
						WNetCloseEnum(hEnum);
					}
					m_hTreeNeighborhood = NULL;
					m_hTreeEntireNetwork = NULL;
				}
				_ExpandGroupNode(&pntv->itemNew);
			}
		}
		break;

	default:
		return false;
	}
	return false;
}