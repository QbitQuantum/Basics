void CGIF::SaveState(Framework::CZipArchiveWriter& archive)
{
	CRegisterStateFile* registerFile = new CRegisterStateFile(STATE_REGS_XML);
	registerFile->SetRegister32(STATE_REGS_M3P, m_path3Masked ? 1 : 0);
	archive.InsertFile(registerFile);
}