void FOOTPRINT_WIZARD_FRAME::ReloadFootprint()
{
    FOOTPRINT_WIZARD* footprintWizard = GetMyWizard();

    if( !footprintWizard )
        return;

    SetCurItem( NULL );
    // Delete the current footprint
    GetBoard()->m_Modules.DeleteAll();

    // Creates the module
    MODULE* module = footprintWizard->GetModule();

    if( module )
    {
        //  Add the object to board
        module->SetParent( (EDA_ITEM*) GetBoard() );
        GetBoard()->m_Modules.Append( module );
        module->SetPosition( wxPoint( 0, 0 ) );
    }
    else
    {
        DBG(printf( "footprintWizard->GetModule() returns NULL\n" );)
    }

    m_canvas->Refresh();
}