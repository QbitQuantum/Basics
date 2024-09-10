void BattleGesture::UpdateTrackingMarker()
{
	Unit* unit = _trackingMarker->GetUnit();

	glm::vec2 screenTouchPosition = _trackingTouch->GetPosition();
	glm::vec2 screenMarkerPosition = screenTouchPosition + glm::vec2(0, 1) * (_offsetToMarker * GetFlipSign());
	glm::vec2 touchPosition = _battleView->GetTerrainPosition3(screenTouchPosition).xy();
	glm::vec2 markerPosition = _battleView->GetTerrainPosition3(screenMarkerPosition).xy();

	Unit* enemyUnit = FindEnemyUnit(touchPosition, markerPosition);
	glm::vec2 unitCenter = unit->state.center;

	bool isModifierMode = _tappedModiferArea || _modifierTouch != nullptr || _trackingTouch->GetCurrentButtons().right;
	_trackingMarker->SetRenderOrientation(isModifierMode);

	if (!isModifierMode)
	{
		std::vector<glm::vec2>& path = _trackingMarker->_path;

		glm::vec2 currentDestination = path.size() != 0 ? *(path.end() - 1) : unit->state.center;

		bounds2f contentBounds = _battleView->GetContentBounds();
		glm::vec2 contentCenter = contentBounds.center();
		float contentRadius = contentBounds.width() / 2;

		glm::vec2 differenceToCenter = contentCenter - markerPosition;
		float distanceToCenter = glm::length(differenceToCenter);
		if (distanceToCenter > contentRadius)
		{
			markerPosition += differenceToCenter * (distanceToCenter - contentRadius) / distanceToCenter;
		}

		float movementLimit = -1;
		float delta = 1.0f / fmaxf(1, glm::length(currentDestination - markerPosition));
		for (float k = delta; k < 1; k += delta)
		{
			GroundMap* groundMap = _battleView->GetSimulator()->GetGroundMap();
			if (groundMap != nullptr && groundMap->IsImpassable(glm::mix(currentDestination, markerPosition, k)))
			{
				movementLimit = k;
				break;
			}
		}

		if (movementLimit >= 0)
		{
			glm::vec2 diff = markerPosition - currentDestination;
			markerPosition = currentDestination + diff * movementLimit;
			markerPosition -= glm::normalize(diff) * 10.0f;

			enemyUnit = nullptr;
		}

		if (enemyUnit && !_trackingMarker->GetMeleeTarget())
			SoundPlayer::singleton->Play(SoundBufferCommandMod);

		_trackingMarker->SetMeleeTarget(enemyUnit);
		_trackingMarker->SetDestination(&markerPosition);

		if (enemyUnit != nullptr)
			MovementRules::UpdateMovementPath(_trackingMarker->_path, unitCenter, enemyUnit->state.center);
		else
			MovementRules::UpdateMovementPath(_trackingMarker->_path, unitCenter, markerPosition);

		if (enemyUnit != nullptr)
		{
			glm::vec2 destination = enemyUnit->state.center;
			glm::vec2 orientation = destination + glm::normalize(destination - unitCenter) * 18.0f;
			_trackingMarker->SetOrientation(&orientation);
		}
		else if (MovementRules::Length(_trackingMarker->_path) > KEEP_ORIENTATION_TRESHHOLD)
		{
			glm::vec2 dir = glm::normalize(markerPosition - unitCenter);
			if (path.size() >= 2)
				dir = glm::normalize(*(path.end() - 1) - *(path.end() - 2));
			glm::vec2 orientation = markerPosition + dir * 18.0f;
			_trackingMarker->SetOrientation(&orientation);
		}
		else
		{
			glm::vec2 orientation = markerPosition + 18.0f * vector2_from_angle(unit->state.bearing);
			_trackingMarker->SetOrientation(&orientation);
		}
	}
	else
	{
		MovementRules::UpdateMovementPathStart(_trackingMarker->_path, unitCenter);

		bool holdFire = false;
		if (_trackingMarker->GetUnit()->state.unitMode == UnitMode_Standing && _trackingMarker->GetUnit()->stats.maximumRange > 0)
		{
			bounds2f unitCurrentBounds = GetUnitCurrentBounds(_trackingMarker->GetUnit());
			holdFire = glm::distance(screenMarkerPosition, unitCurrentBounds.center()) <= unitCurrentBounds.x().radius();
		}

		if (holdFire)
		{
			_trackingMarker->SetMissileTarget(_trackingMarker->GetUnit());
			_trackingMarker->SetOrientation(nullptr);
		}
		else
		{
			//if (!_tappedUnitCenter)
			//	enemyUnit = nullptr;
			if (!_allowTargetEnemyUnit)
				enemyUnit = nullptr;

			if (enemyUnit != nullptr && _trackingMarker->GetMissileTarget() == nullptr)
				SoundPlayer::singleton->Play(SoundBufferCommandMod);

			_trackingMarker->SetMissileTarget(enemyUnit);
			_trackingMarker->SetOrientation(&markerPosition);
		}
	}
}