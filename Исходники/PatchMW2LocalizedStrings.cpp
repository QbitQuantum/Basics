void PatchMW2_LocalizedStrings()
{
	_localizedStrings.set_empty_key("");
 
	loadLocalizeHook.initialize(loadLocalizeHookLoc, SEH_GetLocalizedString);
	loadLocalizeHook.installHook();
 
	call(0x4CE5EE, SetString, PATCH_CALL); //instead of calling CStringEdPackage::SetString in CStringEdPackage::ParseLine we call our SetString
	call(0x41D860, SELoadLanguageHookStub, PATCH_JUMP); //instead of the game loading str files according to loc_language we load them according to loc_modlanguage
 
	Dvar_RegisterEnum("loc_modLanguage", ModLanguageEnum, 0, DVAR_FLAG_SAVED, "Preferred language for custom localized strings.");
}