void MapScene::DrawMap()
{
	CDynArray<Chit*> query;

	const ChitContext* context = lumosChitBag->Context();
	const Web& web = lumosChitBag->GetSim()->CalcWeb();

	Rectangle2I subBounds = MapBounds2();
	float map2X = float(subBounds.min.x) / float(NUM_SECTORS);
	float map2Y = float(subBounds.min.y) / float(NUM_SECTORS);
	RenderAtom subAtom = mapImage.GetRenderAtom();
	subAtom.tx0 = map2X;
	subAtom.ty1 = map2Y;
	subAtom.tx1 = map2X + float(MAP2_SIZE) / float(NUM_SECTORS);
	subAtom.ty0 = map2Y + float(MAP2_SIZE) / float(NUM_SECTORS);
	mapImage2.SetAtom(subAtom);

	for (Rectangle2IIterator it(subBounds); !it.Done(); it.Next()) {
		Vector2I sector = it.Pos();
		const SectorData& sd = worldMap->GetSectorData( sector );

		int i = (sector.x - subBounds.min.x);
		int j = (sector.y - subBounds.min.y);
		int index = j * MAP2_SIZE + i;

		CoreScript* coreScript = CoreScript::GetCore(sector);

		CStr<64> str = "";
		const char* owner = "";
		if (coreScript) {
			if ( coreScript->InUse() ) {
				owner = Team::Instance()->TeamName( coreScript->ParentChit()->Team() ).safe_str();
			}
		}
		str.Format( "%s\n%s", sd.name.safe_str(), owner );

		Rectangle2F r = GridBounds2(i, j, true);
		gridWidget[index].SetPos(r.min.x, r.min.y);
		gridWidget[index].SetSize(r.Width(), r.Height());
		gridWidget[index].Set(context, coreScript, lumosChitBag->GetHomeCore(), &web);
	}

	Vector2I homeSector = lumosChitBag->GetHomeSector();
	if ( !data->destSector.IsZero() && data->destSector != homeSector ) {
		const SectorData& sd = worldMap->GetSectorData( data->destSector );
		CStr<64> str;
		str.Format( "Grid Travel\n%s", sd.name.c_str() );
		gridTravel.SetText(  str.c_str() );
		gridTravel.SetEnabled( true );
	}
	else {
		gridTravel.SetText( "Grid Travel" );
		gridTravel.SetEnabled( false );
	}

	// --- MAIN ---
	Rectangle2I mapBounds = data->worldMap->Bounds();
	Rectangle2I map2Bounds;
	map2Bounds.Set(subBounds.min.x*SECTOR_SIZE, subBounds.min.y*SECTOR_SIZE, 
				   subBounds.max.x*SECTOR_SIZE + SECTOR_SIZE-1, subBounds.max.y*SECTOR_SIZE + SECTOR_SIZE-1);

	Vector2F playerPos = { 0, 0 };
	Chit* player = data->player;
	if ( player ) {
		playerPos = ToWorld2F(player->Position());
	}

	const float dx = mapImage.Width() / float(NUM_SECTORS);
	const float dy = mapImage.Height() / float(NUM_SECTORS);
	for (int j = 0; j < NUM_SECTORS; ++j) {
		for (int i = 0; i < NUM_SECTORS; ++i) {
			diplomacy[j*NUM_SECTORS + i].SetSize(dx, dy);
			diplomacy[j*NUM_SECTORS + i].SetPos(mapImage.X() + dx * float(i), mapImage.Y() + dy * float(j));
		}
	}

	bool inBounds = true;
	Vector2F v;

	for (int i = 0; i < 2; ++i) {
		const Rectangle2I& b = (i == 0) ? mapBounds : map2Bounds;

		v = ToUI(i, playerPos, b, &inBounds);
		playerMark[i].SetCenterPos(v.x, v.y);
		playerMark[i].SetVisible(inBounds);

		Vector2F pos = { float(homeSector.x * SECTOR_SIZE), float(homeSector.y * SECTOR_SIZE) };
		v = ToUI(i,pos, b, &inBounds);
		homeMark[i].SetPos(v.x, v.y);
		homeMark[i].SetVisible(inBounds && !homeSector.IsZero());

		pos.Set(float(data->destSector.x * SECTOR_SIZE), float(data->destSector.y * SECTOR_SIZE));
		v = ToUI(i,pos, b, &inBounds);
//		if (i == 0) {
//			travelMark.SetPos(v.x, v.y);
//			travelMark.SetVisible(inBounds && !data->destSector.IsZero());
//		}
		for (int k = 0; k < MAX_SQUADS; ++k) {
			v = ToUI(i, ToWorld2F(data->squadDest[k]), b, &inBounds);
			squadMark[i][k].SetCenterPos(v.x, v.y);
			squadMark[i][k].SetVisible(!data->squadDest[k].IsZero() && inBounds);
		}
	}
	{
		Vector2F world = { (float)map2Bounds.min.x, (float)map2Bounds.min.y };
		Vector2F pos = ToUI(0, world, mapBounds, 0);
		selectionMark.SetPos(pos.x, pos.y);
	}

	float scale = float(mapImage.Width()) / float(NUM_SECTORS);
	{
		webCanvas.Clear();

		for (int i = 1; i < web.NumNodes(); i++) {
			const MinSpanTree::Node& node = web.NodeAt(i);
			Vector2I s0 = node.parentPos;
			Vector2I s1 = node.pos;
			Vector2F p0 = { (float(s0.x) + 0.5f) * scale, (float(s0.y) + 0.5f) * scale };
			Vector2F p1 = { (float(s1.x) + 0.5f) * scale, (float(s1.y) + 0.5f) * scale };
			webCanvas.DrawLine(p0.x, p0.y, p1.x, p1.y, 1.0f + node.strength * 2.0f);
		}
	}

	CoreScript* homeCore = context->chitBag->GetHomeCore();
	CChitArray citizens;
	if (homeCore) {
		homeCore->Citizens(&citizens);
	}
	for (int i = 0; i < MAX_CITIZENS; ++i) {
		if (i < citizens.Size()) {
			Vector2F cPos = ToWorld2F(citizens[i]->Position());
			Vector2F pos = ToUI(0, cPos, mapBounds, 0);
			unitMarker[i].SetSize(8, 8);
			unitMarker[i].SetCenterPos(pos.x, pos.y);
			unitMarker[i].SetVisible(true);
		}
		else {
			unitMarker[i].SetVisible(false);
		}
	}

	for (int j = 0; j < NUM_SECTORS; ++j) {
		for (int i = 0; i < NUM_SECTORS; ++i) {
			diplomacy[i].SetAtom(RenderAtom());

			Vector2I sector = { i, j };
			CoreScript* core = CoreScript::GetCore(sector);
			RenderAtom atom;

			if (core && homeCore && homeCore->InUse() && core->InUse()) {
				ERelate relate = Team::Instance()->GetRelationship(core->ParentChit(), homeCore->ParentChit());
				if (relate == ERelate::FRIEND) atom = LumosGame::CalcUIIconAtom("friend");
				else if (relate == ERelate::NEUTRAL) atom = LumosGame::CalcUIIconAtom("neutral");
				else if (relate == ERelate::ENEMY) atom = LumosGame::CalcUIIconAtom("enemy");
				
				diplomacy[j*NUM_SECTORS + i].SetSize(scale*0.8f, scale*0.8f);
			}

			if (core && core->InUse() && Team::IsDeity(core->ParentChit()->Team())) {
				atom = LumosGame::CalcDeityAtom(core->ParentChit()->Team());
				diplomacy[j*NUM_SECTORS + i].SetSize(scale, scale);
			}

			diplomacy[j*NUM_SECTORS + i].SetAtom(atom);
			diplomacy[j*NUM_SECTORS + i].SetCenterPos(mapImage.X() + scale * (float(i) + 0.5f), mapImage.Y() + scale * (float(j) + 0.5f));
		}
	}
}