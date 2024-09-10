void DisassemblyTextCtrl::OnGPM(wxMouseEvent& event)
{
    if(platform::gtk == false) // only if GPM is not already implemented by the OS
    {
        int pos = PositionFromPoint(wxPoint(event.GetX(), event.GetY()));

        if(pos == wxSCI_INVALID_POSITION)
            return;

        int start = GetSelectionStart();
        int end = GetSelectionEnd();

        const wxString s = GetSelectedText();

        if(pos < GetCurrentPos())
        {
            start += s.length();
            end += s.length();
        }

        InsertText(pos, s);
        SetSelectionVoid(start, end);
    }
} // end of OnGPM