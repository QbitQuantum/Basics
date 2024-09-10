void ResourceInfo::ReadRC(RCFile &rcFile, bool secondary)
{
    bool done = false;
    while (!done)
    {
        switch (rcFile.GetToken()->GetKeyword())
        {
            case Lexer::DISCARDABLE:
                memoryFlags |= Discardable;
                break;
            case Lexer::PURE:
                memoryFlags |= Pure;
                break;
            case Lexer::PRELOAD:
                memoryFlags |= Preload;
                break;
            case Lexer::MOVEABLE:
                memoryFlags |= Moveable;
                break;
            case Lexer::LOADONCALL:
                memoryFlags |= LoadOnCall;
                break;			
            case Lexer::NONDISCARDABLE:
                memoryFlags &= ~Discardable;
                break;
            case Lexer::IMPURE:
                memoryFlags &= ~Pure;
                break;
            case Lexer::FIXED:
                memoryFlags &= ~Moveable;
                break;
            default:
                done = true;
                break;
        }
        if (!done)
            rcFile.NextToken();
    }
    if (secondary)
    {
        done = false;
        language = rcFile.GetLanguage();
        while (!done)
        {
            switch (rcFile.GetToken()->GetKeyword())
            {
                case Lexer::LANGUAGE:
                    rcFile.NextToken();
                    language = rcFile.GetNumber();
                    rcFile.GetNumber();
                    rcFile.NeedEol();
                    break;
                case Lexer::VERSION:
                    rcFile.NextToken();
                    version = rcFile.GetNumber();
                    rcFile.NeedEol();
                    break;
                case Lexer::CHARACTERISTICS:
                    rcFile.NextToken();
                    characteristics = rcFile.GetNumber();
                    rcFile.NeedEol();
                    break;
                default:
                    done = true;
                    break;
            }
        }
    }
}