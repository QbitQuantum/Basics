void GRIBUIDialog::OnFileDirChange( wxFileDirPickerEvent &event )
{
    m_pRecordTree->DeleteAllItems();
    delete m_pRecordTree->m_file_id_array;

    m_RecordTree_root_id = m_pRecordTree->AddRoot( _T ( "GRIBs" ) );
    PopulateTreeControl();
    m_pRecordTree->Expand( m_RecordTree_root_id );

    pPlugIn->GetGRIBOverlayFactory()->Reset();

    Refresh();

    m_grib_dir = event.GetPath();
}