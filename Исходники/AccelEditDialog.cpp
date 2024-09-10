bool VDDialogEditAccelerators::OnCommand(uint32 id, uint32 extcode) {
	if (id == IDC_FILTER) {
		if (extcode == EN_CHANGE) {
			VDStringA s("*");
			s += VDTextWToA(GetControlValueString(id)).c_str();
			s += '*';

			RefilterCommands(s.c_str());
			return true;
		}
	} else if (id == IDC_ADD) {
		VDUIAccelerator accel;

		int selIdx = LBGetSelectedIndex(IDC_AVAILCOMMANDS);

		if ((size_t)selIdx < mFilteredCommands.size()) {
			const VDAccelToCommandEntry *ace = mFilteredCommands[selIdx];

			if (mpHotKeyControl) {
				mpHotKeyControl->GetAccelerator(accel);

				// Look for a conflicting command.
				for(BoundCommands::iterator it(mBoundCommands.begin()), itEnd(mBoundCommands.end()); it != itEnd; ++it) {
					BoundCommand *obc = *it;

					if (obc->mAccel == accel) {
						VDStringW keyName;
						VDUIGetAcceleratorString(accel, keyName);

						VDStringA msg;
						msg.sprintf("The key %ls is already bound to %hs. Rebind it to %hs?", keyName.c_str(), obc->mpCommand, ace->mpName);

						if (IDOK != MessageBox(mhdlg, msg.c_str(), g_szWarning, MB_OKCANCEL | MB_ICONEXCLAMATION))
							return true;

						mBoundCommands.erase(it);
						obc->Release();
					}
				}

				vdrefptr<BoundCommand> bc(new_nothrow BoundCommand);
				
				if (bc) {
					bc->mpCommand = ace->mpName;
					bc->mCommandId = ace->mId;
					bc->mAccel = accel;

					mBoundCommands.push_back(bc.release());
					RefreshBoundList();
				}
			}
		}

		return true;
	} else if (id == IDC_REMOVE) {
		int selIdx = mListViewBoundCommands.GetSelectedIndex();

		if ((unsigned)selIdx < mBoundCommands.size()) {
			BoundCommand *bc = mBoundCommands[selIdx];

			mBoundCommands.erase(mBoundCommands.begin() + selIdx);

			bc->Release();

			RefreshBoundList();
		}

		return true;
	} else if (id == IDC_RESET) {
		if (IDOK == MessageBox(mhdlg, "Really reset?", g_szWarning, MB_OKCANCEL | MB_ICONEXCLAMATION))
			LoadTable(mBoundCommandsDefault);

		return true;
	}

	return false;
}