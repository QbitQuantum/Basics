//*******************************************************************************
void CBCGPDiagramVisualContainer::UpdateItems (CItemIDList& lst, BOOL bRedraw)
{
	if (m_bInsideUpdateItems)
	{
// 		for (POSITION pos = lst.GetHeadPosition (); pos != NULL; )
// 		{
// 			CBCGPBaseVisualObject* pObject = GetItem (lst.GetNext (pos));
// 			if (pObject != NULL)
// 			{
// 				ASSERT_VALID(pObject);
// 				pObject->SetDirty (TRUE, bRedraw);
// 			}
// 		}
		return;
	}

	m_bInsideUpdateItems = TRUE;

	for (POSITION pos = lst.GetHeadPosition (); pos != NULL; )
	{
		CBCGPBaseVisualObject* pObject = GetItem (lst.GetNext (pos));
		CBCGPDiagramConnector* pConnector = DYNAMIC_DOWNCAST(CBCGPDiagramConnector, pObject);

		if (pConnector != NULL)
		{
			pConnector->SetRect (pConnector->GetBoundsRect (), bRedraw);
		}
		else if (pObject != NULL)
		{
			ASSERT_VALID(pObject);
			pObject->SetDirty (TRUE, bRedraw);
		}
	}

	m_bInsideUpdateItems = FALSE;
}