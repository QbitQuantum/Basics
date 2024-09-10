void WeatherRouting::Render(ocpnDC &dc, PlugIn_ViewPort &vp)
{
    if(!dc.GetDC())
    {
        glPushAttrib(GL_LINE_BIT | GL_ENABLE_BIT | GL_HINT_BIT ); //Save state
        glEnable( GL_LINE_SMOOTH );
        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
        glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
    }

    wxDateTime time = m_ConfigurationDialog.m_GribTimelineTime;
    if(!time.IsValid())
        time = wxDateTime::Now();

    RouteMapOverlay *routemapoverlay = CurrentRouteMap();
    for(int i=0; i<m_lWeatherRoutes->GetItemCount(); i++)
    {
        WeatherRoute *weatherroute =
            reinterpret_cast<WeatherRoute*>(wxUIntToPtr(m_lWeatherRoutes->GetItemData(i)));
        if(weatherroute->routemapoverlay->m_bEndRouteVisible)
            weatherroute->routemapoverlay->Render(time, m_SettingsDialog, dc, vp, true);
    }

    if(routemapoverlay)
        routemapoverlay->Render(time, m_SettingsDialog, dc, vp, false);

    m_ConfigurationBatchDialog.Render(dc, vp);

    if(!dc.GetDC())
        glPopAttrib();
}