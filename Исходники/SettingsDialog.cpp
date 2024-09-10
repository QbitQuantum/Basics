void SettingsDialog::OnRestoreDefaults( wxCommandEvent& args )
{

    wxMessageDialog dialog( this, wxT( "Are you sure you want to reset these settings to the default values?" ), wxT( "Confirm Default Settings" ), wxYES_NO );
    if ( dialog.ShowModal() == wxID_NO )
    {
        return;
    }

    if ( !m_CurrentSetting )
    {
        return;
    }

    Reflect::ObjectPtr defaultElement = Reflect::SafeCast<Reflect::Object>( Reflect::Registry::GetInstance()->CreateInstance( m_CurrentSetting->m_Clone->GetClass() ) );
    if ( !defaultElement )
    {
        return;
    }

    if ( !defaultElement->Equals( m_CurrentSetting->m_Clone ) )
    {
        defaultElement->CopyTo( m_CurrentSetting->m_Clone );
        m_CurrentSetting->m_Clone->RaiseChanged();
        m_CurrentSetting->m_Canvas->Read();
    }
}