//----------Die KI der Einheiten----------------------------------------------------------------
void UnitKI(LPOBJEKT lpObjekt)
{
	// Erst prüfen, ob Objekt zerstört wurde, falls ja->Funktion abbrechen
	if (CheckIfDestroyed(lpObjekt) == true)
		return;
	// Je nach Objekttyp KI aufrufen
	switch(lpObjekt->typ)
	{
	// Das Schiff des Spielers
	case UD_PLAYERSHIP:
		{
			// Aktuelle Position und Energie des PlayerShip in externe Variabeln speichern
			PlayerShipPosX = lpObjekt->x;
			PlayerShipPosY = lpObjekt->y;
			PlayerShipEnergy = lpObjekt->energie;

			// Das Schiff mit dem Vektor des vorigen Frames bewegen
			MoveDiagonal(lpObjekt);

			// Den Bewegungsvektor verkleinern (Schiff wird langsamer, wenn nicht beschleunigt)
			if (VectorLength(lpObjekt->v) > 0)
			{
				lpObjekt->v[0] = lpObjekt->v[0]*0.8;
				lpObjekt->v[1] = lpObjekt->v[1]*0.9;
			}

			// Schiff nach links bewegen
			if(GetAsyncKeyState(VK_LEFT))
			{
				lpObjekt->v[0] -= 1;
				if (GetTickCount() - lpObjekt->timer > 75 && lpObjekt->akt_bild > 0)
				{
					lpObjekt->akt_bild--;
					lpObjekt->timer = GetTickCount();
				}
			}
			// Schiff nach rechts bewegen
			if(GetAsyncKeyState(VK_RIGHT))
			{
				lpObjekt->v[0] += 1;
				if (GetTickCount() - lpObjekt->timer > 75 && lpObjekt->akt_bild < lpObjekt->bild->anz_anim)
				{
					lpObjekt->akt_bild++;
					lpObjekt->timer = GetTickCount();
				}
			}
			// Schiff nach oben bewegen
			if(GetAsyncKeyState(VK_UP))
			{
				lpObjekt->v[1] -= 0.5f;
			}
			// Schiff nach unten bewegen
			if(GetAsyncKeyState(VK_DOWN))
			{
				lpObjekt->v[1] += 0.5f;
			}

			// Prüfen, ob der Bewegungsvektor zu lang ist und ggf. auf maximale Länge kürzen
			if (VectorLength(lpObjekt->v) >= lpObjekt->s)
			{
				lpObjekt->v[0] = ((lpObjekt->v[0])/(VectorLength(lpObjekt->v)))*lpObjekt->s;
				lpObjekt->v[1] = ((lpObjekt->v[1])/(VectorLength(lpObjekt->v)))*lpObjekt->s;
			}
			
			// Prüfen, ob Schiff nicht mehr im Bildschirm-Bereich und korrigieren falls nötig
			// Linker Rand
			if (lpObjekt->x < 0)
				lpObjekt->x = 0;
			// Rechter Rand
			if ((lpObjekt->x + lpObjekt->bild->breite) > RESOLUTION_X)
				lpObjekt->x = (float)(RESOLUTION_X - lpObjekt->bild->breite);
			// Oberer Rand
			if ((lpObjekt->y) < (ScrollY))
				lpObjekt->y = ScrollY;
			// Unterer Rand
			if ((lpObjekt->y + lpObjekt->bild->hoehe) > (ScrollY + RESOLUTION_Y))
				lpObjekt->y = ((float)(ScrollY + RESOLUTION_Y)) - (lpObjekt->bild->hoehe);
			// Position etwas nach oben setzen (Raumschiff bewegt sich nach oben mit dem Scrolling)
			lpObjekt->y -= 1;
			
			// Langsames zurückneigen des Schiffes, wenn es sich nicht nach links/rechts bewegt
			if (abs(lpObjekt->v[0]) < 0.2) // Zurückneigen nur, falls fast keine Bewegung in X-Richtung
			{
				if ((GetTickCount() - ZurueckNeigenTimer) > 100)
				{
					if (lpObjekt->akt_bild < 3)
						lpObjekt->akt_bild++;
					if (lpObjekt->akt_bild > 3)
						lpObjekt->akt_bild--;
					ZurueckNeigenTimer = GetTickCount();
				}
			}

			// Rakete erstellen, falls CTRL gedrückt und genug Zeit seit letzer Rakete verstrichen
			iRocketTimer += fFrameTime;
			if (iRocketTimer > WeaponShotSpeed)
				iRocketTimer = WeaponShotSpeed;
			if (GetAsyncKeyState(VK_CONTROL) && iRocketTimer >= WeaponShotSpeed)
			{
				// Eine Rakete abschiessen kostet Punkte
				Score -= 20;
				if (Score < 0)
					Score = 0;
				// Rakete mit Sound erstellen
				CreateObjekt(lpObjekt->x + 24, lpObjekt->y - 20, 0, 0, ChosenWeaponType);
				iRocketTimer = 0;
				PlaySoundOnce(SoundArray[1], 0, DSBVOLUME_MAX);
			}

			return;
		} // Ende UD_PLAYERSHIP

	// Ein Meteorit
	case UD_STONE64:
		{
			lpObjekt->y += lpObjekt->s;
			lpObjekt->LifeTime -= dwFrameTime;
			return;
		} // Ende UD_STONE64

	// Das erste Monster (Ein Wurm)
	case UD_MONSTER1A:
		{
			if (lpObjekt->zustand == OZ_GO)
				MoveDiagonal(lpObjekt);
			return;
		} // Ende UD_MONSTER1A

	// Das zweiter Monster (Eine Schnecke)
	case UD_MONSTER1B:
		{
			if (lpObjekt->zustand == OZ_GO)
				MoveDiagonal(lpObjekt);
			// Mit einer kleinen Wahrscheinlichkeit einen Schuss erzeugen
			if((rand()%200)==1)
				CreateObjekt(lpObjekt->x + 32, lpObjekt->y + 65, PlayerShipPosX, PlayerShipPosY - 100, UD_SCHUSS);
			return;
		} // Ende UD_MONSTER1B

	// Der Schuss von Gegner Nr.2 (UD_MONSTER1B)
	case UD_SCHUSS:
		{
			if (lpObjekt->zustand == OZ_GO)
				MoveDiagonal(lpObjekt);
			return;
		} // Ende UD_EXTRA

	// 2000 Extra-Punkte
	case UD_EXTRA:
		{
			// Prüfen, ob das Spielerschiff dieses Objekt berührt hat und wenn ja-->
			// Extra-Punkte berechnen
			if (((PlayerShipPosX + 64) > lpObjekt->x) && (PlayerShipPosX < (lpObjekt->x + 32)) && ((PlayerShipPosY + 64) > lpObjekt->y) && (PlayerShipPosY < (lpObjekt->y + 32)))
			{
				Score += 2000;
				lpObjekt->zustand = OZ_DEAD;
			}
			return;
		} // Ende UD_EXTRA

	//------B L O C K S-------------------
	// Ein grosses Hindernis
	case UD_BLOCK1:
		{
			// Damit Objekt nie zerstört wird (+ um Variabel-Überläufe zu verhindern)
			lpObjekt->energie = 1;
			return;
		} //Ende UD_BLOCK1

	// Ein Stein im Hintergrund
	case UD_BACK64A:
		{
			// Damit Objekt nie zerstört wird (+ um Variabel-Überläufe zu verhindern)
			lpObjekt->energie = 1;
			return;
		} // Ende UD_BACK64A

	//------E F F E K T E-------------------------
	// Die verschiedenen Explosionen (Verschieden gross)
	case UD_EXP16:
	case UD_EXP32:
	case UD_EXP64:
		{
			lpObjekt->LifeTime -= dwFrameTime;
			return;
		} // Ende UD_EXP16/32/64

	//------W A F F E N-------------------
	// Die Standard-Rakete
	case UD_STDROCKET:
		{			
			lpObjekt->y -= lpObjekt->s;
			lpObjekt->LifeTime -= dwFrameTime;
			return;
		} // Ende UD_STDROCKET
	} // Ende switch(lpObjekt->typ)
} // Ende UnitKI()