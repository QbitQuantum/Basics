int __cdecl _tmain(int argc, _TCHAR *argv[])
{
	HDEVINFO h = NULL;
	SP_DEVINFO_DATA dev_info_data;
	ULONG status = 0, problem = 0;
	BOOL bDevice = FALSE;

	if (IsWow64()) {
		logPrint("Your are runing 32bit VirtualMonitor on 64bit windows\n");
		logPrint("Please Download 64bit version of VirtualMonitor\n");
		return -1;
	}
	if (argc < 2 || !strcmp(argv[1], "-h")) {
		usage(argv);
		goto out;
	}

	GetWinVersion();
	if (!isSupport) {
		logPrint("Unsupported Windows system\n");
		goto out;
	}
	if (isVista || isWin7) {
		if (!IsUserAnAdmin()) {
			logPrint("Access Denied. Administrator permissions are needed to use the selected options.");
			logPrint("Use an administrator command prompt to complete these tasks.");
			goto out;
		}
	}

	if (!strcmp(argv[1], "-i")) {
		FixInfFile(INF);
	}
	h = GetDevInfoFromDeviceId(&dev_info_data, DRIVER_NAME);
	if (!strcmp(argv[1], "-i")) {
		if (h) {
			logPrint("Driver already installed\n");
			goto out;
		}
		if (!logInit()) {
			goto out;
		}
		logPrint("Installing driver, It may take few minutes. please wait\n");
		RegClean();
		InstallInf(INF);
		if (isVista || isWin7) {
			DisableMirror();
		}
		h = GetDevInfoFromDeviceId(&dev_info_data, DRIVER_NAME);
		if (!h) {
			logError("GetDevInfo Failed After Driver Installed\n");
		}
		GetDevStatus(h, &dev_info_data, &status, &problem);
		bDevice = DetectVirtualMonitor(FALSE);
		logInfo("Driver Status: %x, problem: %x\n", status, problem);
		if (!bDevice) {
			DetectVirtualMonitor(TRUE);
			logPrint("Driver installed Status: %x, problem: %x\n", status, problem);
			logPrint("Please reboot your system\n");
		} else {
			logPrint("Driver installed successful\n");
		}
		if (isVista || isWin7) {
			logPrint("Please reboot your system\n");
		}
	} else if (!strcmp(argv[1], "-u")) {
		if (!h) {
			logPrint("Driver not found\n");
		} else {
			if (!logInit()) {
				goto out;
			}
			UnInstallDriver(h, &dev_info_data);
			if (isVista || isWin7) {
				CleanOemInf();
			}
			RegClean();
			logPrint("Driver Uninstalled sucessful, Please Reboot System\n");
		}
	} else {
		usage(argv);
		goto out;
	}
out:
	if (g_logf)
		fclose(g_logf);
	if (h) {
			DestroyDevInfo(h);
	}
	exit(0);
}