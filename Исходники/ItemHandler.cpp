void CUser::WarehouseProcess(Packet & pkt)
{
	Packet result(WIZ_WAREHOUSE);
	CNpc * pNpc;
	uint32 itemid, count;
	uint16 npcid, reference_pos;
	uint8 page, srcpos, destpos;
	_ITEM_TABLE* pTable = nullptr;
	uint8 command = pkt.read<uint8>();
	bool bResult = false;

	if (isDead())
		return;

	if (isTrading())
		goto fail_return;

	if (command == WAREHOUSE_OPEN)
	{
		result << uint8(WAREHOUSE_OPEN) << uint8(WAREHOUSE_OPEN) << GetInnCoins();
		for (int i = 0; i < WAREHOUSE_MAX; i++)
		{
			_ITEM_DATA *pItem = &m_sWarehouseArray[i];
			result	<< pItem->nNum << pItem->sDuration << pItem->sCount
					<< uint8(0) << uint16(0) << uint16(0) << uint16(0) << uint16(0);
		}
		Send(&result);
		return;
	}

	pkt >> npcid >> itemid >> page >> srcpos >> destpos;

	pNpc = g_pMain->m_arNpcArray.GetData(npcid);
	if (pNpc == nullptr
		|| pNpc->GetType() != NPC_WAREHOUSE
		|| !isInRange(pNpc, MAX_NPC_RANGE))
		goto fail_return;

	pTable = g_pMain->GetItemPtr( itemid );
	if( !pTable ) goto fail_return;
	reference_pos = 24 * page;

	// TO-DO: Clean up this entire method. It's horrendous!
	switch (command)
	{
	/* stuff going into the inn */
	case WAREHOUSE_INPUT:
		pkt >> count;

		// Handle coin input.
		if (itemid == ITEM_GOLD)
		{
			if (!hasCoins(count)
				|| GetInnCoins() + count > COIN_MAX)
				goto fail_return;

			m_iBank += count;
			m_iGold -= count;
			break;
		}

		if (srcpos > HAVE_MAX
			|| reference_pos + destpos > WAREHOUSE_MAX
			|| itemid >= ITEM_NO_TRADE) // Cannot be traded, sold or stored (note: don't check the race, as these items CAN be stored).
			goto fail_return;

		if (m_sItemArray[SLOT_MAX+srcpos].isSealed()
			|| m_sItemArray[SLOT_MAX+srcpos].isRented())
			goto fail_return;

		if( m_sItemArray[SLOT_MAX+srcpos].nNum != itemid ) goto fail_return;
		if( m_sWarehouseArray[reference_pos+destpos].nNum && !pTable->m_bCountable ) goto fail_return;
		if( m_sItemArray[SLOT_MAX+srcpos].sCount < count ) goto fail_return;
		m_sWarehouseArray[reference_pos+destpos].nNum = itemid;
		m_sWarehouseArray[reference_pos+destpos].sDuration = m_sItemArray[SLOT_MAX+srcpos].sDuration;
		m_sWarehouseArray[reference_pos+destpos].nSerialNum = m_sItemArray[SLOT_MAX+srcpos].nSerialNum;
		if( pTable->m_bCountable == 0 && m_sWarehouseArray[reference_pos+destpos].nSerialNum == 0 )
			m_sWarehouseArray[reference_pos+destpos].nSerialNum = g_pMain->GenerateItemSerial();

		if( pTable->m_bCountable ) {
			m_sWarehouseArray[reference_pos+destpos].sCount += (unsigned short)count;
		}
		else {
			m_sWarehouseArray[reference_pos+destpos].sCount = m_sItemArray[SLOT_MAX+srcpos].sCount;
		}

		if( !pTable->m_bCountable ) {
			m_sItemArray[SLOT_MAX+srcpos].nNum = 0;
			m_sItemArray[SLOT_MAX+srcpos].sDuration = 0;
			m_sItemArray[SLOT_MAX+srcpos].sCount = 0;
			m_sItemArray[SLOT_MAX+srcpos].nSerialNum = 0;
		}
		else {
			m_sItemArray[SLOT_MAX+srcpos].sCount -= (unsigned short)count;
			if( m_sItemArray[SLOT_MAX+srcpos].sCount <= 0 ) {
				m_sItemArray[SLOT_MAX+srcpos].nNum = 0;
				m_sItemArray[SLOT_MAX+srcpos].sDuration = 0;
				m_sItemArray[SLOT_MAX+srcpos].sCount = 0;
				m_sItemArray[SLOT_MAX+srcpos].nSerialNum = 0;
			}
		}

		SendItemWeight();
		break;

	/* stuff being taken out of the inn */
	case WAREHOUSE_OUTPUT:
		pkt >> count;

		if (itemid == ITEM_GOLD)
		{
			if (!hasInnCoins(count)
				|| GetCoins() + count > COIN_MAX)
				goto fail_return;

			m_iGold += count;
			m_iBank -= count;
			break;
		}

		if (reference_pos + srcpos > WAREHOUSE_MAX
			|| destpos > HAVE_MAX)
			goto fail_return;

		if (pTable->m_bCountable) {	// Check weight of countable item.
			if (((pTable->m_sWeight * count)   + m_sItemWeight) > m_sMaxWeight) {			
				goto fail_return;
			}
		}
		else {	// Check weight of non-countable item.
			if ((pTable->m_sWeight + m_sItemWeight) > m_sMaxWeight) {
				goto fail_return;
			}
		}		

		if( m_sWarehouseArray[reference_pos+srcpos].nNum != itemid ) goto fail_return;
		if( m_sItemArray[SLOT_MAX+destpos].nNum && !pTable->m_bCountable ) goto fail_return;
		if( m_sWarehouseArray[reference_pos+srcpos].sCount < count ) goto fail_return;
		m_sItemArray[SLOT_MAX+destpos].nNum = itemid;
		m_sItemArray[SLOT_MAX+destpos].sDuration = m_sWarehouseArray[reference_pos+srcpos].sDuration;
		m_sItemArray[SLOT_MAX+destpos].nSerialNum = m_sWarehouseArray[reference_pos+srcpos].nSerialNum;
		if( pTable->m_bCountable )
			m_sItemArray[SLOT_MAX+destpos].sCount += (unsigned short)count;
		else {
			if( m_sItemArray[SLOT_MAX+destpos].nSerialNum == 0 )
				m_sItemArray[SLOT_MAX+destpos].nSerialNum = g_pMain->GenerateItemSerial();
			m_sItemArray[SLOT_MAX+destpos].sCount = m_sWarehouseArray[reference_pos+srcpos].sCount;
		}
		if( !pTable->m_bCountable ) {
			m_sWarehouseArray[reference_pos+srcpos].nNum = 0;
			m_sWarehouseArray[reference_pos+srcpos].sDuration = 0;
			m_sWarehouseArray[reference_pos+srcpos].sCount = 0;
			m_sWarehouseArray[reference_pos+srcpos].nSerialNum = 0;
		}
		else {
			m_sWarehouseArray[reference_pos+srcpos].sCount -= (unsigned short)count;
			if( m_sWarehouseArray[reference_pos+srcpos].sCount <= 0 ) {
				m_sWarehouseArray[reference_pos+srcpos].nNum = 0;
				m_sWarehouseArray[reference_pos+srcpos].sDuration = 0;
				m_sWarehouseArray[reference_pos+srcpos].sCount = 0;
				m_sWarehouseArray[reference_pos+srcpos].nSerialNum = 0;
			}
		}

		SendItemWeight();		
		//TRACE("WARE OUTPUT : %s %s %d %d %d %d %d", m_id, m_Accountid, ITEM_WAREHOUSE_GET, 0, itemid, count, m_sItemArray[SLOT_MAX+destpos].sDuration );
		break;
	case WAREHOUSE_MOVE:
		if( reference_pos+srcpos > WAREHOUSE_MAX ) goto fail_return;
		if( m_sWarehouseArray[reference_pos+srcpos].nNum != itemid ) goto fail_return;
		if( m_sWarehouseArray[reference_pos+destpos].nNum ) goto fail_return;
		m_sWarehouseArray[reference_pos+destpos].nNum = itemid;
		m_sWarehouseArray[reference_pos+destpos].sDuration = m_sWarehouseArray[reference_pos+srcpos].sDuration;
		m_sWarehouseArray[reference_pos+destpos].sCount = m_sWarehouseArray[reference_pos+srcpos].sCount;
		m_sWarehouseArray[reference_pos+destpos].nSerialNum = m_sWarehouseArray[reference_pos+srcpos].nSerialNum;

		m_sWarehouseArray[reference_pos+srcpos].nNum = 0;
		m_sWarehouseArray[reference_pos+srcpos].sDuration = 0;
		m_sWarehouseArray[reference_pos+srcpos].sCount = 0;
		m_sWarehouseArray[reference_pos+srcpos].nSerialNum = 0;
		break;
	case WAREHOUSE_INVENMOVE:
		if( itemid != m_sItemArray[SLOT_MAX+srcpos].nNum )
			goto fail_return;
		{
			short duration = m_sItemArray[SLOT_MAX+srcpos].sDuration;
			short itemcount = m_sItemArray[SLOT_MAX+srcpos].sCount;
			uint64 serial = m_sItemArray[SLOT_MAX+srcpos].nSerialNum;
			m_sItemArray[SLOT_MAX+srcpos].nNum = m_sItemArray[SLOT_MAX+destpos].nNum;
			m_sItemArray[SLOT_MAX+srcpos].sDuration = m_sItemArray[SLOT_MAX+destpos].sDuration;
			m_sItemArray[SLOT_MAX+srcpos].sCount = m_sItemArray[SLOT_MAX+destpos].sCount;
			m_sItemArray[SLOT_MAX+srcpos].nSerialNum = m_sItemArray[SLOT_MAX+destpos].nSerialNum;

			m_sItemArray[SLOT_MAX+destpos].nNum = itemid;
			m_sItemArray[SLOT_MAX+destpos].sDuration = duration;
			m_sItemArray[SLOT_MAX+destpos].sCount = itemcount;
			m_sItemArray[SLOT_MAX+destpos].nSerialNum = serial;
		}
		break;
	}

	bResult = true;

fail_return: // hmm...
	result << uint8(command) << bResult;
	Send(&result);
}