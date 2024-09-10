// Mesage handler for work box.
LRESULT CALLBACK DrugProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	const int nrItem = 5;

	switch (message)
	{
		case WM_INITDIALOG:
			SendMessage(hDlg, WM_COMMAND, UPDATE_DLG, NULL);
		break;
		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK)
			{
				if(EmptyBox(hDlg, IDC_FIT, nrItem) != true)
				{
					SendMessage(hDlg, WM_COMMAND, SAVE_DLG, NULL);
					MessageBox(hDlg, "Now the Drug is saved \nJust load the game...", "Now Saved", MB_OK);
					DestroyWindow(hDlg);
				}
			}
			if (LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			if (LOWORD(wParam) == IDC_LOAD) 
			{	
				SendMessage(hDlg, WM_COMMAND, SAVE_DLG, NULL);
				EndDialog(hDlg, LOWORD(wParam));
				DialogBox(hInst, (LPCTSTR)IDD_STARTDLG, NULL, (DLGPROC)Start);
			}
			if (LOWORD(wParam) == IDC_DELETE) 
			{
				char objectName[MAX_NAME_LENGTH];
				strcpy(objectName, drug[activeDrug].name);

				for(int i = activeDrug; i < antDrug-1; i++)
				{
					strcpy(drug[i].name, drug[i+1].name);
					strcpy(drug[i].text, drug[i+1].text);
					drug[i].id = i;
					drug[i].nWage = drug[i+1].nWage;
					drug[i].nCostInSleep = drug[i+1].nCostInSleep;
					drug[i].nFitnes = drug[i+1].nFitnes;
				}

				strcpy(drug[i].name, "");
				strcpy(drug[i].text, "");
				drug[i].id = 0;
				drug[i].nCostInSleep = 0;
				drug[i].nWage = 0;
				drug[i].nFitnes = 0;

				if(antDrug > 0)
					antDrug--;

				activeDrug--;

				SendMessage(hDlg, WM_COMMAND, UPDATE_DLG, NULL);
				MessageBox(hDlg, "Object Deleted", objectName, MB_OK | MB_ICONEXCLAMATION);
			}
			if (LOWORD(wParam) == IDC_RIGHT) 
			{	
				if(EmptyBox(hDlg, IDC_FIT, nrItem) != true)
				{
					SendMessage(hDlg, WM_COMMAND, SAVE_DLG, NULL);
					if(activeDrug < antDrug-1)
					{
						activeDrug++;
					}
					else
					{
						if(MessageBox(hDlg, "Add one more Drug object?", "Add?", MB_ICONQUESTION | MB_YESNO) == IDYES)
							if(antDrug < MAX_WORK)
							{
								antDrug++;
								activeDrug++;
								drug[activeDrug].id = activeDrug;
							}
							else
								MessageBox(hDlg, "Max Drug\n Contact programmer !!!", "Array overflow", MB_OK);
					}
					SendMessage(hDlg, WM_COMMAND, UPDATE_DLG, NULL);
				}
			}

			if (LOWORD(wParam) == IDC_LEFT) 
			{	
				SendMessage(hDlg, WM_COMMAND, SAVE_DLG, NULL);
				if(activeDrug > 0)
					activeDrug--;

				SendMessage(hDlg, WM_COMMAND, UPDATE_DLG, NULL);
			}
			if (LOWORD(wParam) == UPDATE_DLG) 
			{	
				char* str[nrItem+1];

				str[0] = IntToChar(drug[activeDrug].id);
				str[1] = IntToChar(drug[activeDrug].nFitnes);
				str[2] = IntToChar(drug[activeDrug].nCostInSleep);
				str[3] = IntToChar(drug[activeDrug].nWage);
				str[4] = drug[activeDrug].name;
				str[5] = drug[activeDrug].text;


				int i = 0;
				for(int  item = IDC_ID; i < nrItem+1; i++, item++)
					SetDlgItemText(hDlg, item, str[i]);	
			}
			if (LOWORD(wParam) == SAVE_DLG) 
			{
				String str[nrItem];
				char* tmpStr;
				int i= 0;
				int len;
				bool emptyBox = false;
				for(int  item = IDC_FIT; i < nrItem && emptyBox != true; i++, item++)
				{
					len = GetWindowTextLength(GetDlgItem(hDlg, item));
					if(len > 0)
					{
						tmpStr = (char*)GlobalAlloc(GPTR, len + 1);
						GetDlgItemText(hDlg, item, tmpStr, len + 1);
						str[i] = tmpStr;
						GlobalFree((HANDLE)tmpStr);	
					}
					else
					{
						emptyBox = true;
						MessageBox(hDlg, "All fields are not filled!!!", "Oups!", MB_OK);
					}
				}

				if(emptyBox == false)
				{
					drug[activeDrug].id = activeDrug;
					drug[activeDrug].nFitnes = str[0].convertToInt();
					drug[activeDrug].nCostInSleep = str[1].convertToInt();
					drug[activeDrug].nWage = str[2].convertToInt();
					strcpy(drug[activeDrug].name, str[3].getString());
					strcpy(drug[activeDrug].text, str[4].getString());

					NewSaveDrug(file);
				}
			}
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			return TRUE;	
	}
    return FALSE;
}