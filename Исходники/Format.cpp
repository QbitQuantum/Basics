inline bool format::isNumeric(wxString kw) {
    if(kw.Len()==0)
        return false;
    if(kw.GetChar(0)=='&') {
        switch(kw.MakeLower().GetChar(1)) {
            case 'b':
            kw=kw.Mid(2);
            break;
            case 'o':
            kw=kw.Mid(2);
            break;
            case 'h':
            kw=kw.Mid(2);
            break;
        }
    }
    char ch;
    for(int i=0;i<(int)kw.Len();i++) {
        ch = kw.GetChar(i);
        if( ch >= 46 && ch <= 57 ) {
            if (ch==47)
                return false;
        }
        else {
            return false;
        }
    }
    return true;
}