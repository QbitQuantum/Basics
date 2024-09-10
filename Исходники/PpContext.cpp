TPpContext::TPpContext(TParseContext& pc) : 
    preamble(0), strings(0), parseContext(pc), inComment(false)
{
    InitAtomTable();
    InitScanner();

    ifdepth = 0;
    for (elsetracker = 0; elsetracker < maxIfNesting; elsetracker++)
        elseSeen[elsetracker] = false;
    elsetracker = 0;
    
    // The following identifies all legal characters in GLSL:

    //for (int c = 0; c < 256; ++c)
    //    languageCharacters[c] = false;
    //for (int c = 'a'; c <= 'z'; ++c)
    //    languageCharacters[c] = true;
    //for (int c = 'A'; c <= 'Z'; ++c)
    //    languageCharacters[c] = true;
    //languageCharacters['_'] = true;
    //for (int c = '0'; c <= '9'; ++c)
    //    languageCharacters[c] = true;
    //languageCharacters['.'] = true;
    //languageCharacters['+'] = true;
    //languageCharacters['-'] = true;
    //languageCharacters['/'] = true;
    //languageCharacters['*'] = true;
    //languageCharacters['%'] = true;
    //languageCharacters['<'] = true;
    //languageCharacters['>'] = true;
    //languageCharacters['['] = true;
    //languageCharacters[']'] = true;
    //languageCharacters['('] = true;
    //languageCharacters[')'] = true;
    //languageCharacters['{'] = true;
    //languageCharacters['}'] = true;
    //languageCharacters['^'] = true;
    //languageCharacters['|'] = true;
    //languageCharacters['&'] = true;
    //languageCharacters['~'] = true;
    //languageCharacters['='] = true;
    //languageCharacters['!'] = true;
    //languageCharacters[':'] = true;
    //languageCharacters[';'] = true;
    //languageCharacters[','] = true;
    //languageCharacters['?'] = true;
    //languageCharacters['#'] = true;

    //// white space
    //languageCharacters[' '] = true;
    //for (int c = 9; c <= 13; ++c)
    //    languageCharacters[c] = true;
}