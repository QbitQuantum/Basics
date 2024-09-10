BOOL TSetupSheet::SetData()
{
	if (resId == MAIN_SHEET) {
		if (sv) {
			sv->bufSize			= cfg->bufSize;
			sv->estimateMode	= cfg->estimateMode;
			sv->ignoreErr		= cfg->ignoreErr;
			sv->enableVerify	= cfg->enableVerify;
			sv->enableAcl		= cfg->enableAcl;
			sv->enableStream	= cfg->enableStream;
			sv->speedLevel		= cfg->speedLevel;
			sv->isExtendFilter	= cfg->isExtendFilter;
			sv->enableOwdel		= cfg->enableOwdel;
		}
		SetDlgItemInt(BUFSIZE_EDIT, cfg->bufSize);
		CheckDlgButton(ESTIMATE_CHECK, cfg->estimateMode);
		CheckDlgButton(IGNORE_CHECK, cfg->ignoreErr);
		CheckDlgButton(VERIFY_CHECK, cfg->enableVerify);
		CheckDlgButton(ACL_CHECK, cfg->enableAcl);
		CheckDlgButton(STREAM_CHECK, cfg->enableStream);
		SendDlgItemMessage(SPEED_SLIDER, TBM_SETRANGE, 0, MAKELONG(SPEED_SUSPEND, SPEED_FULL));
		SetSpeedLevelLabel(this, cfg->speedLevel);
		CheckDlgButton(EXTENDFILTER_CHECK, cfg->isExtendFilter);
		CheckDlgButton(OWDEL_CHECK, cfg->enableOwdel);
	}
	else if (resId == IO_SHEET) {
		SetDlgItemInt(MAXTRANS_EDIT, cfg->maxTransSize);
		SetDlgItemInt(MAXOVL_EDIT, cfg->maxOvlNum);
		CheckDlgButton(READOSBUF_CHECK, cfg->isReadOsBuf);
		SetDlgItemInt(NONBUFMINNTFS_EDIT, cfg->nbMinSizeNtfs);
		SetDlgItemInt(NONBUFMINFAT_EDIT, cfg->nbMinSizeFat);
	}
	else if (resId == PHYSDRV_SHEET) {
		SetDlgItemText(DRIVEMAP_EDIT, cfg->driveMap);
		SendDlgItemMessage(NETDRVMODE_COMBO, CB_ADDSTRING, 0, (LPARAM)GetLoadStr(IDS_NETDRV_UNC));
		SendDlgItemMessage(NETDRVMODE_COMBO, CB_ADDSTRING, 0, (LPARAM)GetLoadStr(IDS_NETDRV_SVR));
		SendDlgItemMessage(NETDRVMODE_COMBO, CB_ADDSTRING, 0, (LPARAM)GetLoadStr(IDS_NETDRV_ALL));
		SendDlgItemMessage(NETDRVMODE_COMBO, CB_SETCURSEL, cfg->netDrvMode, 0);
	}
	else if (resId == PARALLEL_SHEET) {
		SetDlgItemInt(MAXRUN_EDIT, cfg->maxRunNum);
		CheckDlgButton(FORCESTART_CHECK, cfg->forceStart);
	}
	else if (resId == COPYOPT_SHEET) {
		CheckDlgButton(SAMEDIR_RENAME_CHECK, cfg->isSameDirRename);
		CheckDlgButton(EMPTYDIR_CHECK, cfg->skipEmptyDir);
		CheckDlgButton(REPARSE_CHECK, cfg->isReparse);
		::EnableWindow(GetDlgItem(REPARSE_CHECK), TRUE);
		CheckDlgButton(MOVEATTR_CHECK, cfg->enableMoveAttr);
		CheckDlgButton(SERIALMOVE_CHECK, cfg->serialMove);
		CheckDlgButton(SERIALVERIFYMOVE_CHECK, cfg->serialVerifyMove);
		SetDlgItemInt(TIMEGRACE_EDIT, cfg->timeDiffGrace);
	}
	else if (resId == DEL_SHEET) {
		CheckDlgButton(NSA_CHECK, cfg->enableNSA);
		CheckDlgButton(DELDIR_CHECK, cfg->delDirWithFilter);
	}
	else if (resId == LOG_SHEET) {
		SetDlgItemInt(HISTORY_EDIT, cfg->maxHistoryNext);
		CheckDlgButton(ERRLOG_CHECK, cfg->isErrLog);
		CheckDlgButton(UTF8LOG_CHECK, cfg->isUtf8Log);
		::EnableWindow(GetDlgItem(UTF8LOG_CHECK), TRUE);
		CheckDlgButton(FILELOG_CHECK, cfg->fileLogMode);
		CheckDlgButton(TIMESTAMP_CHECK, (cfg->fileLogFlags & FastCopy::FILELOG_TIMESTAMP) ?
			TRUE : FALSE);
		CheckDlgButton(FILESIZE_CHECK,  (cfg->fileLogFlags & FastCopy::FILELOG_FILESIZE)  ?
			TRUE : FALSE);
		CheckDlgButton(ACLERRLOG_CHECK, cfg->aclErrLog);
		::EnableWindow(GetDlgItem(ACLERRLOG_CHECK), TRUE);
		CheckDlgButton(STREAMERRLOG_CHECK, cfg->streamErrLog);
		::EnableWindow(GetDlgItem(STREAMERRLOG_CHECK), TRUE);
	}
	else if (resId == MISC_SHEET) {
		CheckDlgButton(EXECCONFIRM_CHECK, cfg->execConfirm);
		CheckDlgButton(TASKBAR_CHECK, cfg->taskbarMode);
		CheckDlgButton(SPAN1_RADIO + cfg->infoSpan, 1);

		if ((cfg->lcid != -1 || GetSystemDefaultLCID() == 0x411)) {
			::ShowWindow(GetDlgItem(LCID_CHECK), SW_SHOW);
			::EnableWindow(GetDlgItem(LCID_CHECK), TRUE);
			CheckDlgButton(LCID_CHECK, cfg->lcid == -1 || cfg->lcid == 0x411 ? FALSE : TRUE);
		}
	}
	return	TRUE;
}