    BreakpointProbe* DebugDocument::SetBreakPoint(StatementLocation statement, BREAKPOINT_STATE bps)
    {
        ScriptContext* scriptContext = this->utf8SourceInfo->GetScriptContext();

        if (scriptContext == nullptr || scriptContext->IsClosed())
        {
            return nullptr;
        }

        switch (bps)
        {
            default:
                AssertMsg(FALSE, "Bad breakpoint state");
                // Fall thru
            case BREAKPOINT_DISABLED:
            case BREAKPOINT_DELETED:
            {
                BreakpointProbeList* pBreakpointList = this->GetBreakpointList();
                if (pBreakpointList)
                {
                    ArenaAllocator arena(_u("TemporaryBreakpointList"), scriptContext->GetThreadContext()->GetDebugManager()->GetDiagnosticPageAllocator(), Throw::OutOfMemory);
                    BreakpointProbeList* pDeleteList = this->NewBreakpointList(&arena);

                    pBreakpointList->Map([&statement, scriptContext, pDeleteList](int index, BreakpointProbe * breakpointProbe)
                    {
                        if (breakpointProbe->Matches(statement.function, statement.statement.begin))
                        {
                            scriptContext->GetDebugContext()->GetProbeContainer()->RemoveProbe(breakpointProbe);
                            pDeleteList->Add(breakpointProbe);
                        }
                    });

                    pDeleteList->Map([pBreakpointList](int index, BreakpointProbe * breakpointProbe)
                    {
                        pBreakpointList->Remove(breakpointProbe);
                    });
                    pDeleteList->Clear();
                }

                break;
            }
            case BREAKPOINT_ENABLED:
            {
                BreakpointProbe* pProbe = Anew(scriptContext->AllocatorForDiagnostics(), BreakpointProbe, this, statement,
                    scriptContext->GetThreadContext()->GetDebugManager()->GetNextBreakpointId());

                scriptContext->GetDebugContext()->GetProbeContainer()->AddProbe(pProbe);
                BreakpointProbeList* pBreakpointList = this->GetBreakpointList();
                pBreakpointList->Add(pProbe);
                return pProbe;
                break;
            }
        }
        return nullptr;
    }