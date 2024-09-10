static VOID
Adv_SaveData(HWND hwndDlg)
{
	BOOL bSystrayBatteryMeter;
	BOOL bPasswordLogon;
	BOOL bVideoDimDisplay;

	bSystrayBatteryMeter =
		(IsDlgButtonChecked(hwndDlg, IDC_SYSTRAYBATTERYMETER) == BST_CHECKED);

	bPasswordLogon =
		(IsDlgButtonChecked(hwndDlg, IDC_PASSWORDLOGON) == BST_CHECKED);

	bVideoDimDisplay =
		(IsDlgButtonChecked(hwndDlg, IDC_VIDEODIMDISPLAY) == BST_CHECKED);

	if (bSystrayBatteryMeter)
	{
		if (!(gGPP.user.GlobalFlags & EnableSysTrayBatteryMeter))
		{
			gGPP.user.GlobalFlags = gGPP.user.GlobalFlags + EnableSysTrayBatteryMeter;
		}
	}
	else
	{
		if ((gGPP.user.GlobalFlags & EnableSysTrayBatteryMeter))
		{
			gGPP.user.GlobalFlags = gGPP.user.GlobalFlags - EnableSysTrayBatteryMeter;
		}
	}

	if (bPasswordLogon)
	{
		if (!(gGPP.user.GlobalFlags & EnablePasswordLogon))
		{
			gGPP.user.GlobalFlags = gGPP.user.GlobalFlags + EnablePasswordLogon;
		}
	}
	else
	{
		if ((gGPP.user.GlobalFlags & EnablePasswordLogon))
		{
			gGPP.user.GlobalFlags = gGPP.user.GlobalFlags - EnablePasswordLogon;
		}
	}

	if (bVideoDimDisplay)
	{
		if (!(gGPP.user.GlobalFlags & EnableVideoDimDisplay))
		{
			gGPP.user.GlobalFlags = gGPP.user.GlobalFlags + EnableVideoDimDisplay;
		}
	}
	else
	{
		if ((gGPP.user.GlobalFlags & EnableVideoDimDisplay))
		{
			gGPP.user.GlobalFlags = gGPP.user.GlobalFlags - EnableVideoDimDisplay;
		}
	}

	if (!IsBatteryUsed())
	{
		SaveCurrentPowerActionPolicy(GetDlgItem(hwndDlg, IDC_POWERBUTTON), &gGPP.user.PowerButtonAc);
#if 0
		SaveCurrentPowerActionPolicy(GetDlgItem(hwndDlg, IDC_LIDCLOSE), &gGPP.user.LidCloseAc);
		SaveCurrentPowerActionPolicy(GetDlgItem(hwndDlg, IDC_SLEEPBUTTON), &gGPP.user.SleepButtonAc);
#endif
	}
	else
	{
#if 0
		SaveCurrentPowerActionPolicy(GetDlgItem(hwndDlg, IDC_POWERBUTTON), &gGPP.user.PowerButtonDc);
		SaveCurrentPowerActionPolicy(GetDlgItem(hwndDlg, IDC_LIDCLOSE), &gGPP.user.LidCloseDc);
		SaveCurrentPowerActionPolicy(GetDlgItem(hwndDlg, IDC_SLEEPBUTTON), &gGPP.user.SleepButtonDc);
#endif
	}

	if (!WriteGlobalPwrPolicy(&gGPP))
	{
		MessageBox(hwndDlg, L"WriteGlobalPwrPolicy failed", NULL, MB_OK);
	}

	Adv_InitDialog();
}