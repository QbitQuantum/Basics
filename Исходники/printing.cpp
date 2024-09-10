static int
get_text_height(wxDC &dc, const wxString &text) {
    int width, height;
    dc.GetTextExtent(text, &width, &height);
    
    // GetTextExtent only takes into account one line, so just count the \n's
    // and multiply the height by that.
    int text_len = text.length();
    int times = 1;
    for (int i = 0; i < text_len; ++i) {
        if (text[i] == wxT('\n'))
            ++times;
    }
    return times * height;
}