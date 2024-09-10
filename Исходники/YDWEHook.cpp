static void InitPatches()
{
	LOGGING_DEBUG(lg) << "Patches initialization started.";


	// Syntax check patch
	LOGGING_TRACE(lg) << "Installing syntax check patch";
	INSTALL_PATCH(syntaxCheck);

	// Auto disable trigger patch
	LOGGING_TRACE(lg) << "Installing auto disable patch";
	INSTALL_PATCH(autoDisable);

	// Enable trigger check patch
	LOGGING_TRACE(lg) << "Installing enable trigger check patch";
	INSTALL_PATCH(enableTriggerCheck1);
	INSTALL_PATCH(enableTriggerCheck2);

	LOGGING_TRACE(lg) << "Installing doodad limit patch";
	INSTALL_PATCH(doodadLimit);

	LOGGING_TRACE(lg) << "Installing unit/item limit patch";
	INSTALL_PATCH(unitItemLimit);

	LOGGING_TRACE(lg) << "Installing editor multi-instance patch";
	INSTALL_PATCH(editorInstanceCheck);

	LOGGING_TRACE(lg) << "Installing attack table patch";

	base::win::pe_reader module(GetModuleHandleW(NULL));
#define WE_ADDRESS(ADDR) ((uintptr_t)(ADDR) - 0x00400000 + (uintptr_t)module.module())
	enum ATTACK_TABLE
	{
		WESTRING_UE_ATTACKTYPE_SPELLS = 0,
		WESTRING_UE_ATTACKTYPE_NORMAL,
		WESTRING_UE_ATTACKTYPE_PIERCE,
		WESTRING_UE_ATTACKTYPE_SIEGE,
		WESTRING_UE_ATTACKTYPE_MAGIC,
		WESTRING_UE_ATTACKTYPE_CHAOS,
		WESTRING_UE_ATTACKTYPE_HERO,
	};
	uintptr_t attack_table_string[] = {
		WE_ADDRESS(0x007DF394),
		WE_ADDRESS(0x007DF374),
		WE_ADDRESS(0x007DF354),
		WE_ADDRESS(0x007DF334),
		WE_ADDRESS(0x007DF314),
		WE_ADDRESS(0x007DF2F4),
		WE_ADDRESS(0x007DF2D8),
	};

	uintptr_t ptr = WE_ADDRESS(0x00784488);
	base::hook::replace_pointer(ptr, attack_table_string[WESTRING_UE_ATTACKTYPE_NORMAL]); ptr += 4;
	base::hook::replace_pointer(ptr, attack_table_string[WESTRING_UE_ATTACKTYPE_PIERCE]); ptr += 4;
	base::hook::replace_pointer(ptr, attack_table_string[WESTRING_UE_ATTACKTYPE_SIEGE]);  ptr += 4;
	base::hook::replace_pointer(ptr, attack_table_string[WESTRING_UE_ATTACKTYPE_MAGIC]);  ptr += 4;
	base::hook::replace_pointer(ptr, attack_table_string[WESTRING_UE_ATTACKTYPE_CHAOS]);  ptr += 4;
	base::hook::replace_pointer(ptr, attack_table_string[WESTRING_UE_ATTACKTYPE_SPELLS]); ptr += 4;
	base::hook::replace_pointer(ptr, attack_table_string[WESTRING_UE_ATTACKTYPE_HERO]);   ptr += 4;

#undef WE_ADDRESS

	LOGGING_DEBUG(lg) << "Patches initialization completed.";
}