void Coverage::onItem(unsigned traceIndex,
            const s2e::plugins::ExecutionTraceItemHeader &hdr,
            void *item)
{
    if (hdr.type != s2e::plugins::TRACE_TB_START) {
        return;
    }

    const s2e::plugins::ExecutionTraceTb *te =
            (const s2e::plugins::ExecutionTraceTb*) item;

    ModuleCacheState *mcs = static_cast<ModuleCacheState*>(m_events->getState(m_cache, &ModuleCacheState::factory));

    const ModuleInstance *mi = mcs->getInstance(hdr.pid, te->pc);
    if (!mi) {
        std::cerr << "Could not find module for pc=0x" << std::hex << te->pc << std::endl;
        return;
    }

    BasicBlockCoverage *bbcov = NULL;
    BbCoverageMap::iterator it = m_bbCov.find(mi->Name);
    if (it == m_bbCov.end()) {
        //Look for the file containing the bbs.
        std::string bblist = mi->Name + ".bblist";
        std::string path;
        if (m_library->findLibrary(bblist, path)) {
            BasicBlockCoverage *bb = new BasicBlockCoverage(path, mi->Name);
            m_bbCov[mi->Name] = bb;
            bbcov = bb;
        }
    }else {
        bbcov = (*it).second;
    }

    uint64_t relPc = te->pc - mi->LoadBase + mi->ImageBase;

    if (!bbcov) {
        std::cerr << "The block 0x" << std::hex << relPc << " could not be found in any module. " <<
                "Make sure the path to the lists of basic blocks for module " << mi->Name << " is correct." << std::endl;
        return;
    }

    bbcov->addTranslationBlock(hdr.timeStamp, relPc, relPc+te->size-1);
}