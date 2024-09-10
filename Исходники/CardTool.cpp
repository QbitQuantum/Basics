int main(int argc, char *argv[])
{
	int Index = 0;
	int Arg = 1;
	char *VirtualCard = NULL;
	BCAS::Manager::Abstract *Card;

	argc--;
	while (argc > 0) {
		if (strcmp(argv[Arg], "-virtual") == 0) {
			if (argc == 1) {
				printf("Missing file parameter.\n");
				return 1;
			}	
			VirtualCard = _strdup(argv[++Arg]);
			argc--;
		} else if (strcmp(argv[Arg], "-reader") == 0) {
			if (argc == 1) {
				printf("Missing file parameter.\n");
				return 1;
			}
			Index = atoi(argv[++Arg]);
			argc--;
		} else if (strcmp(argv[Arg], "-list") == 0) {
			Index = -1;
		} else {
			printf("Invalid parameter: %s\n", argv[Arg]);
			return 1;
		}
		Arg++;
		argc--;
	}

	if (VirtualCard == NULL) {
		SCARDCONTEXT Ctx;
		LONG Result;
		char *Reader = NULL;

		Result = SCardEstablishContext(SCARD_SCOPE_USER, NULL, NULL, &Ctx);

		if (Result != SCARD_S_SUCCESS) {
			printf("Failed to establish context, error: %08x\n", Result);
			return 1;
		}

		DWORD Count = SCARD_AUTOALLOCATE;
		LPTSTR Readers = NULL;

		Result = SCardListReaders(Ctx, NULL, (LPTSTR)&Readers, &Count);
		if (Result != SCARD_S_SUCCESS) {
			if (Result == SCARD_E_NO_READERS_AVAILABLE)
				printf("No card readers available.\n");
			else
				printf("Failed to list card readers, error: %08x\n", Result);
			SCardReleaseContext(Ctx);
			return 1;
		}

		LPTSTR R = Readers;
		Count = 0;
		while (*R != 0) {
			if (Index == Count) {
				Reader = _strdup(R);
				break;
			} else if (Index == -1) {
				printf("Reader %d: %s\n", Count, R);
			}
			R += strlen(R) + 1;
			Count++;
		}
		SCardFreeMemory(Ctx, Readers);

		if (Reader == NULL) {
			if (Index != -1)
				printf("Cannot find a reader at index %d\n", Index);
			SCardReleaseContext(Ctx);
			return 1;
		}
		BCAS::Manager::Card *RealCard = new BCAS::Manager::Card;
		RealCard->SetReader(Reader);
		Card = RealCard;
	} else {
		BCAS::Manager::Virtual *Dump = new BCAS::Manager::Virtual;
		Dump->SetReader(VirtualCard);
		Card = Dump;
	}

	BCAS::Keys::RegisterAll();

	Card->Init();
	BCAS::Manager::Ops *Ops = new BCAS::Manager::Ops;
	Ops->SetCard(Card);

	BCAS::Manager::Manager *Mgr = new BCAS::Manager::Manager(Ops);

	bool Quit = false;
	u16 Date;
	SYSTEMTIME Time;

	GetSystemTime(&Time);
	Date = ConvertDateToMJD(Time.wYear, Time.wMonth & 0xff, Time.wDay & 0xff) + 7;

	while (!Quit) {
		bool NewCard = false;
		bool HasCard;
		u16 Expiry;

		HasCard = Card->WaitForEvent(NewCard);
		if (NewCard == true) {
			Mgr->PrintCardInformation(CardType);
			if (CardType == kType_INVALID)
				break;
			PrintMenu();
			continue;
		}
		if (HasCard == false) {
			if (_kbhit()) {
				int Selection = _getch();
				if (Selection == 27) {
					break;
				}
				if (Selection == 0)
					_getch();
			}
			continue;
		}

		int Key = _getch();
		switch (Key) {
		case 27:
				Quit = true;
				break;

		case 0:
			Key = _getch();
			switch (Key) {
			case 59:
				Mgr->DumpMode();
				break;
			case 60:
				Mgr->PrintEntitlements();
				break;
			case 61:
				Mgr->PrintEmail();
				break;
			case 62:
				DateState = (DateState + 1) % 7;
				switch (DateState) {
				case 0:
					Expiry = 7;
					break;
				case 1:
					Expiry = 15;
					break;
				case 2:
					Expiry = 30;
					break;
				case 3:
					Expiry = 90;
					break;
				case 4:
					Expiry = 180;
					break;
				case 5:
					Expiry = 365 * 2;
					break;
				case 6:
					break;
				}
				if (DateState != 6) {
					GetSystemTime(&Time);
					Date = ConvertDateToMJD(Time.wYear, Time.wMonth & 0xff, Time.wDay & 0xff) + Expiry;
				} else {
					Date = 0xffff;
				}
				break;

			default:
				printf("%d\n", Key);
				break;
			}
			break;

		// UpdateTiers
		case 49:
			Mgr->AddEntitlement(BCAS::Keys::KEYSET_WOWOW, Date);
			break;
		case 50:
			Mgr->AddEntitlement(BCAS::Keys::KEYSET_STARCHANNELHD, Date);
			break;
		case 51:
			Mgr->AddEntitlement(BCAS::Keys::KEYSET_E2_110CS, Date);
			break;
		case 52:
			Mgr->AddEntitlement(BCAS::Keys::KEYSET_SAFETYNET, Date);
			break;
		case 53:
			Mgr->AddEntitlement(BCAS::Keys::KEYSET_NHK, Date);
			break;

		// InvalidateTiers
		case 113:
			Mgr->InvalidateEntitlement(BCAS::Keys::KEYSET_WOWOW);
			break;
		case 119:
			Mgr->InvalidateEntitlement(BCAS::Keys::KEYSET_STARCHANNELHD);
			break;
		case 101:
			Mgr->InvalidateEntitlement(BCAS::Keys::KEYSET_E2_110CS);
			break;
		case 114:
			Mgr->InvalidateEntitlement(BCAS::Keys::KEYSET_SAFETYNET);
			break;
		case 116:
			Mgr->InvalidateEntitlement(BCAS::Keys::KEYSET_NHK);
			break;

		// DeleteEmail
		case 97:
			Mgr->DeleteEmail(BCAS::Keys::KEYSET_WOWOW);
			break;
		case 115:
			Mgr->DeleteEmail(BCAS::Keys::KEYSET_STARCHANNELHD);
			break;
		case 100:
			Mgr->DeleteEmail(BCAS::Keys::KEYSET_E2_110CS);
			break;
		case 102:
			Mgr->DeleteEmail(BCAS::Keys::KEYSET_SAFETYNET);
			break;
		case 103:
			Mgr->DeleteEmail(BCAS::Keys::KEYSET_NHK);
			break;
		case 104:
			Mgr->DeleteEmail(BCAS::Keys::KEYSET_EMAIL);
			break;

		// ActivateTrial
		case 122:
			Mgr->ActivateTrial(BCAS::Keys::KEYSET_WOWOW, false, Date);
			Mgr->ActivateTrial(BCAS::Keys::KEYSET_WOWOW, true, Date);
			break;
		case 120:
			Mgr->ActivateTrial(BCAS::Keys::KEYSET_STARCHANNELHD, false, Date);
			Mgr->ActivateTrial(BCAS::Keys::KEYSET_STARCHANNELHD, true, Date);
			break;
		case 99:
			Mgr->ActivateTrial(BCAS::Keys::KEYSET_E2_110CS, false, Date);
			Mgr->ActivateTrial(BCAS::Keys::KEYSET_E2_110CS, true, Date);
			break;
		case 118:
			Mgr->ActivateTrial(BCAS::Keys::KEYSET_SAFETYNET, false, Date);
			Mgr->ActivateTrial(BCAS::Keys::KEYSET_SAFETYNET, true, Date);
			break;
		case 98:
			Mgr->ActivateTrial(BCAS::Keys::KEYSET_NHK, false, Date);
			Mgr->ActivateTrial(BCAS::Keys::KEYSET_NHK, true, Date);
			break;

		default:
			printf("%d\n", Key);
			break;
		}

		if (!Quit)
			PrintMenu();
	}

	return 0;
}