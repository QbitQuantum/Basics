void DockBase::ControlPanel()
{
    if(controlpanel.IsOpen()) return;
    controlpanel.Open(GetTopWindow());
   	RefreshGroups();
    RefreshPanel(); 
}