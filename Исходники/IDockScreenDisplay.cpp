bool IDockScreenDisplay::EvalString (const CString &sString, bool bPlain, ECodeChainEvents iEvent, CString *retsResult)

//	EvalString
//
//	Evaluates the given string.

	{
	CCodeChainCtx Ctx;
	Ctx.SetEvent(iEvent);
	Ctx.SetScreen(m_pDockScreen);
	Ctx.SaveAndDefineSourceVar(m_pLocation);
	Ctx.SaveAndDefineDataVar(m_pData);

	return Ctx.RunEvalString(sString, bPlain, retsResult);
	}