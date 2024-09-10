void PatchMW2_MusicalTalent()
{
	findSoundAliasHook.initialize(findSoundAliasHookLoc, FindSoundAliasHookFunc);
	findSoundAliasHook.installHook();
}