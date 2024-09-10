void FOOTPRINT_EDIT_FRAME::restoreLastFootprint()
{
    wxString pretty = Prj().GetRString( PROJECT::PCB_FOOTPRINT );

    if( !!pretty )
    {
        PCB_IO  pcb_io;
        MODULE* module = NULL;

        try
        {
            module = (MODULE*) pcb_io.Parse( pretty );
        }
        catch( const PARSE_ERROR& pe )
        {
            // unlikely to be a problem, since we produced the pretty string.
            wxLogError( wxT( "PARSE_ERROR" ) );
        }
        catch( const IO_ERROR& ioe )
        {
            // unlikely to be a problem, since we produced the pretty string.
            wxLogError( wxT( "IO_ERROR" ) );
        }

        if( module )
        {
            // assumes BOARD is empty.
            wxASSERT( GetBoard()->m_Modules == NULL );

            // no idea, its monkey see monkey do.  I would encapsulate this into
            // a member function if its actually necessary.
            module->SetParent( GetBoard() );
            module->SetLink( 0 );

            GetBoard()->Add( module );
        }
    }
}