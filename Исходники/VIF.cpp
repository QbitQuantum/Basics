void CVIF::SaveState(Framework::CZipArchiveWriter& archive)
{
	//TODO: Save FifoStream states

	{
		CRegisterStateFile* registerFile = new CRegisterStateFile(STATE_REGS_XML);
		registerFile->SetRegister32(STATE_REGS_VPU_STAT, m_VPU_STAT);
		archive.InsertFile(registerFile);
	}

	m_pVPU[0]->SaveState(archive);
	m_pVPU[1]->SaveState(archive);
}