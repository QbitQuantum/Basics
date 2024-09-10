L2ItemTemplate::L2ItemTemplate( L2ItemType itemType, L2ItemSubType subType, StatsSet& set )
{
	m_type = itemType;
	m_subType = subType;
	int temp_i;
	//   id
	set.getInt( "item_id", &m_itemId );
	//   name
	std::wstring wstr_name;
	set.getWString( "name", wstr_name );
	m_name = NULL;
	if( wstr_name.length() > 0 )
		m_name = _wcsdup( wstr_name.c_str() );
	set.getInt( "type1", &m_type1, 0 );
	set.getInt( "type2", &m_type2, 0 );
	set.getInt( "weight", &m_weight, 0 );
	set.getBool( "crystallizable", &m_crystallizable, false );
	set.getBool( "stackable", &m_stackable, false );
	set.getInt( "material", (int *)&m_materialType );
	set.getInt( "crystal_type", (int *)&m_crystalType, (int)CRYSTAL_NONE ); // default to none-grade
	set.getInt( "duration", &m_duration ); // default 0 or -1?
	set.getInt( "time", &m_time ); // default seems to be -1
	set.getInt( "bodypart", &temp_i );
	m_bodyPart = (L2ItemSlot)temp_i;
	set.getInt( "price", &m_referencePrice );
	set.getInt( "crystal_count", &m_crystalCount, 0 );
	set.getBool( "sellable", &m_sellable, true );
	set.getBool( "dropable", &m_dropable, true );
	set.getBool( "destroyable", &m_destroyable, true );
	set.getBool( "tradeable", &m_tradeable, true );
	// checks by item id
	m_common = (m_itemId >= 12006 && m_itemId <= 12361) || (m_itemId >= 11605 && m_itemId <= 12308);
	m_heroItem = (m_itemId >= 6611 && m_itemId <= 6621) || (m_itemId >= 9388 && m_itemId <= 9390) || m_itemId == 6842;
	m_pvpItem = (m_itemId >= 10667 && m_itemId <= 10792) || (m_itemId >= 10793 && m_itemId <= 10835) || (m_itemId >= 12852 && m_itemId <= 12977) || (m_itemId >= 14363 && m_itemId <= 14519) || (m_itemId >= 14520 && m_itemId <= 14525) || m_itemId == 14528 || m_itemId == 14529 || m_itemId == 14558;
}