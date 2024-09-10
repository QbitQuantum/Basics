bool SIM_PLOT_PANEL::DeleteTrace( const wxString& aName )
{
    auto it = m_traces.find( aName );

    if( it != m_traces.end() )
    {
        m_traces.erase( it );
        TRACE* trace = it->second;

        if( CURSOR* cursor = trace->GetCursor() )
            DelLayer( cursor, true );

        DelLayer( trace, true, true );
        ResetScales();

        return true;
    }

    return false;
}