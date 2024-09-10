void CALLBACK dispatchEvents(SIMCONNECT_RECV*  pData, DWORD  cbData, void *  pContext)
{
	HRESULT hr;

	switch (pData->dwID)
	{
	case SIMCONNECT_RECV_ID_EVENT:
	{
		SIMCONNECT_RECV_EVENT *evt = (SIMCONNECT_RECV_EVENT*)pData;

		switch (evt->uEventID)
		{
		case STARTUP:
			stats.lastDeleted = 0;
			stats.nrOfDeletions = 0;
			stats.nrOfRequests = 0;
			// Now the sim is running, request information on the user aircraft
			hr = SimConnect_RequestDataOnSimObjectType(hSimConnect, R1, AIPARKDATA, conf.radius, SIMCONNECT_SIMOBJECT_TYPE_AIRCRAFT);
			++stats.nrOfRequests;
			break;


		case R2:
			fsecCnt++;

			if (fsecCnt >= (conf.requestEveryXSec/4))
			{
				fsecCnt = 0;
				if (SUCCEEDED(SimConnect_RequestDataOnSimObjectType(hSimConnect, R1, AIPARKDATA, conf.radius, SIMCONNECT_SIMOBJECT_TYPE_AIRCRAFT)))
				{
					++stats.nrOfRequests;
				}
			}
			break;

		case MENU:
			getMenu(menu, sizeof(menu));
			SimConnect_Text(hSimConnect, SIMCONNECT_TEXT_TYPE_MENU, 0, SELECTION, sizeof(menu), (void*)menu);
			break;

		case SELECTION:
			res = (SIMCONNECT_TEXT_RESULT)(evt->dwData);
			switch (res) {
			case SIMCONNECT_TEXT_RESULT_MENU_SELECT_1:
				if (conf.requestEveryXSec < 3600)
				{
					conf.requestEveryXSec += 30;
				}
				getMenu(menu, sizeof(menu));
				SimConnect_Text(hSimConnect, SIMCONNECT_TEXT_TYPE_MENU, 0, SELECTION, sizeof(menu), (void*)menu);
				break;

			case SIMCONNECT_TEXT_RESULT_MENU_SELECT_2:
				if (conf.requestEveryXSec > 45)
				{
					conf.requestEveryXSec -= 30;
				}
				getMenu(menu, sizeof(menu));
				SimConnect_Text(hSimConnect, SIMCONNECT_TEXT_TYPE_MENU, 0, SELECTION, sizeof(menu), (void*)menu);
				break;

			case SIMCONNECT_TEXT_RESULT_MENU_SELECT_3:
				if (conf.radius < 190000)
				{
					conf.radius += 5000;
				}
				getMenu(menu, sizeof(menu));
				SimConnect_Text(hSimConnect, SIMCONNECT_TEXT_TYPE_MENU, 0, SELECTION, sizeof(menu), (void*)menu);
				break;

			case SIMCONNECT_TEXT_RESULT_MENU_SELECT_4:
				if (conf.radius > 5000)
				{
					conf.radius -= 5000;
				}
				getMenu(menu, sizeof(menu));
				SimConnect_Text(hSimConnect, SIMCONNECT_TEXT_TYPE_MENU, 0, SELECTION, sizeof(menu), (void*)menu);
				break;

			case SIMCONNECT_TEXT_RESULT_MENU_SELECT_5:
				if (conf.maxetd > 5400)
				{
					conf.maxetd -= 3600;
				}
				getMenu(menu, sizeof(menu));
				SimConnect_Text(hSimConnect, SIMCONNECT_TEXT_TYPE_MENU, 0, SELECTION, sizeof(menu), (void*)menu);
				break;


			case SIMCONNECT_TEXT_RESULT_MENU_SELECT_6:
				if (conf.maxetd < 7*86400) // must be smaller than a week
				{
					conf.maxetd += 3600;
				}
				getMenu(menu, sizeof(menu));
				SimConnect_Text(hSimConnect, SIMCONNECT_TEXT_TYPE_MENU, 0, SELECTION, sizeof(menu), (void*)menu);
				break;

			case SIMCONNECT_TEXT_RESULT_MENU_SELECT_8:
				SimConnect_Text(hSimConnect, SIMCONNECT_TEXT_TYPE_MENU, 0, SELECTION, sizeof(empty), (void*)empty);
				break;
			default: //default cannot be close as displayed is also an event
				break;
			}
			saveConfig(conf);
			break;
		default:
			break;
		}
		break;
	}


	case SIMCONNECT_RECV_ID_SIMOBJECT_DATA_BYTYPE:
	{
		SIMCONNECT_RECV_SIMOBJECT_DATA_BYTYPE *pObjData = (SIMCONNECT_RECV_SIMOBJECT_DATA_BYTYPE*)pData;

		switch (pObjData->dwRequestID)
		{
		case R1:
		{
			DWORD ObjectID = pObjData->dwObjectID;
			DWORD entry = pObjData->dwentrynumber;
			DWORD outof = pObjData->dwoutof;
			DWORD length = pObjData->dwDefineCount;
			AIData *pS = (AIData*)&pObjData->dwData;
			if (ObjectID != SIMCONNECT_OBJECT_ID_USER)
			{
				if (strcmp(pS->state, "sleep") == 0 && pS->ETD > conf.maxetd)
				{
					if (FS10DeleteAIAircraft != NULL)
					{
						FS10DeleteAIAircraft(ObjectID, 1);
						++stats.nrOfDeletions;
						deletedSome = true;
					}
				}
			}

			if (entry == outof)
			{
				if (deletedSome)
				{
					stats.lastDeleted = GetTickCount64();
				}
				deletedSome = false;
			}


		}

		default:
			break;
		}
		break;
	}

	case SIMCONNECT_RECV_ID_EXCEPTION:
	{
		SIMCONNECT_RECV_EXCEPTION *except = (SIMCONNECT_RECV_EXCEPTION*)pData;
		printf("\n\n***** EXCEPTION=%d  SendID=%d  Index=%d  cbData=%d\n", except->dwException, except->dwSendID, except->dwIndex, cbData);
		break;
	}

	case SIMCONNECT_RECV_ID_QUIT:
	{
		quit = 1;
		break;
	}

	default:
		printf("\nReceived:%d", pData->dwID);
		break;
	}
}