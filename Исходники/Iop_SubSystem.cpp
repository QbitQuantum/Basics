void CSubSystem::SaveState(Framework::CZipArchiveWriter& archive)
{
    archive.InsertFile(new CMemoryStateFile(STATE_CPU,		&m_cpu.m_State, sizeof(MIPSSTATE)));
    archive.InsertFile(new CMemoryStateFile(STATE_RAM,		m_ram,			IOP_RAM_SIZE));
    archive.InsertFile(new CMemoryStateFile(STATE_SCRATCH,	m_scratchPad,	IOP_SCRATCH_SIZE));
    archive.InsertFile(new CMemoryStateFile(STATE_SPURAM,	m_spuRam,		SPU_RAM_SIZE));
    m_intc.SaveState(archive);
    m_counters.SaveState(archive);
    m_spuCore0.SaveState(archive);
    m_spuCore1.SaveState(archive);
    m_bios->SaveState(archive);
}