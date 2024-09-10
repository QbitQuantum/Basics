BOOL doScriptItemizeOpenType(struct scriptItemizeParams *p)
{
	HRESULT hr;

	hr = ScriptItemizeOpenType(p->pwcInChars, p->cInChars,
		p->cMaxItems, p->psControl, p->psState,
		p->pItems, p->pScriptTags, p->pcItems);
	if (hr == S_OK)
		return TRUE;
	if (hr != E_OUTOFMEMORY)
		die("error calling ScriptItemizeOpenType()", hr);
	return FALSE;
}