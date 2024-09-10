void SW_ParaDrop::LoadFromINI(
	SWTypeExt::ExtData *pData, SuperWeaponTypeClass *pSW, CCINIClass *pINI)
{
	const char * section = pSW->ID;

	if(!pINI->GetSection(section)) {
		return;
	}

	INI_EX exINI(pINI);

	char base[0x40];

	auto CreateParaDropBase = [](char* pID, char* pBuffer) {
		// put a string like "Paradrop.Americans" into the buffer
		if(pBuffer) {
			AresCRT::strCopy(pBuffer, "ParaDrop", 9);
			if(pID && strlen(pID)) {
				AresCRT::strCopy(&pBuffer[8], ".", 2);
				AresCRT::strCopy(&pBuffer[9], pID, 0x18);
			}
		}
	};

	auto ParseParaDrop = [&](char* pID, int Plane) -> ParadropPlane* {
		ParadropPlane* pPlane = NULL;

		// create the plane part of this request. this will be
		// an empty string for the first plane for this is the default.
		char plane[0x10] = "";
		if(Plane) {
			AresCRT::strCopy(plane, ".Plane", 0x10);
			_itoa_s(Plane + 1, &plane[6], 10, 10);
		}
		
		// construct the full tag name base
		char base[0x40], key[0x40];
		_snprintf_s(base, 0x3F, "%s%s", pID, plane);

		// parse the plane contents
		_snprintf_s(key, 0x3F, "%s.Aircraft", base);
		if(pINI->ReadString(section, key, "", Ares::readBuffer, Ares::readLength)) {
			if(AircraftTypeClass* pTAircraft = AircraftTypeClass::Find(Ares::readBuffer)) {
				pPlane = new ParadropPlane();
				pPlane->pAircraft = pTAircraft;
			} else {
				Debug::INIParseFailed(section, key, Ares::readBuffer);
			}
		}

		// a list of UnitTypes and InfantryTypes
		_snprintf_s(key, 0x3F, "%s.Types", base);
		if(pINI->ReadString(section, key, "", Ares::readBuffer, Ares::readLength)) {
			// create new plane if there is none yet
			if(!pPlane) {
				pPlane = new ParadropPlane();
			}

			// parse the types
			pPlane->pTypes.Clear();

			char* context = nullptr;
			for(char* p = strtok_s(Ares::readBuffer, Ares::readDelims, &context); p && *p; p = strtok_s(nullptr, Ares::readDelims, &context)) {
				TechnoTypeClass* pTT = UnitTypeClass::Find(p);

				if(!pTT) {
					pTT = InfantryTypeClass::Find(p);
				}

				if(pTT) {
					pPlane->pTypes.AddItem(pTT);
				} else {
					Debug::INIParseFailed(section, key, p);
				}
			}
		}

		// don't parse nums if there are no types
		if(!pPlane || !pPlane->pTypes.Count) {
			return pPlane;
		}

		// the number how many times each item is created
		_snprintf_s(key, 0x3F, "%s.Num", base);
		if(pINI->ReadString(section, key, "", Ares::readBuffer, Ares::readLength)) {
			pPlane->pNum.Clear();

			char* context = nullptr;
			for(char* p = strtok_s(Ares::readBuffer, Ares::readDelims, &context); p && *p; p = strtok_s(nullptr, Ares::readDelims, &context)) {
				pPlane->pNum.AddItem(atoi(p));
			}
		}

		return pPlane;
	};

	auto GetParadropPlane = [&](char *pID, int defCount, DynamicVectorClass<ParadropPlane*>* ret) {
		// get the number of planes for this house or side
		char key[0x40];
		_snprintf_s(key, 0x3F, "%s.Count", pID);
		int count = pINI->ReadInteger(section, key, defCount);

		// parse every plane
		ret->SetCapacity(count, NULL);
		for(int i=0; i<count; ++i) {
			if(i>=ret->Count) {
				ret->AddItem(NULL);
			}
			
			ParadropPlane* pPlane = ParseParaDrop(base, i);
			if(pPlane) {
				pData->ParaDropPlanes.AddItem(pPlane);
				ret->Items[i] = pPlane;
			}
		}
	};

	// now load the paradrops
	// 0: default
	// 1 to n: n sides
	// n+1 to n+m+1: m countries

	// default
	CreateParaDropBase(NULL, base);
	GetParadropPlane(base, 1, &pData->ParaDrop[NULL]);

	// put all sides into the hash table
	for(int i=0; i<SideClass::Array->Count; ++i) {
		SideClass *pSide = SideClass::Array->GetItem(i);
		CreateParaDropBase(pSide->ID, base);
		GetParadropPlane(base, pData->ParaDrop[NULL].Count, &pData->ParaDrop[pSide]);
	}

	// put all countries into the hash table
	for(int i=0; i<HouseTypeClass::Array->Count; ++i) {
		HouseTypeClass *pTHouse = HouseTypeClass::Array->GetItem(i);
		CreateParaDropBase(pTHouse->ID, base);
		GetParadropPlane(base, pData->ParaDrop[SideClass::Array->GetItem(pTHouse->SideIndex)].Count, &pData->ParaDrop[pTHouse]);
	}
}