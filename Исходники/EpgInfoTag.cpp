void CEpgInfoTag::SetPlot(const CStdString &strPlot)
{

  CStdString strPlotClean = (m_strPlotOutline.length() > 0 && strPlot.Left(m_strPlotOutline.length()).Equals(m_strPlotOutline)) ?
    strPlot.Right(strPlot.length() - m_strPlotOutline.length()) :
    strPlot;

  if (m_strPlot != strPlotClean)
  {
    m_strPlot = strPlotClean;
    m_bChanged = true;
    UpdatePath();
  }
}