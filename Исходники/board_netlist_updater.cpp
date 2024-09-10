MODULE* BOARD_NETLIST_UPDATER::replaceComponent( NETLIST& aNetlist, MODULE* aPcbComponent, COMPONENT* aNewComponent )
{
    wxString msg;

    if( !m_replaceFootprints )
        return NULL;

    // Test if the footprint has not changed
    if( aNewComponent->GetFPID().empty() || aPcbComponent->GetFPID() == aNewComponent->GetFPID() )
        return NULL;

    if( aNewComponent->GetModule() != NULL )
    {
        msg.Printf( _( "Change component %s footprint from %s to %s.\n"),
                    GetChars( aPcbComponent->GetReference() ),
                    GetChars( aPcbComponent->GetFPID().Format() ),
                    GetChars( aNewComponent->GetFPID().Format() ) );

        m_reporter->Report( msg, REPORTER::RPT_ACTION );

        msg.Printf( _( "Replacing component \"%s:%s\" footprint \"%s\" with "
                       "\"%s\".\n" ),
                    GetChars( aPcbComponent->GetReference() ),
                    GetChars( aPcbComponent->GetPath() ),
                    GetChars( aPcbComponent->GetFPID().Format() ),
                    GetChars( aNewComponent->GetFPID().Format() ) );

        m_reporter->Report( msg, REPORTER::RPT_INFO );

        if( !m_isDryRun )
        {
            wxASSERT( aPcbComponent != NULL );

            MODULE* newFootprint = new MODULE( *aNewComponent->GetModule() );
            newFootprint->SetParent( m_board );

            if( aNetlist.IsFindByTimeStamp() )
                newFootprint->SetReference( aPcbComponent->GetReference() );
            else
                newFootprint->SetPath( aPcbComponent->GetPath() );

            aPcbComponent->CopyNetlistSettings( newFootprint, false );
            m_commit.Remove( aPcbComponent );
            m_commit.Add( newFootprint );

            return newFootprint;
        }
    }
    else
    {
        msg.Printf( _( "Cannot change component %s footprint due to missing "
                       "footprint %s.\n" ),
                    GetChars( aPcbComponent->GetReference() ),
                    GetChars( aNewComponent->GetFPID().Format() ) );

        m_reporter->Report( msg, REPORTER::RPT_ERROR );

        msg.Printf( _( "Cannot replace component \"%s:%s\" due to missing "
                       "footprint \"%s\".\n" ),
                    GetChars( aPcbComponent->GetReference() ),
                    GetChars( aPcbComponent->GetPath() ),
                    GetChars( aNewComponent->GetFPID().Format() ) );

        m_reporter->Report( msg, REPORTER::RPT_INFO );

        ++m_errorCount;
    }

    return NULL;
}