int NFCSceneAOIModule::EnterSceneCondition(const NFGUID & self, const int nSceneID, const int nGroupID, const int nType, const NFDataList & argList)
{
	std::vector<SCENE_EVENT_FUNCTOR_PTR>::iterator it = mtEnterSceneConditionCallback.begin();
	for (; it != mtEnterSceneConditionCallback.end(); it++)
	{
		SCENE_EVENT_FUNCTOR_PTR& pFunPtr = *it;
		SCENE_EVENT_FUNCTOR* pFunc = pFunPtr.get();
		const int nReason = pFunc->operator()(self, nSceneID, nGroupID, nType, argList);
		if (nReason != 0)
		{
			return nReason;
		}
	}
	return 0;
}