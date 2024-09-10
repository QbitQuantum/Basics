void
CBFunctionMenu::SetEmptyMenuItems()
{
	JString name = CBCtagsUser::GetFunctionMenuTitle(itsFileType);
	name.ToLower();

	const JCharacter* map[] =
		{
		"name", name.GetCString()
		};
	const JString menuItems = JGetString(kEmptyMenuID, map, sizeof(map));
	SetMenuItems(menuItems);
}