//------------------------------------------------------------------------
int CScriptBind_Weapon::IsZoomed(IFunctionHandler *pH)
{
	CWeapon *pWeapon = GetWeapon(pH);
	if (!pWeapon)
		return pH->EndFunction();

	IZoomMode *pZoomMode = pWeapon->GetZoomMode(pWeapon->GetCurrentZoomMode());

	if (pZoomMode)
		return pH->EndFunction(pZoomMode->IsZoomed());

	return pH->EndFunction();
}