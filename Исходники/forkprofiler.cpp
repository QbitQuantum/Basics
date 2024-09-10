void ForkProfiler::doGraph(
        const s2e::plugins::ExecutionTraceItemHeader &hdr,
        const s2e::plugins::ExecutionTraceFork *te)
{
    ModuleCacheState *mcs = static_cast<ModuleCacheState*>(m_events->getState(m_cache, &ModuleCacheState::factory));

    const ModuleInstance *mi = mcs->getInstance(hdr.pid, te->pc);

    Fork f;
    f.id = hdr.stateId;
    f.pid = hdr.pid;
    f.pc = te->pc;
    if (mi) {
        f.module = mi->Name;
        f.relPc = te->pc - mi->LoadBase + mi->ImageBase;
    }else {
        f.relPc = te->pc;
    }

    for (unsigned i=0; i<te->stateCount; ++i) {
        f.children.push_back(te->children[i]);
    }

    m_forks.push_back(f);
}