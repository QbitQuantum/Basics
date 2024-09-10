    // removes "/../" bits from the middle of the path
    String simplifyPath (String::CharPointerType p)
    {
       #if JUCE_WINDOWS
        if (CharacterFunctions::indexOf (p, CharPointer_ASCII ("/../")) >= 0
             || CharacterFunctions::indexOf (p, CharPointer_ASCII ("\\..\\")) >= 0)
       #else
        if (CharacterFunctions::indexOf (p, CharPointer_ASCII ("/../")) >= 0)
       #endif
        {
            StringArray toks;

           #if JUCE_WINDOWS
            toks.addTokens (p, "\\/", String::empty);
           #else
            toks.addTokens (p, "/", String::empty);
           #endif

            while (toks[0] == ".")
                toks.remove (0);

            for (int i = 1; i < toks.size(); ++i)
            {
                if (toks[i] == ".." && toks [i - 1] != "..")
                {
                    toks.removeRange (i - 1, 2);
                    i = jmax (0, i - 2);
                }
            }

            return toks.joinIntoString ("/");
        }

        return p;
    }