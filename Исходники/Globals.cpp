AnsiString Global::Bezogonkow(AnsiString str, bool _)
{ // wyciêcie liter z ogonkami, bo OpenGL nie umie wyœwietliæ
    for (int i = 1; i <= str.Length(); ++i)
        if (str[i] & 0x80)
            str[i] = bezogonkowo[str[i] & 0x7F];
        else if (str[i] < ' ') // znaki steruj¹ce nie s¹ obs³ugiwane
            str[i] = ' ';
        else if (_)
            if (str[i] == '_') // nazwy stacji nie mog¹ zawieraæ spacji
                str[i] = ' '; // wiêc trzeba wyœwietlaæ inaczej
    return str;
}