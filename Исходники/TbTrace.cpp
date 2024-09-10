void TbTrace::printDebugInfo(uint64_t pid, uint64_t pc, unsigned tbSize, bool printListing)
{
    ModuleCacheState *mcs = static_cast<ModuleCacheState*>(m_events->getState(m_cache, &ModuleCacheState::factory));
    const ModuleInstance *mi = mcs->getInstance(pid, pc);
    if (!mi) {
        return;
    }
    uint64_t relPc = pc - mi->LoadBase + mi->ImageBase;
    m_output << std::hex << "(" << mi->Name;
    if (relPc != pc) {
       m_output << " 0x" << relPc;
    }
    m_output << ")";

    m_hasModuleInfo = true;

    std::string file = "?", function="?";
    uint64_t line=0;
    if (m_library->getInfo(mi, pc, file, line, function)) {
        size_t pos = file.find_last_of('/');
	if (pos != std::string::npos) {
            file = file.substr(pos+1);
        }

        m_output << " " << file << std::dec << ":" << line << " in " << function;
        m_hasDebugInfo = true;
    }

    if (PrintDisassembly && printListing) {
        m_output << std::endl;
        printDisassembly(mi->Name, relPc, tbSize);
    }
}