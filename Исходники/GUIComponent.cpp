void GUIComponent::Render(const CU::Vector2<int>& aWindowSize, const CU::Vector2<float>& aMousePos, bool aIsActiveState)
{
	aMousePos;
	myIsActiveState = aIsActiveState;

	my3DClosestEnemyLength = 10000.f;
	myClosestEnemyLength = 100000.f;
	myClosestEnemy = nullptr;

	Prism::Engine::GetInstance()->DisableZBuffer();
	float halfHeight = aWindowSize.y * 0.5f;
	float halfWidth = aWindowSize.x * 0.5f;
	CU::Vector2<float> steeringPos(halfWidth + mySteeringTargetPosition.x
		, -halfHeight - mySteeringTargetPosition.y);

	if (myConversation.size() > 1)
	{
		myBackgroundConversation->Render({ 15.f, -halfHeight * 1.2f + 20.f + 128.f - 150.f });
	}

	myBackgroundMission->Render({ 15.f, -10.f });

	CU::Vector2<float> crosshairPosition(CU::Math::Lerp<CU::Vector2<float>>({ halfWidth, -halfHeight }
	, { steeringPos.x, steeringPos.y }, 0.3f));

	myReticle->Render({ halfWidth, -halfHeight });
	mySteeringTarget->Render({ steeringPos.x, steeringPos.y });
	myCrosshair->Render(crosshairPosition);

	myFirstSpawn = myWaypointSpawn;
	myFirstSpawnTimer = myWaypointSpawnTimer;

	if (myIsActiveState == true)
	{
		Prism::Engine::GetInstance()->PrintText(myConversation, { 35.f, -halfHeight * 1.2f + 20.f + 128.f - 200.f }, Prism::eTextType::RELEASE_TEXT);
		CalculateAndRender(myWaypointPosition, myModel2DToRender, myWaypointArrow, myWaypointMarker
			, aWindowSize, myWaypointActive);

		for (int i = 0; i < myEnemies.Size(); ++i)
		{
			myFirstSpawn = myEnemies[i]->GetGUIStartReneringMarker();
			myFirstSpawnTimer = myEnemies[i]->GetGUIStartRenderingMarkerTimer();
			if (myFirstSpawn == false && myFirstSpawnTimer != 0) myEnemies[i]->ActivateGUIStartRenderingMarker();
			float lengthToEnemy = CU::Length(myEnemies[i]->myOrientation.GetPos() - myCamera->GetOrientation().GetPos());
			if (lengthToEnemy < my3DClosestEnemyLength)
			{
				my3DClosestEnemyLength = lengthToEnemy;
			}

			if (myEnemies[i]->GetType() == eEntityType::STRUCTURE)
			{
				CalculateAndRender(myEnemies[i]->myOrientation.GetPos(), myModel2DToRender, myStructureArrow
					, myStructureMarker, aWindowSize, true, 1.f, false, "", myEnemies[i]);
			}
			else
			{
				if (lengthToEnemy < myMaxDistanceToEnemies)
				{
					CalculateAndRender(myEnemies[i]->myOrientation.GetPos(), myModel2DToRender, myEnemyArrow, myEnemyMarker, aWindowSize, true);
				}
			}
			CU::Vector2<float> enemyScreenPos = myClosestScreenPos;
			float lengthFromMouseToEnemy = CU::Length(enemyScreenPos - CU::Vector2<float>(steeringPos.x, steeringPos.y));
			if (lengthFromMouseToEnemy < myClosestEnemyLength)
			{
				myClosestEnemy = myEnemies[i];
				myClosestEnemyLength = lengthFromMouseToEnemy;
			}
		}

		if (myEnemies.Size() > 0 && my3DClosestEnemyLength < 1000)
		{
			if (myBattlePlayed == false)
			{
				Prism::Audio::AudioInterface::GetInstance()->PostEvent("Pause_BackgroundMusic", 0);
				Prism::Audio::AudioInterface::GetInstance()->PostEvent("Resume_BattleMusic", 0);

			}
			myBackgroundMusicPlayed = false;
			myBattlePlayed = true;
		}
		else
		{
			if (myBackgroundMusicPlayed == false)
			{
				Prism::Audio::AudioInterface::GetInstance()->PostEvent("Resume_BackgroundMusic", 0);
				Prism::Audio::AudioInterface::GetInstance()->PostEvent("Pause_BattleMusic", 0);
			}
			myBattlePlayed = false;
			myBackgroundMusicPlayed = true;
		}

		for (int i = 0; i < myPowerUps.Size(); ++i)
		{
			myFirstSpawn = myPowerUps[i]->GetGUIStartReneringMarker();
			myFirstSpawnTimer = myPowerUps[i]->GetGUIStartRenderingMarkerTimer();
			if (myFirstSpawn == false && myFirstSpawnTimer != 0) myPowerUps[i]->ActivateGUIStartRenderingMarker();
			CalculateAndRender(myPowerUps[i]->myOrientation.GetPos(), myModel2DToRender, myPowerUpArrow, myPowerUpMarker
				, aWindowSize, true, true, 1.f, myPowerUps[i]->GetComponent<PowerUpComponent>()->GetInGameName());
		}

		if (myEnemiesTarget != nullptr)
		{
			CalculateAndRender(myEnemiesTarget->myOrientation.GetPos(), myModel2DToRender, myDefendArrow, myDefendMarker, aWindowSize, true);
		}

		float percentageToReady = 1.f;

		if (myHasRocketLauncher == true)
		{
			Prism::Engine::GetInstance()->PrintText("RL", { halfWidth + 550.f, -halfHeight + 15.f }, Prism::eTextType::RELEASE_TEXT);

			percentageToReady = *myRocketCurrentTime / *myRocketMaxTime;
			if (percentageToReady >= 1.f)
			{
				if (myPlayedMissilesReady == false)
				{
					myEntity.SendNote<SoundNote>(SoundNote(eSoundNoteType::PLAY, "Play_MissilesReady"));
					myPlayedMissilesReady = true;
				}
				Prism::Engine::GetInstance()->PrintText("RDY", { halfWidth + 550.f, -halfHeight - 20.f }, Prism::eTextType::RELEASE_TEXT);
			}
			else
			{
				myPlayedMissilesReady = false;
			}
		}



		if (myHasHomingWeapon == true)
		{
			if (myClosestEnemy != nullptr)
			{
				myHomingTarget->Rotate(myDeltaTime);
				CalculateAndRender(myClosestEnemy->myOrientation.GetPos(), nullptr, nullptr, nullptr, aWindowSize, true, 1.f);
			}
			myEntity.GetComponent<ShootingComponent>()->SetHomingTarget(myClosestEnemy);
		}
		if (myHasRocketLauncher == true && percentageToReady >= 1.f)
		{
			if (myClosestEnemy != nullptr)
			{
				myHomingTarget->Rotate(myDeltaTime);
				if (myClosestEnemy->GetName() != "E_enemy_turret_noShoot")
				{
					CalculateAndRender(myClosestEnemy->myOrientation.GetPos(), myModel2DToRender, myHomingTarget, myHomingTarget, aWindowSize, true, percentageToReady);
				}
			}

			myEntity.GetComponent<ShootingComponent>()->SetHomingTarget(myClosestEnemy);
		}
	}

	myEnemies.RemoveAll();
	myPowerUps.RemoveAll();

	myGUIBars[0]->Render(*myCamera);

	if (myCurrentShield <= 101.f)
	{
		myGUIBars[1]->Render(*myCamera);
	}
	else
	{
		myGUIBars[2]->Render(*myCamera);
	}

	if (myHitMarkerTimer >= 0.f)
	{
		myCurrentHitmarker->Render(crosshairPosition);
	}

	if (myDamageIndicatorTimer >= 0.f)
	{
		float alpha = fminf(1.f, myDamageIndicatorTimer);
		if (myCurrentShield <= 0)
		{
			myDamageIndicatorHealth->Render({ halfWidth, -halfHeight }, { 1.f, 1.f }, { 1.f, 1.f, 1.f, alpha });
		}
		else
		{
			//myDamageIndicatorShield->Render({ halfWidth, -halfHeight }, { 1.f, 1.f }, { 1.f, 1.f, 1.f, alpha });
		}
	}

	if (myIsActiveState == true)
	{
		if (myClosestEnemy != nullptr)
		{
			CalculateAndRender(myClosestEnemy->myOrientation.GetPos(), nullptr, nullptr, nullptr, aWindowSize
				, true, 1.f, false, "", myClosestEnemy);

			if (myShouldRenderHP == true && myClosestEnemy->GetName() != "E_enemy_turret_noShoot")
			{
				float alpha = CU::Length(steeringPos - myClosestScreenPos);
				alpha = 1.f - (alpha / CIRCLERADIUS);
				Prism::Engine::GetInstance()->PrintText("Hp: " + std::to_string(myClosestEnemy->GetComponent<HealthComponent>()->GetHealth())
					, { myClosestScreenPos.x - 30.f, myClosestScreenPos.y + 40.f }, Prism::eTextType::RELEASE_TEXT
					, 0.5f, { 1.f, 1.f, 1.f, alpha });
			}
		}

		myPowerUpSlots[ePowerUpType::EMP]->Render(aWindowSize, myDeltaTime);
		myPowerUpSlots[ePowerUpType::FIRERATEBOOST]->Render(aWindowSize, myDeltaTime);
		myPowerUpSlots[ePowerUpType::HOMING]->Render(aWindowSize, myDeltaTime);
		myPowerUpSlots[ePowerUpType::INVULNERABLITY]->Render(aWindowSize, myDeltaTime);

		if (myShowMessage == true)
		{
			Prism::Engine::GetInstance()->PrintText(myMessage, { halfWidth - 150.f, -halfHeight + 200.f }, Prism::eTextType::RELEASE_TEXT
				, 1.f, { 1.f, 1.f, 1.f, myMessageAlpha });
		}

		if (myShowTutorialMessage == true)
		{
			Prism::Engine::GetInstance()->PrintText(myTutorialMessage, { halfWidth - 270.f, -halfHeight + 220.f }, Prism::eTextType::RELEASE_TEXT
				, 1.f, { 1.f, 1.f, 1.f, myMessageAlpha });
		}

		if (myHasMachinegun == true)
		{
			Prism::Engine::GetInstance()->PrintText("MG", { halfWidth + 420.f, -halfHeight + 15.f }, Prism::eTextType::RELEASE_TEXT);

			if (*myCurrentWeapon == 0)
			{
				Prism::Engine::GetInstance()->PrintText("RDY", { halfWidth + 420.f, -halfHeight - 20.f }, Prism::eTextType::RELEASE_TEXT);
			}
		}

		if (myHasShotgun == true)
		{
			Prism::Engine::GetInstance()->PrintText("SG", { halfWidth + 480.f, -halfHeight + 15.f }, Prism::eTextType::RELEASE_TEXT);

			if (*myCurrentWeapon == 1)
			{
				Prism::Engine::GetInstance()->PrintText("RDY", { halfWidth + 480.f, -halfHeight - 20.f }, Prism::eTextType::RELEASE_TEXT);
			}
		}

		float speed = myEntity.GetComponent<PhysicsComponent>()->GetSpeed();
		speed += 0.5f;
		int displaySpeed = int(speed);
		if (speed > 99.5f && speed < 102.f)
		{
			displaySpeed = 100;
		}
		if (speed > 250.f)
		{
			displaySpeed = 250;
		}

		Prism::Engine::GetInstance()->PrintText(displaySpeed
			, { halfWidth - 360.f, -halfHeight - 270.f }, Prism::eTextType::RELEASE_TEXT);

		if (myHasEMP == true)
		{
			Prism::Engine::GetInstance()->PrintText("EMP ready. Press [Space] to release."
				, { halfWidth - 240.f, -halfHeight - 270.f }, Prism::eTextType::RELEASE_TEXT, 1.f, { 1.f, 1.f, 1.f, myEMPMessageAlpha });
		}
	}

	Prism::Engine::GetInstance()->EnableZBuffer();
}