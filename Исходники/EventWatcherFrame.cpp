void EventWatcherFrame::addEvents(wxString& s)
{
    // deselect all items so user can cleanly see what is added
    for (int ix = 0; ix < (int)listbox_monitored->GetCount(); ++ix)
    {
        if (listbox_monitored->IsSelected(ix))
            listbox_monitored->Deselect(ix);
    }
    while (true)
    {
        int p = s.Find("\n");
        wxString s2;
        if (p == -1)
            s2 = s.Strip();
        else
        {
            s2 = s.Left(p).Strip(wxString::both);
            s.Remove(0, p);
            s.Trim(false);
        }
        if (!s2.IsEmpty() && listbox_monitored->FindString(s2) == wxNOT_FOUND)
            listbox_monitored->Select(listbox_monitored->Append(s2));
        if (p == -1)
            break;
    }
    updateControls();
}