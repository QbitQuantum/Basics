//------------------------------------------------------------------------------
void CvDllScriptSystemUtility::PushCvPlotInstance(lua_State* L, ICvPlot1* pkPlot)
{
	if(NULL != L && NULL != pkPlot)
	{
		CvDllPlot* pkDllPlot = static_cast<CvDllPlot*>(pkPlot);
		CvLuaPlot::Push(L, pkDllPlot->GetInstance());
	}
	else
	{
		lua_pushnil(L);
	}
}