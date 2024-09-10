void DatabaseRegistrationDialog::OnAuthenticationChange(
    wxCommandEvent& WXUNUSED(event))
{
    if (IsShown())
    {
        updateAuthenticationMode();
        updateColors();
    }
}