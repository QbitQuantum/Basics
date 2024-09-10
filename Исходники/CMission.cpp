void CMission::FireCustomEvent (const CString &sEvent)

//	FireCustomEvent
//
//	Fires a custom timed event

{
    SEventHandlerDesc Event;

    if (FindEventHandler(sEvent, &Event))
    {
        CCodeChainCtx Ctx;

        Ctx.SetEvent(eventDoEvent);
        Ctx.SaveAndDefineSourceVar(this);

        ICCItem *pResult = Ctx.Run(Event);
        if (pResult->IsError())
            ReportEventError(sEvent, pResult);
        Ctx.Discard(pResult);
    }
}