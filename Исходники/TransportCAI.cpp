bool CTransportCAI::FindEmptyDropSpots(float3 startpos, float3 endpos, std::list<float3>& dropSpots) {
	//should only be used by air

	CTransportUnit* transport=(CTransportUnit*)owner;
	//dropSpots.clear();
	float gap = 25.5; //TODO - set tag for this?
	float3 dir = endpos - startpos;
	dir.Normalize();

	float3 nextPos = startpos;
	float3 pos;

	list<CTransportUnit::TransportedUnit>::iterator ti = transport->transported.begin();
	dropSpots.push_front(nextPos);

	//first spot
	if (ti!=transport->transported.end()) {
		//float3 p = nextPos; //test to make intended land spots visible
		//inMapDrawer->CreatePoint(p,ti->unit->unitDef->name);
		//p.z +=transport->transportCapacityUsed*5;
		nextPos += dir*(gap + ti->unit->radius);
		ti++;
	}

	//remaining spots
	if (dynamic_cast<CTAAirMoveType*>(owner->moveType)) {
		while (ti != transport->transported.end() && startpos.distance(nextPos) < startpos.distance(endpos)) {
			nextPos += dir*(ti->unit->radius);
			nextPos.y = ground->GetHeight(nextPos.x, nextPos.z);

			//check landing spot is ok for landing on
			if (!SpotIsClear(nextPos,ti->unit))
				continue;

			dropSpots.push_front(nextPos);
			//float3 p = nextPos; //test to make intended land spots visible
			//inMapDrawer->CreatePoint(p,ti->unit->unitDef->name);
			//p.z +=transport->transportCapacityUsed*5;
			nextPos += dir*(gap + ti->unit->radius);
			ti++;
		}
		return true;
	}
	return false;
}