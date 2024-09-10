// NOTE: Cut from UtlFixedLinkedList<>, UNDONE: Find a way to share this code
void CBaseEntityList::CEntInfoList::LinkBefore( CEntInfo *pBefore, CEntInfo *pElement )
{
	Assert( pElement );
	
	// Unlink it if it's in the list at the moment
	Unlink(pElement);
	
	// The element *after* our newly linked one is the one we linked before.
	pElement->m_pNext = pBefore;
	
	if (pBefore == NULL)
	{
		// In this case, we're linking to the end of the list, so reset the tail
		pElement->m_pPrev = m_pTail;
		m_pTail = pElement;
	}
	else
	{
		// Here, we're not linking to the end. Set the prev pointer to point to
		// the element we're linking.
		Assert( IsInList(pBefore) );
		pElement->m_pPrev = pBefore->m_pPrev;
		pBefore->m_pPrev = pElement;
	}
	
	// Reset the head if we linked to the head of the list
	if (pElement->m_pPrev == NULL)
	{
		m_pHead = pElement;
	}
	else
	{
		pElement->m_pPrev->m_pNext = pElement;
	}
}