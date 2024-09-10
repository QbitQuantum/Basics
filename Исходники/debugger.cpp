void ExecutionDebugger::onItem(unsigned traceIndex,
            const s2e::plugins::ExecutionTraceItemHeader &hdr,
            void *item)
{
    if (hdr.type != TRACE_TB_START) {
        return;
    }

    ExecutionTraceTb *tb = (ExecutionTraceTb*) item;

    m_os << " pc=0x" << std::hex << tb->pc <<
            " tpc=0x" << std::hex <<  tb->targetPc ;

    ModuleCacheState *mcs = static_cast<ModuleCacheState*>(m_events->getState(m_cache, &ModuleCacheState::factory));
    const ModuleInstance *mi = mcs->getInstance(hdr.pid, tb->pc);
    std::string dbg;
    if (m_library->print(mi, tb->pc, dbg, true, true, true)) {
        m_os << " - " << dbg;
    }

     m_os << '\n';

}