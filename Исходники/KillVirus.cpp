void CKillVirus::OnHookCode(uint64_t address, uint32_t size)
{
	BOOL detected = FALSE;
	m_InsCount++;

	if (m_InsCount > g_maxInsCount)
	{
		m_emul->StopEmulator();
		return;
	}

	// check for RETN instruction
	unsigned char opCode;

	// check instruction size
	if (size != 1) return;
	// check instruction code
	if (FAILED(m_emul->ReadMemory((DWORD_PTR)address, &opCode, size))) return;
	if (opCode != 0xc3) return;

	// find VA of new state
	uint32_t salityEp = 0;
	if (FAILED(m_emul->ReadRegister(UC_X86_REG_ESP, (DWORD_PTR *)&salityEp)) ||
		FAILED(m_emul->ReadMemory((DWORD_PTR)salityEp, &salityEp, sizeof(salityEp)))
		)
		return;

	BYTE * sality = new BYTE[0x100];
	if (sality == NULL) return;

	// check sality code
	if (FAILED(m_emul->ReadMemory((DWORD_PTR)salityEp, sality, 0x100)) ||
		!VerifySignature(sality, 0x100)
		)
	{
		delete[] sality;
		return;
	}

	// virus FOUND!
	m_scanResult.scanResult = VirusDetected;

	// find original code
	if (SUCCEEDED(m_emul->ReadMemory((DWORD_PTR)salityEp + 0x1F, &m_OepAddr, sizeof(DWORD))))
	{
		m_OepAddr = salityEp + 5 - m_OepAddr;
		unsigned char bRestoreOepCode = 0;

		if (SUCCEEDED(m_emul->ReadMemory((DWORD_PTR)salityEp + 0x1773, &bRestoreOepCode, sizeof(bRestoreOepCode))) &&
			bRestoreOepCode &&
			SUCCEEDED(m_emul->ReadMemory((DWORD_PTR)salityEp + 0x1774, &m_dwOepCodeSize, sizeof(m_dwOepCodeSize))))
		{
			if (m_dwOepCodeSize > 1)
			{
				// original code Found!
				m_OepCode = new BYTE[m_dwOepCodeSize];
				if (m_OepCode)
				{
					m_salityEp = salityEp;
					if (FAILED(m_emul->ReadMemory((DWORD_PTR)salityEp + 0x1778, m_OepCode, m_dwOepCodeSize)))
					{
						delete[] m_OepCode;
						m_OepCode = NULL;
						m_dwOepCodeSize = 0;
					}
				}
			}
		}
	}
	m_emul->StopEmulator();
	delete[] sality;
}