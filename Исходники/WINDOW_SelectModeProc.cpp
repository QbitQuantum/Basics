//Handle Select Mode dialog box
INT_PTR CALLBACK WINDOW::SelectModeProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDOK:	//If OK was pressed
				{
					//Make changes to resolution
					if(IsDlgButtonChecked(hWnd, IDC_640))
					{
						Instance()->width=640;
						Instance()->height=480;
					}
					if(IsDlgButtonChecked(hWnd, IDC_800))
					{
						Instance()->width=800;
						Instance()->height=600;
					}
					if(IsDlgButtonChecked(hWnd, IDC_1024))
					{
						Instance()->width=1024;
						Instance()->height=768;
					}

					EndDialog(hWnd, wParam);
					return true;
				}
			}

			switch (HIWORD(wParam))
			{
			case BN_CLICKED:	//If a button was pressed
				{
					CheckDlgButton(hWnd, lParam, BST_CHECKED);

					//If it is the fullscreen button, change the variable
					if((int)LOWORD(wParam) == IDC_FULLSCREEN)
						Instance()->fullscreen=!Instance()->fullscreen;

					//If it is an AA settings button, save the nuber of samples
					if((int) LOWORD(wParam) == IDC_NOAA)
						Instance()->numSamples=0;

					for(int i=2; i<16; ++i)
					{
						if((int) LOWORD(wParam)==IDC_2AA+i-2)
							Instance()->numSamples=i;
					}

					return true;
				}
			}

			break;
		}

	case WM_INITDIALOG:		//Initiate dialog box
		{
			//Set default resolution
			if(Instance()->width==640)
				CheckRadioButton(hWnd, IDC_640, IDC_1024, IDC_640);
			if(Instance()->width==800)
				CheckRadioButton(hWnd, IDC_640, IDC_1024, IDC_800);
			if(Instance()->width==1024)
				CheckRadioButton(hWnd, IDC_640, IDC_1024, IDC_1024);

			//Set default full screen
			if(Instance()->fullscreen)
				CheckDlgButton(hWnd, IDC_FULLSCREEN, true);

			//Grey out the unsupported AA modes
			HWND buttonHWnd;
			for(int i=2; i<=16; ++i)
			{
				//requires that 2AA - 16AA have sequential ID numbers
				buttonHWnd=GetDlgItem(hWnd, IDC_2AA+(i-2));

				EnableWindow(buttonHWnd, Instance()->samplesSupported[i]);
			}

			//Set default to no AA
			CheckRadioButton(hWnd, IDC_NOAA, IDC_16AA, IDC_NOAA);

			return true;
		}
	}

	return false;
}