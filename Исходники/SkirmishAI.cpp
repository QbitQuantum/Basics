CSkirmishAI::CSkirmishAI(int skirmishAIId, int teamId, const SkirmishAIKey& key,
		const SSkirmishAICallback* callback) :
		skirmishAIId(skirmishAIId),
		key(key),
		callback(callback),
		timerName("AI t:" + IntToString(teamId) +
		          " id:" + IntToString(skirmishAIId) +
		          " " + key.GetShortName() + " " + key.GetVersion()),
		initOk(false),
		dieing(false)
{
	SCOPED_TIMER(timerName.c_str());
	library = IAILibraryManager::GetInstance()->FetchSkirmishAILibrary(key);
	if (library == NULL) {
		dieing = true;
		skirmishAIHandler.SetLocalSkirmishAIDieing(skirmishAIId,
				5 /* = AI failed to init */);
	}
}