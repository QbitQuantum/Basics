    // Select the currently actively field.
    void HighlightCurrentField()
    {
        m_text->SetFocus();

        const CharRange range = GetFieldRange(m_currentField);

        m_text->SetSelection(range.from, range.to);
    }