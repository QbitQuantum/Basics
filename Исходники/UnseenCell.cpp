//----------------------------------------------------------------------------
//
// Name       : UnseenCell::UnseenCell
//
// Description: Constructor
//
// Parameters : point			: The point (RC coordinate)
//
// Globals    : g_theWorld		: World information
//
// Returns    : -
//
// Remark(s)  : The constructor to use normally.
//
//----------------------------------------------------------------------------
UnseenCell::UnseenCell(const MapPoint & point)
:
	m_env                           (0),
	m_terrain_type                  (TERRAIN_UNKNOWN),
	m_move_cost                     (MOVECOST_UNKNOWN),
	m_flags                         (0x0000),
	m_bioInfectedOwner              (0x00), /// @todo Check PLAYER_UNASSIGNED?
	m_nanoInfectedOwner             (0x00),
	m_convertedOwner                (0x00),
	m_franchiseOwner                (0x00),
	m_injoinedOwner                 (0x00),
	m_happinessAttackOwner          (0x00),
	m_citySize                      (0),
	m_cityOwner                     (0),
	m_citySpriteIndex               (-1),
	m_cell_owner                    (PLAYER_UNASSIGNED),
	m_slaveBits                     (0x0000),
#ifdef BATTLE_FLAGS
	m_battleFlags                   (0),
#endif
	m_tileInfo                      (NULL),
	m_point                         (point),
	m_installations                 (new PointerList<UnseenInstallationInfo>),
	m_improvements                  (new PointerList<UnseenImprovementInfo>),
	m_cityName                      (NULL),
	m_actor                         (NULL),
	m_poolIndex                     (-1),
	m_visibleCityOwner              (0)
{
	if (g_theWorld->GetTileInfo(point))
	{
		m_tileInfo = new TileInfo(g_theWorld->GetTileInfo(point));
	}

	Cell * cell = g_theWorld->GetCell(point);
	if (cell)
	{
		m_env = cell->GetEnv();
		m_move_cost = sint16(cell->GetMoveCost());
		m_terrain_type = (sint8)TERRAIN_TYPES(cell->GetTerrain());
#ifdef BATTLE_FLAGS
		m_battleFlags = cell->GetBattleFlags();
#endif

		sint32 i;

		// Same as well information about existing
		// tile improvments, except roadlike ones,
		// so that this information is available
		// later as well.
		// And in order not to break anythink use the existing
		// list for unfinished tile improvements.
		for(i = 0; i < cell->GetNumDBImprovements(); i++) {
			sint32 imp = cell->GetDBImprovement(i);
			m_improvements->AddTail(new UnseenImprovementInfo(imp, 100));
		}
		for(i = 0; i < cell->GetNumImprovements(); i++) {
			TerrainImprovement imp = cell->AccessImprovement(i);
			if (imp.IsValid())
			{
				m_improvements->AddTail(new UnseenImprovementInfo(imp.GetType(),
															      imp.PercentComplete()));
			}
		}

		DynamicArray<Installation> instArray;
		g_theInstallationTree->GetAt(point, instArray);
		for(i = 0; i < instArray.Num(); i++) {
			m_installations->AddTail(new UnseenInstallationInfo(instArray[i].GetType(),
														       instArray[i].GetVisibility()));
		}

		m_cell_owner = (sint8) cell->GetOwner();

		// Store the city that controlls this tile.
		m_visibleCityOwner = cell->GetCityOwner().m_id;

		Unit    city = cell->GetCity();

		if (city.IsValid())
		{
			m_citySize = (sint16)city.PopCount();
			m_citySpriteIndex = (sint16)city.CD()->GetDesiredSpriteIndex();
			const MBCHAR *name = city.GetName();
			m_cityName = new MBCHAR[strlen(name) + 1];
			strcpy(m_cityName, name);

			m_cityOwner = static_cast<sint16>(city.GetCityData()->GetOwner());

			CityData *cityData = city.GetData()->GetCityData();

			UnitActor *actor = city.GetActor();

			if (actor) {

				SpriteState *newSS = new SpriteState(city.GetSpriteState()->GetIndex());

				UnitActor *newActor = new UnitActor(newSS,
												    city,
												    city.GetType(),
												    point,
												    city.GetOwner(),
												    TRUE,
												    city.GetVisionRange(),
												    city.CD()->GetDesiredSpriteIndex());

				newActor->SetUnitVisibility((1 << g_selected_item->GetVisiblePlayer())
										    | actor->GetUnitVisibility());
				newActor->SetPos(point);

				newActor->SetIsFortified(actor->IsFortified());
				newActor->SetIsFortifying(actor->IsFortifying());
				newActor->SetHasCityWalls(actor->HasCityWalls());
				newActor->SetHasForceField(actor->HasForceField());

				newActor->SetSize(m_citySize);

				newActor->ChangeImage(newSS, city.GetType(), city);

				newActor->AddIdle();
				newActor->GetNextAction();

				m_actor = newActor;
			} // actor

			SetIsBioInfected(cityData->IsBioInfected());
			SetIsNanoInfected(cityData->IsNanoInfected());
			SetIsConverted(cityData->IsConverted());
			SetIsFranchised(cityData->IsFranchised());
			SetIsInjoined(cityData->IsInjoined());
			SetWasHappinessAttacked(cityData->WasHappinessAttacked());
			SetIsRioting(cityData->GetIsRioting());
			SetHasAirport(cityData->HasAirport());
			SetHasSleepingUnits(cityData->HasSleepingUnits());
			SetIsWatchful(cityData->IsWatchful());
			SetIsCapitol(cityData->IsCapitol()); //emod
			SetIsReligionIcon(cityData->HasReligionIcon()); //emod
			m_bioInfectedOwner = (sint8)cityData->GetBioInfectedBy();
			m_nanoInfectedOwner = (sint8)cityData->GetNanoInfectedBy();
			m_convertedOwner = (sint8)cityData->IsConvertedTo();
			m_franchiseOwner = (sint8)cityData->GetFranchiseOwner();
			m_injoinedOwner = (sint8)cityData->InjoinedBy();
			m_happinessAttackOwner = (sint8)cityData->GetHappinessAttackedBy();
			m_slaveBits = cityData->GetSlaveBits();
			SetIsSpecialIcon(cityData->HasSpecialIcon()); //emod

		    sint32 pollution = cityData->GetPollution();
			SetIsPollutionRisk(pollution > g_theConstDB->Get(0)->GetLocalPollutionLevel());

		} // city.IsValid
	} // cell

	SetHasHut(NULL != g_theWorld->GetGoodyHut(point));
}