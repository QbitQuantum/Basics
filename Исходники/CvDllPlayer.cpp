//------------------------------------------------------------------------------
int CvDllPlayer::GetPlotDanger(ICvPlot1* pPlot) const
{
	CvDllPlot* pDllPlot = static_cast<CvDllPlot*>(pPlot);
	CvPlot& kPlot = (*pDllPlot->GetInstance());
	return m_pPlayer->GetPlotDanger(kPlot);
}