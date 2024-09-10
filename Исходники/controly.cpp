int controlyPlugin::launchItem(QList<InputData>* id, CatItem* item)
{
	item = item; // Compiler warning

	if (id->count() == 1) {
		// no parameters, just the item itsef

		QString path = item->fullPath;

		if (path.contains(",@")) {
			// dll cpl item indexing containing items, e.g. 'main.cpl,@1'

			runProgram("control.exe", item->fullPath); //runProgram(cmd, args);
			// use toNativeSeparators()?
		} else if ((path.startsWith("csidl:", Qt::CaseInsensitive)) && (path.endsWith(".controly", Qt::CaseSensitive))) {
			// Constant special item ID list (CSIDL)

			// shell instance object (special shell extension folder), e.g. 'csidl:0x0014.controly' ('shellinstance:0x0014')
			QString folderId = path.mid(strlen("csidl:"), strlen(path.toAscii())-strlen("csidl:")-strlen(".controly")); // e.g. 0x0014 = CSIDL_FONTS;
			bool ok;
			int folderIdx = folderId.toLong(&ok, 16);
			if (ok) {
				LPITEMIDLIST pidl;
				HRESULT hres = SHGetFolderLocation(NULL, folderIdx, NULL, 0, &pidl);
				if (hres == S_OK) {
					SHELLEXECUTEINFO sei;
					memset(&sei, 0, sizeof(sei));
					sei.cbSize = sizeof(SHELLEXECUTEINFO);
					sei.fMask = SEE_MASK_IDLIST;
					sei.hwnd = NULL;
					sei.lpVerb = NULL;
					sei.lpFile = NULL;
					sei.lpParameters = NULL;
					sei.lpDirectory = NULL;
					sei.nShow = SW_SHOW;
					sei.hInstApp = NULL;
					sei.lpIDList = pidl;
					sei.hProcess = NULL;
					//it seems we don't need CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
					ShellExecuteEx(&sei);

					CoTaskMemFree((void*)pidl); // needs objbase.h/ole32.lib
				}
			}
		} else {
			// exe cpl item with command line parameters, e.g. 'rundll32.exe shell32.dll,Options_RunDLL 1'
			// or item defined via application name, e.g. 'control.exe /name Microsoft.WindowsUpdate'

			QStringList spl = path.split(".exe ");
			if (spl.size() == 2) {
				// split size currently is always 2, as assured above
				QString executable = spl[0] + ".exe";
				QString parameters = spl[1];
				runProgram(executable, parameters);
			} else {
				runProgram(path, "");
			}
		}

		return 1;
	}

	if (id->count() != 2)
		return 1;

	CatItem last = id->last().getTopResult();
	QSettings* set = *settings;
	if (set == NULL) return 1;
	if (last.shortName == "Options") {
		set->setValue("controly/OptionsCount", set->value("controly/OptionsCount",0).toInt() + 1);
		return MSG_CONTROL_OPTIONS;
	}
	else if (last.shortName == "Rebuild Index") {
		set->setValue("controly/RebuildCount", set->value("controly/RebuildCount",0).toInt() + 1);
		return MSG_CONTROL_REBUILD;
	}
	else if (last.shortName == "Exit") {
		set->setValue("controly/ExitCount", set->value("controly/ExitCount",0).toInt() + 1);
		return MSG_CONTROL_EXIT;
	}
	return 1;

}