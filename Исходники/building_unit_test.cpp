//----------------------------------------------------------------------------
bool CBuildingTest::changeRoom(uint charIndex)
{
	nlassert( charIndex < TestCharacters.size() );
	nlassert( TestCharacters[charIndex].InBuilding );

	CEntityId id = TestCharacters[charIndex].EId;

	CCharacter * c = PlayerManager.getChar( id );
	nlassert( c );

	sint32 cellId = TestCharacters[charIndex].CellId;
	const IRoomInstance * room = CBuildingManager::getInstance()->getRoomInstanceFromCell( cellId );
	if ( !room )
	{
		nlwarning("*** BuildingUnitTest *** cannot get room instance for character %u at cell %d.", charIndex, cellId);
		return false;
	}

	IBuildingPhysical * buildingInst = room->getBuilding();
	nlassert( buildingInst );

	const uint16 roomIndex = room->getRoomIndex();

	vector<IBuildingPhysical::CRoomPhysical> & rooms = buildingInst->_Rooms;
	nlassert( !rooms.empty() );

	if ( rooms.size() == 1 )
		return true;

	// find another room
	uint16 newRoomIndex;
	const uint maxLoops = 1000;
	uint nbLoops = 0;
	while (1)
	{
		nlassert(++nbLoops <= maxLoops);

		newRoomIndex = (uint16) RandomGenerator.rand( (uint16)rooms.size()-1 );
		if (newRoomIndex >= rooms.size())
			newRoomIndex = 0;

		if (newRoomIndex != roomIndex)
			break;
	}

	nlassert( !rooms[newRoomIndex].Cells.empty() );
	const sint32 newCellId = rooms[newRoomIndex].Cells[0];
	const IRoomInstance * newRoom = CBuildingManager::getInstance()->getRoomInstanceFromCell( newCellId );
	if ( !newRoom )
	{
		nlwarning("*** BuildingUnitTest *** cannot get room instance for character %u at cell %d.", charIndex, newCellId);
		return false;
	}

	IBuildingPhysical * newBuildingInst = newRoom->getBuilding();
	nlassert( newBuildingInst );
	nlassert( newBuildingInst == buildingInst );

	// cannot change room if we are in a guild/player building
	if ( !dynamic_cast<const CRoomInstanceCommon *>( newRoom ) )
		return true;

	if ( !newBuildingInst->addUser( c, newRoomIndex, 0, cellId ) )
	{
		nlwarning("*** BuildingUnitTest *** character %u cannot go from room %hu to room %hu in building %s.",
			charIndex, roomIndex, newRoomIndex, TestCharacters[charIndex].BuildingName.c_str()
			);
		CBuildingManager::getInstance()->removePlayerFromRoom( c );
		return false;
	}

	if (Verbose)
	{
		nlinfo("*** BuildingUnitTest *** character %u goes from room %hu (cell = %d) to room %hu (cell = %d) in building %s.",
			charIndex, roomIndex, TestCharacters[charIndex].CellId, newRoomIndex, cellId, TestCharacters[charIndex].BuildingName.c_str()
			);
	}

	// fake teleport
	CBuildingManager::getInstance()->removePlayerFromRoom( c );
	CMirrorPropValue<TYPE_CELL> mirrorCell( TheDataset, c->getEntityRowId(), DSPropertyCELL );
	mirrorCell = cellId;

	// update character data
	TestCharacters[charIndex].CellId		= cellId;
	TestCharacters[charIndex].RoomIndex		= newRoomIndex;

	return true;
}