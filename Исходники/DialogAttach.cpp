//------------------------------------------------------------------------------
// Name: update_list(const QString &filter)
// Desc:
//------------------------------------------------------------------------------
void DialogAttach::update_list(const QString &filter) {

	QMap<edb::pid_t, ProcessInfo> procs;
	edb::uid_t myUID = 0;

	// FILL up procs
	HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(handle != INVALID_HANDLE_VALUE) {
		PROCESSENTRY32 lppe;

		std::memset(&lppe, 0, sizeof(lppe));
		lppe.dwSize = sizeof(lppe);

		if(Process32First(handle, &lppe)) {
			do {
				ProcessInfo pi;
				pi.pid = lppe.th32ProcessID;
				pi.uid = 0; // TODO
				pi.name = QString::fromWCharArray(lppe.szExeFile);

				HANDLE hProc = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, lppe.th32ProcessID);
				if(hProc != 0) {
					BOOL wow64 = FALSE;
					if(fnIsWow64Process && fnIsWow64Process(hProc, &wow64) && wow64) {
						pi.name += " *32";
					}

					pi.user = dumpToken(hProc);

					CloseHandle(hProc);
				}

				procs[pi.pid] = pi;

				std::memset(&lppe, 0, sizeof(lppe));
				lppe.dwSize = sizeof(lppe);
			} while(Process32Next(handle, &lppe));
		}

		CloseHandle(handle);
	}

	const bool filterUID = ui->filter_uid->isChecked();
	const QString lowerFilter = filter.toLower();
	ui->processes_table->setSortingEnabled(false);
	ui->processes_table->setRowCount(0);

	Q_FOREACH(const ProcessInfo &procInfo, procs) {

		const QString procName = procInfo.name;

		if(filter.isEmpty() || procName.toLower().contains(lowerFilter)) {
			if(!filterUID || procInfo.uid == myUID) {
				const int row = ui->processes_table->rowCount();
				ui->processes_table->insertRow(row);

				QTableWidgetItem *const itemPID = new QTableWidgetItem;
				itemPID->setData(Qt::DisplayRole, static_cast<quint32>(procInfo.pid));

				QTableWidgetItem *itemUID;
				if(!procInfo.user.isEmpty()) {
					itemUID = new QTableWidgetItem(procInfo.user);
				} else {
					itemUID = new QTableWidgetItem;
					itemUID->setData(Qt::DisplayRole, static_cast<quint32>(procInfo.uid));
				}

				ui->processes_table->setItem(row, 0, itemPID);
				ui->processes_table->setItem(row, 1, itemUID);
		        ui->processes_table->setItem(row, 2, new QTableWidgetItem(procInfo.name));
			}
		}
	}
	ui->processes_table->setSortingEnabled(true);
}