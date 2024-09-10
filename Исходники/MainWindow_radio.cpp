	void MainWindow::radioSetMuted(bool muted) {
		radioMuted = muted;
		if (currentStream)
			BASS_ChannelSetAttribute(currentStream, BASS_ATTRIB_VOL,
			radioGetVolume());

		if (OSUtil::IsVistaOrLater()) {
			SendMessage(volumePbar, PBM_SETSTATE, muted ?
				(isColorblindModeEnabled ? PBST_PAUSED : PBST_ERROR) :
				PBST_NORMAL, (LPARAM)0);
		} else if (IsAppThemed() == FALSE) {
			SendMessage(volumePbar, PBM_SETBARCOLOR,
				(WPARAM)0, (LPARAM)(muted ? RGB(255, 0, 0) : CLR_DEFAULT));
		}

		ShowWindow(volumePbar, SW_SHOW);
		if (muted)
			KillTimer(window, hideVolBarTimerId);
		else
			SetTimer(window, hideVolBarTimerId, 1000, nullptr);

		updateStatusLabel();

		if (OSUtil::IsWin7OrLater()) {
			ITaskbarList3 *taskbarList;
			if (SUCCEEDED(CoCreateInstance(CLSID_TaskbarList, nullptr,
				CLSCTX_INPROC_SERVER, __uuidof(taskbarList),
				reinterpret_cast<void**>(&taskbarList)))) {

				HICON icon = LoadIcon(instance,
					MAKEINTRESOURCE(muted ? IDI_ICON_SOUND : IDI_ICON_MUTE));

				THUMBBUTTON thumbButtons[1];

				thumbButtons[0].dwMask = THB_ICON;
				thumbButtons[0].iId = thumbBarMuteBtnId;
				thumbButtons[0].hIcon = icon;

				taskbarList->ThumbBarUpdateButtons(window, 1, thumbButtons);

				DeleteObject((HGDIOBJ)icon);

				taskbarList->SetProgressValue(window, muted ? 100UL : 0UL,
					100UL);
				taskbarList->SetProgressState(window, muted ? TBPF_ERROR :
					TBPF_NOPROGRESS);

				taskbarList->Release();
			}
		}
	}