void Dialog::ReadSettings(RCFile &rcFile)
{
    bool hascaption = false, hasstyle = false, hasfont = false;
    resInfo.SetLanguage(rcFile.GetLanguage());
    bool done = FALSE;
    while (!done && rcFile.IsKeyword())
    {
        switch (rcFile.GetToken()->GetKeyword())
        {
            case Lexer::LANGUAGE:
            {
                rcFile.NextToken();
                int n = rcFile.GetNumber() ;
                rcFile.SkipComma();
                n += rcFile.GetNumber() * 1024;
                resInfo.SetLanguage(n);
            }
                break;
            case Lexer::VERSION:
                rcFile.NextToken();
                resInfo.SetVersion(rcFile.GetNumber());
                break;
            case Lexer::CHARACTERISTICS:
                rcFile.NextToken();
                resInfo.SetCharacteristics(rcFile.GetNumber());
                break;
            case Lexer::STYLE:
                hasstyle = true;
                rcFile.NextToken();
                style = rcFile.GetNumber();
                break;
            case Lexer::EXSTYLE:
                rcFile.NextToken();
                exStyle |= rcFile.GetNumber();
                break;
            case Lexer::MENU:
                rcFile.NextToken();
                menu.ReadRC(rcFile);
                break;
            case Lexer::FONT:
                hasfont = true;
                rcFile.NextToken();
                pointSize = rcFile.GetNumber();
                rcFile.SkipComma();
                font = rcFile.GetString();
                break;
            case Lexer::CAPTION:
                hascaption = true;
                rcFile.NextToken();
                caption = rcFile.GetString();
                break;
            case Lexer::CLASS:
                rcFile.NextToken();
                cls.ReadRC(rcFile, true);
                break;
            case Lexer::HELP:
                rcFile.NextToken();
                if (!extended)
                    throw new std::runtime_error("Need DialogEx");
                helpIndex = rcFile.GetNumber();
                break;
            case Lexer::WEIGHT:
                rcFile.NextToken();
                if (!extended)
                    throw new std::runtime_error("Need DialogEx");
                weight = rcFile.GetNumber();
                break;
            case Lexer::ITALIC:
                rcFile.NextToken();
                if (!extended)
                    throw new std::runtime_error("Need DialogEx");
                italics = rcFile.GetNumber();
                break;
            default:
                done = TRUE;
                break;
        }
        if (!done)
        {
            rcFile.NeedEol();
        }
    }
    if (hascaption)
        style |= WS_CAPTION;
    if (!hasstyle)
        style |= WS_POPUPWINDOW;
    if (hasfont)
        style |= DS_SETFONT;
}