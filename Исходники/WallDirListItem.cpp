void CWallDirListItem::UpdateDirState()
{
	if (m_mux.Lock()) {
		m_uDirState = 0;
		if (DRIVE_FIXED == RealDriveType(PathGetDriveNumber(GetItemDirPath()), 0))
			m_uDirState |= DIRSTATE_FIXEDDRIVE;
		m_pIni->WriteUInt(_T("DirState"), GetItemDirPath(), m_uDirState);

		m_mux.Unlock();
	}
}