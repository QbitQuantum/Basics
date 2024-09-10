void CUser::MerchantItemBuy(Packet & pkt)
{
	uint32 itemid, req_gold;
	uint16 item_count, leftover_count;
	uint8 item_slot, dest_slot, rob_slot;

	CUser *pMerchant = g_pMain->GetUserPtr(m_sMerchantsSocketID),
		*pUser = g_pMain->GetUserPtr(GetID());
	if (pMerchant == nullptr)
		return;

	pkt >> itemid >> item_count >> item_slot >> dest_slot >> rob_slot;

	// Make sure the slots are correct and that we're actually buying at least 1 item.
	if (item_slot >= MAX_MERCH_ITEMS
		|| dest_slot >= HAVE_MAX
		|| item_count == 0)
		return;

	// Grab pointers to the items.
	_MERCH_DATA *pMerch = &pMerchant->m_arMerchantItems[item_slot];
	_ITEM_DATA *pItem = GetItem(SLOT_MAX + dest_slot);
	_ITEM_DATA *pItemRob = &pMerchant->m_sItemArray[pMerch->bOriginalSlot];

	// Make sure the merchant actually has that item in that slot
	// and that they have enough
	if (pMerch->nNum != itemid
		|| pMerch->sCount < item_count)
		return;

	// If it's not stackable, and we're specifying something other than 1
	// we really don't care to handle this request...
	_ITEM_TABLE *proto = g_pMain->GetItemPtr(itemid);
	if (proto == nullptr
		|| !proto->m_bCountable && item_count != 1)
		return;

	// Do we have enough coins?
	req_gold = pMerch->nPrice * item_count;
	if (m_iGold < req_gold)
		return;

	// If the slot's not empty
	if (pItem->nNum != 0 
		// and we already have an item that isn't the same item
			// or it's the same item but the item's not stackable...
				&& (pItem->nNum != itemid || !proto->m_bCountable))
				return;

	leftover_count = pMerch->sCount - item_count;
	pMerchant->GoldChange(GetSocketID(), req_gold);
	pItem->nNum = itemid;
	pItem->sCount += item_count;
	pItem->sDuration = pMerch->sDuration;
	pItem->nSerialNum = pMerch->nSerialNum;

	pMerch->sCount -= item_count;
	pMerch->bCount -= item_count;
	
	if (pMerch->sCount == 0 && pMerch->bCount == 0)
	memset(pItemRob, 0, sizeof(_ITEM_DATA));
	else
		pItemRob->sCount = pMerch->sCount;

	SendStackChange(itemid, pItem->sCount, pItem->sDuration, dest_slot, 
		(pItem->sCount == item_count)); // is it a new item?

	pMerchant->SendStackChange(itemid, pMerch->bCount, pMerch->sDuration,
		pMerch->bOriginalSlot- SLOT_MAX);

	if (pMerch->sCount == 0 && pMerch->bCount == 0)
		memset(pMerch, 0, sizeof(_MERCH_DATA));
	else if (pMerch->bCount == 0 && pMerch->bCount != 0) // Countable item protect.
		pMerch->IsSoldOut = true;

	Packet result(WIZ_MERCHANT, uint8(MERCHANT_ITEM_PURCHASED));
	result << itemid << GetName();
	pMerchant->Send(&result);

	result.clear();

	result	<< uint8(MERCHANT_ITEM_BUY) << uint16(1)
		<< itemid << leftover_count
		<< item_slot << dest_slot;
	Send(&result);

	if (item_slot < 4 && leftover_count == 0)
	{
		result.Initialize(WIZ_MERCHANT_INOUT);
		result << uint8(2) << m_sMerchantsSocketID << uint8(1) << uint8(0) << item_slot;
		pMerchant->SendToRegion(&result);
	}

	g_pMain->MerchantUserInOutForMe(pMerchant);
	g_pMain->MerchantUserInOutForMe(pUser);

	int nItemsRemaining = 0;
	for (int i = 0; i < MAX_MERCH_ITEMS; i++)
	{
		if (pMerchant->m_arMerchantItems[i].nNum != 0 && !pMerchant->m_arMerchantItems[i].IsSoldOut)
			nItemsRemaining++;
	}

	if (nItemsRemaining == 0)
		pMerchant->MerchantClose();
}			