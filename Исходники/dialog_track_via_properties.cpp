bool DIALOG_TRACK_VIA_PROPERTIES::confirmPadChange( const std::vector<D_PAD*>& changingPads )
{
    wxString msg;

    if( changingPads.size() == 1 )
    {
        D_PAD* pad = *changingPads.begin();
        msg.Printf( _( "This will change the net assigned to %s pad %s to %s.\n"
                       "Do you wish to continue?" ),
                    pad->GetParent()->GetReference(),
                    pad->GetName(),
                    m_netSelector->GetValue() );
    }
    else if( changingPads.size() == 2 )
    {
        D_PAD* pad1 = *changingPads.begin();
        D_PAD* pad2 = *( ++changingPads.begin() );
        msg.Printf( _( "This will change the net assigned to %s pad %s and %s pad %s to %s.\n"
                       "Do you wish to continue?" ),
                    pad1->GetParent()->GetReference(),
                    pad1->GetName(),
                    pad2->GetParent()->GetReference(),
                    pad2->GetName(),
                    m_netSelector->GetValue() );
    }
    else
    {
        msg.Printf( _( "This will change the net assigned to %d connected pads to %s.\n"
                       "Do you wish to continue?" ),
                    changingPads.size(),
                    m_netSelector->GetValue() );
    }

    KIDIALOG dlg( this, msg, _( "Confirmation" ), wxOK | wxCANCEL | wxICON_WARNING );
    dlg.SetOKLabel( _( "Continue" ) );
    dlg.DoNotShowCheckbox( __FILE__, __LINE__ );

    return dlg.ShowModal() == wxID_OK;
}