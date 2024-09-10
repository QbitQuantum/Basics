void CCdvdfsv::SaveState(Framework::CZipArchiveWriter& archive)
{
	auto registerFile = new CRegisterStateFile(STATE_FILENAME);

	registerFile->SetRegister32(STATE_PENDINGCOMMAND, m_pendingCommand);
	registerFile->SetRegister32(STATE_PENDINGREADSECTOR, m_pendingReadSector);
	registerFile->SetRegister32(STATE_PENDINGREADCOUNT, m_pendingReadCount);
	registerFile->SetRegister32(STATE_PENDINGREADADDR, m_pendingReadAddr);

	registerFile->SetRegister32(STATE_STREAMING, m_streaming);
	registerFile->SetRegister32(STATE_STREAMPOS, m_streamPos);
	registerFile->SetRegister32(STATE_STREAMBUFFERSIZE, m_streamBufferSize);

	archive.InsertFile(registerFile);
}