void Accelerators::Key::ReadRC(RCFile &rcFile)
{
    if (rcFile.IsString())
    {
        std::wstring str = rcFile.GetString();
        if (str[0] == '^')
        {
            if (str.size() != 2)
                throw new std::runtime_error("Invalid key sequence");
            if (str[1] == '^')
                key = '^';
            else
                key = str[1] & 0x1f;
        }
        else
        {
            if (str.size() != 1)
                throw new std::runtime_error("Invalid key sequence");
            key = str[0];
        }
    }
    else
    {
        key = rcFile.GetNumber();
    }
    rcFile.SkipComma();
    id = rcFile.GetNumber();
    rcFile.SkipComma();
    bool done = false;
    while (rcFile.IsKeyword() && !done)
    {
        switch (rcFile.GetToken()->GetKeyword())
        {
            case Lexer::ASCII:
                flags &= ~Virtkey;
                break;
            case Lexer::VIRTKEY:
                flags |= Virtkey;
                break;
            case Lexer::NOINVERT:
                flags |= NoInvert;
                break;
            case Lexer::SHIFT:
                flags |= Shift;
                break;
            case Lexer::CONTROL:
                flags |= Control;
                break;
            case Lexer::ALT:
                flags |= Alt;
                break;
            default:
                done = true;
                break;
        }
        if (!done)
        {
            rcFile.NextToken();
            rcFile.SkipComma();
        }
    }
    rcFile.NeedEol();
}