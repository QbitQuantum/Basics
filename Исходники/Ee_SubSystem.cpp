void CSubSystem::SaveState(Framework::CZipArchiveWriter& archive)
{
    archive.InsertFile(new CMemoryStateFile(STATE_EE,			&m_EE.m_State,	sizeof(MIPSSTATE)));
    archive.InsertFile(new CMemoryStateFile(STATE_VU0,			&m_VU0.m_State,	sizeof(MIPSSTATE)));
    archive.InsertFile(new CMemoryStateFile(STATE_VU1,			&m_VU1.m_State,	sizeof(MIPSSTATE)));
    archive.InsertFile(new CMemoryStateFile(STATE_RAM,			m_ram,			PS2::EE_RAM_SIZE));
    archive.InsertFile(new CMemoryStateFile(STATE_SPR,			m_spr,			PS2::EE_SPR_SIZE));
    archive.InsertFile(new CMemoryStateFile(STATE_VUMEM0,		m_vuMem0,		PS2::VUMEM0SIZE));
    archive.InsertFile(new CMemoryStateFile(STATE_MICROMEM0,	m_microMem0,	PS2::MICROMEM0SIZE));
    archive.InsertFile(new CMemoryStateFile(STATE_VUMEM1,		m_vuMem1,		PS2::VUMEM1SIZE));
    archive.InsertFile(new CMemoryStateFile(STATE_MICROMEM1,	m_microMem1,	PS2::MICROMEM1SIZE));

    m_dmac.SaveState(archive);
    m_intc.SaveState(archive);
    m_sif.SaveState(archive);
    m_vpu0->SaveState(archive);
    m_vpu1->SaveState(archive);
    m_timer.SaveState(archive);
}