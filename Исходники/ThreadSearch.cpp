bool ThreadSearch::GetCursorWord(wxString& sWord)
{
    bool wordFound = false;
    sWord = wxEmptyString;

    // Gets active editor
    cbEditor* ed = Manager::Get()->GetEditorManager()->GetBuiltinActiveEditor();
    if ( ed != NULL )
    {
        cbStyledTextCtrl* control = ed->GetControl();

        sWord = control->GetSelectedText();
        if (sWord != wxEmptyString)
        {
            sWord.Trim(true);
            sWord.Trim(false);

            wxString::size_type pos = sWord.find(wxT('\n'));
            if (pos != wxString::npos)
            {
                sWord.Remove(pos, sWord.length() - pos);
                sWord.Trim(true);
                sWord.Trim(false);
            }

            return !sWord.IsEmpty();
        }

        // Gets word under cursor
        int pos = control->GetCurrentPos();
        int ws  = control->WordStartPosition(pos, true);
        int we  = control->WordEndPosition(pos, true);
        const wxString word = control->GetTextRange(ws, we);
        if (!word.IsEmpty()) // Avoid empty strings
        {
            sWord.Clear();
            while (--ws > 0)
            {
                const wxChar ch = control->GetCharAt(ws);
                if (ch <= _T(' '))
                    continue;
                else if (ch == _T('~'))
                    sWord << _T("~");
                break;
            }
            // m_SearchedWord will be used if 'Find occurrences' ctx menu is clicked
            sWord << word;
            wordFound = true;
        }
    }

    return wordFound;
}