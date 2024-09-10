void CVPU1::SaveState(Framework::CZipArchiveWriter& archive)
{
	CVPU::SaveState(archive);

	std::string path = STATE_PREFIX + boost::lexical_cast<std::string>(m_vpuNumber) + STATE_SUFFIX;
	CRegisterStateFile* registerFile = new CRegisterStateFile(path.c_str());
	registerFile->SetRegister32(STATE_REGS_BASE,	m_BASE);
	registerFile->SetRegister32(STATE_REGS_TOP,		m_TOP);
	registerFile->SetRegister32(STATE_REGS_TOPS,	m_TOPS);
	registerFile->SetRegister32(STATE_REGS_OFST,	m_OFST);
	archive.InsertFile(registerFile);
}