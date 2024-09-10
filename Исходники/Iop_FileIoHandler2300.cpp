void CFileIoHandler2300::SaveState(Framework::CZipArchiveWriter& archive) const
{
	auto registerFile = new CRegisterStateFile(STATE_XML);
	registerFile->SetRegister32(STATE_RESULTPTR0,     m_resultPtr[0]);
	registerFile->SetRegister32(STATE_RESULTPTR1,     m_resultPtr[1]);
	registerFile->SetRegister32(STATE_PENDINGREADCMD, m_pendingReadCommand ? 1 : 0);
	archive.InsertFile(registerFile);
}