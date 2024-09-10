void wxDialogBase::OnCloseWindow(wxCloseEvent& WXUNUSED(event))
{
    // We'll send a Cancel message by default, which may close the dialog.
    // Check for looping if the Cancel event handler calls Close().

    // Note that if a cancel button and handler aren't present in the dialog,
    // nothing will happen when you close the dialog via the window manager, or
    // via Close(). We wouldn't want to destroy the dialog by default, since
    // the dialog may have been created on the stack. However, this does mean
    // that calling dialog->Close() won't delete the dialog unless the handler
    // for wxID_CANCEL does so. So use Destroy() if you want to be sure to
    // destroy the dialog. The default OnCancel (above) simply ends a modal
    // dialog, and hides a modeless dialog.

    int idCancel = GetEscapeId();
    if ( idCancel == wxID_NONE )
        return;
    if ( idCancel == wxID_ANY )
        idCancel = wxID_CANCEL;

    // VZ: this is horrible and MT-unsafe. Can't we reuse some of these global
    //     lists here? don't dare to change it now, but should be done later!
    static wxList closing;

    if ( closing.Member(this) )
        return;

    closing.Append(this);

    wxCommandEvent cancelEvent(wxEVT_COMMAND_BUTTON_CLICKED, idCancel);
    cancelEvent.SetEventObject( this );
    GetEventHandler()->ProcessEvent(cancelEvent); // This may close the dialog

    closing.DeleteObject(this);
}