void CVif1::SaveState(Framework::CZipArchiveWriter& archive)
{
    CVif::SaveState(archive);

    auto path = string_format(STATE_PATH_FORMAT, m_number);
    CRegisterStateFile* registerFile = new CRegisterStateFile(path.c_str());
    registerFile->SetRegister32(STATE_REGS_BASE,	m_BASE);
    registerFile->SetRegister32(STATE_REGS_TOP,		m_TOP);
    registerFile->SetRegister32(STATE_REGS_TOPS,	m_TOPS);
    registerFile->SetRegister32(STATE_REGS_OFST,	m_OFST);
    archive.InsertFile(registerFile);
}