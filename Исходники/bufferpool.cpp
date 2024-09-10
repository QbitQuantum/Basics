TItem* CItemPool::PickFreeItem()
{
	TItem* pItem = nullptr;

	if(m_lsFreeItem.Size() > 0)
	{
		CCriSecLock locallock(m_csFreeItem);

		if(m_lsFreeItem.Size() > 0)
			pItem = m_lsFreeItem.PopFront();
	}

	if(pItem == nullptr)
		pItem = TItem::Construct(m_heap, m_dwItemCapacity);
	else
		pItem->Reset();

	return pItem;
}