static LRESULT CALLBACK WndProc(HWND Hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch(Msg)
	{
	case WM_CLOSE:
		DestroyWindow(Hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_DEVICECHANGE:
		{
			//bool Arrival=false;
			switch(wParam)
			{
			case DBT_DEVICEARRIVAL:
				//Arrival=true;
			case DBT_DEVICEREMOVECOMPLETE:
				{

					auto Pbh = reinterpret_cast<PDEV_BROADCAST_HDR>(lParam);
					if(Pbh->dbch_devicetype==DBT_DEVTYP_VOLUME)
					{
						// currently we don't care what actually happened, "just a notification" is OK

						//auto Pdv=reinterpret_cast<PDEV_BROADCAST_VOLUME>(Pbh);
						//bool Media = Pdv->dbcv_flags & DBTF_MEDIA != 0;
						Notifier().at(devices_notify).notify(std::make_unique<payload>());
					}
				}
				break;

			}
		}
		break;

	case WM_SETTINGCHANGE:
		if(lParam)
		{
			if (!StrCmp(reinterpret_cast<LPCWSTR>(lParam),L"Environment"))
			{
				if (Global->Opt->UpdateEnvironment) 
				{
					Notifier().at(environment_notify).notify(std::make_unique<payload>());
				}
			}
			else if (!StrCmp(reinterpret_cast<LPCWSTR>(lParam),L"intl"))
			{
				Notifier().at(intl_notify).notify(std::make_unique<payload>());
			}
		}
		break;

	case WM_POWERBROADCAST:
		switch(wParam)
		{
		case PBT_APMPOWERSTATUSCHANGE: // change status

		case PBT_POWERSETTINGCHANGE:   // change percent
			Notifier().at(power_notify).notify(std::make_unique<payload>());
			break;
		// TODO:
		// PBT_APMSUSPEND & PBT_APMRESUMEAUTOMATIC handlers

		}

		break;

	}
	return DefWindowProc(Hwnd, Msg, wParam, lParam);
}