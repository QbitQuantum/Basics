static const char *
FormatHelpTextCallback ()
{
    
    static char* help_text_ptr = NULL;
    
    if (help_text_ptr)
        return help_text_ptr;
    
    StreamString sstr;
    sstr << "One of the format names (or one-character names) that can be used to show a variable's value:\n";
    for (Format f = eFormatDefault; f < kNumFormats; f = Format(f+1))
    {
        if (f != eFormatDefault)
            sstr.PutChar('\n');
        
        char format_char = FormatManager::GetFormatAsFormatChar(f);
        if (format_char)
            sstr.Printf("'%c' or ", format_char);
        
        sstr.Printf ("\"%s\"", FormatManager::GetFormatAsCString(f));
    }
    
    sstr.Flush();
    
    std::string data = sstr.GetString();
    
    help_text_ptr = new char[data.length()+1];
    
    data.copy(help_text_ptr, data.length());
    
    return help_text_ptr;
}