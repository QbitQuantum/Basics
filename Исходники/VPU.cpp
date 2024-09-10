void CVPU::SaveState(Framework::CZipArchiveWriter& archive)
{
	std::string path = STATE_PREFIX + boost::lexical_cast<std::string>(m_vpuNumber) + STATE_SUFFIX;
	CRegisterStateFile* registerFile = new CRegisterStateFile(path.c_str());
	registerFile->SetRegister32(STATE_REGS_STAT,		m_STAT);
	registerFile->SetRegister32(STATE_REGS_CODE,		m_CODE);
	registerFile->SetRegister32(STATE_REGS_CYCLE,		m_CYCLE);
	registerFile->SetRegister32(STATE_REGS_NUM,			m_NUM);
	registerFile->SetRegister32(STATE_REGS_MODE,		m_MODE);
	registerFile->SetRegister32(STATE_REGS_MASK,		m_MASK);
	registerFile->SetRegister32(STATE_REGS_MARK,		m_MARK);
	registerFile->SetRegister32(STATE_REGS_ROW0,		m_R[0]);
	registerFile->SetRegister32(STATE_REGS_ROW1,		m_R[1]);
	registerFile->SetRegister32(STATE_REGS_ROW2,		m_R[2]);
	registerFile->SetRegister32(STATE_REGS_ROW3,		m_R[3]);
	registerFile->SetRegister32(STATE_REGS_COL0,		m_C[0]);
	registerFile->SetRegister32(STATE_REGS_COL1,		m_C[1]);
	registerFile->SetRegister32(STATE_REGS_COL2,		m_C[2]);
	registerFile->SetRegister32(STATE_REGS_COL3,		m_C[3]);
	registerFile->SetRegister32(STATE_REGS_ITOP,		m_ITOP);
	registerFile->SetRegister32(STATE_REGS_ITOPS,		m_ITOPS);
	registerFile->SetRegister32(STATE_REGS_READTICK,	m_readTick);
	registerFile->SetRegister32(STATE_REGS_WRITETICK,	m_writeTick);
	archive.InsertFile(registerFile);
}