//------------------------------------------------------------------------
IUIElement* CScriptBind_UIAction::GetElement( const char* sName, int instanceID, bool bSupressWarning )
{
	if (gEnv->IsDedicated())
		return NULL;

	CRY_ASSERT_MESSAGE( gEnv->pFlashUI, "FlashUI extension does not exist!" );
	if ( !gEnv->pFlashUI )
	{
		UIACTION_WARNING( "LUA: FlashUI extension does not exist!" );
		return NULL;
	}

	IUIElement* pElement = gEnv->pFlashUI->GetUIElement( sName );
	if ( pElement && instanceID > 0)
		pElement = pElement->GetInstance( instanceID );

	if (pElement && pElement->IsValid())
		return pElement;

	if (!bSupressWarning)
	{
		UIACTION_WARNING( "LUA: Try to access UIElement %s that is not valid!", sName );
	}
	return NULL;
}