void CCdvdman::SaveState(Framework::CZipArchiveWriter& archive)
{
	auto registerFile = new CRegisterStateFile(STATE_FILENAME);
	registerFile->SetRegister32(STATE_CALLBACK_ADDRESS, m_callbackPtr);
	registerFile->SetRegister32(STATE_STATUS, m_status);
	archive.InsertFile(registerFile);
}