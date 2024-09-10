void wxFrameBase::OnMenuOpen(wxMenuEvent& event)
{
#if wxUSE_IDLEMENUUPDATES
    wxUnusedVar(event);
#else // !wxUSE_IDLEMENUUPDATES
    // as we didn't update the menus from idle time, do it now
    DoMenuUpdates(event.GetMenu());
#endif // wxUSE_IDLEMENUUPDATES/!wxUSE_IDLEMENUUPDATES
}