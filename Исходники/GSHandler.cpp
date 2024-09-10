void CGSHandler::SaveState(Framework::CZipArchiveWriter& archive)
{
	archive.InsertFile(new CMemoryStateFile(STATE_RAM,		m_pRAM,		RAMSIZE));
	archive.InsertFile(new CMemoryStateFile(STATE_REGS,		m_nReg,		sizeof(uint64) * CGSHandler::REGISTER_MAX));
	archive.InsertFile(new CMemoryStateFile(STATE_TRXCTX,	&m_trxCtx,	sizeof(TRXCONTEXT)));

	{
		CRegisterStateFile* registerFile = new CRegisterStateFile(STATE_PRIVREGS);

		registerFile->SetRegister64(STATE_PRIVREGS_PMODE,			m_nPMODE);
		registerFile->SetRegister64(STATE_PRIVREGS_SMODE2,			m_nSMODE2);
		registerFile->SetRegister64(STATE_PRIVREGS_DISPFB1,			m_nDISPFB1.value.q);
		registerFile->SetRegister64(STATE_PRIVREGS_DISPLAY1,		m_nDISPLAY1.value.q);
		registerFile->SetRegister64(STATE_PRIVREGS_DISPFB2,			m_nDISPFB2.value.q);
		registerFile->SetRegister64(STATE_PRIVREGS_DISPLAY2,		m_nDISPLAY2.value.q);
		registerFile->SetRegister64(STATE_PRIVREGS_CSR,				m_nCSR);
		registerFile->SetRegister64(STATE_PRIVREGS_IMR,				m_nIMR);
		registerFile->SetRegister32(STATE_PRIVREGS_CRTMODE,			m_nCrtMode);

		archive.InsertFile(registerFile);
	}
}