//--------------------------------------------------------------------------------------------------
/// 
//--------------------------------------------------------------------------------------------------
void RicTilePlotWindowsFeature::onActionTriggered(bool isChecked)
{
    RiuMainPlotWindow* mainPlotWindow = RiaApplication::instance()->mainPlotWindow();
    if (mainPlotWindow)
    {
        mainPlotWindow->tileWindows();
    }
}