void CRPGPlayer::ShowSkillMenu()
{
	if (GetCurrentClass() == RPG_CLASS_NONE )
	{
		ShowClassMenu( GetPlayerInfo()->GetTeamIndex());
		return;
	}

	if (GetFreeSkills() < 0)
	{
		ResetAccount();
		gamehelpers->TextMsg(GetIndex(), HUD_PRINTTALK, "[ZPS-RPG] Your skills have been reset because of an error.\n");
	}

	IMenuStyle *style = menus->GetDefaultStyle();
	IBaseMenu *menu = style->CreateMenu(&g_RPGPlugin, myself->GetIdentity());

	menu->SetDefaultTitle(MENU_SKILL_TITLE);

	char skillname[64];
	unsigned int menustyle = ITEMDRAW_DEFAULT;

	for (int i = 0; i < MAX_SKILLS; i++)
	{
		sprintf(skillname, "%s (Level %d)", SkillNames[skills[i].iIndex], skills[i].iLevel);
		menustyle = ITEMDRAW_DEFAULT;

		if ((skills[i].iLevel >= 3) || (GetFreeSkills() == 0))
			menustyle = ITEMDRAW_DISABLED;

		if( i == 3 ) // ULTIMATE
		{
			if ((skills[i].iLevel >= 1) || (GetLevel() < 6) || (GetFreeSkills() == 0))
			{
				menustyle = ITEMDRAW_DISABLED;
			}
		}

		menu->AppendItem(SkillNames[skills[i].iIndex], ItemDrawInfo(skillname, menustyle));
	}
	menu->AppendItem(MENU_ITEM_RESET, ItemDrawInfo("Reset Skills"));
	menu->InsertItem(6, MENU_ITEM_RETURN, ItemDrawInfo(MENU_ITEM_RETURN));
	menu->SetMenuOptionFlags( menu->GetMenuOptionFlags() | MENUFLAG_BUTTON_EXIT );
	menu->Display(this->GetIndex(), MENU_TIME_FOREVER);
}