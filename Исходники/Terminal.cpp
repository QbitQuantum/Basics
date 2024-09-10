bool CTerminal::PrintText(const CSmallString& text,
                                       int column_width,const char* p_leading)
{
    if( FOut == NULL ) return(false);

    if( column_width <= 0 ) column_width = NColumns;

    const char* white_list = " \t\n/";

    int indent = 0;
    int lpos = indent;
    int len  = text.GetLength();
    int maxlen = column_width;

    if( p_leading != NULL ) Printf("%s",p_leading);

    for(int i=0; i < len; i++) {
        // find next non-white character
        int wc  = text.Scan(white_list,i+1);
        if( wc < 0 ) wc = len;

        if( (wc - i + lpos >= maxlen)  ) {
            Printf("\n");
            if( p_leading != NULL ) Printf("%s",p_leading);
            lpos = indent;
            if( isspace(text[i]) == 0 ) Printf("%c",text[i]);
        } else {
            if( text[i] != '\n' ) {
                Printf("%c",text[i]);
            } else {
                Printf("%c",' ');
            }
            lpos++;
        }
    }
    Printf("\n");

    return(true);
}