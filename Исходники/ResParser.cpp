bool CResParser::Parse(CResNode* pRootNode, const wchar_t* pszContent, const wchar_t* pszFileName)
{
    // Initialize tokenizer
    CCppTokenizer::ParseString(pszContent, pszFileName);

    // Parse it
    CVector<CResNode*>	ScopeStack;
    ScopeStack.Push(pRootNode);
    while (CurrentToken()!=tokenEOF)
    {
        // Ending a Node
        if (CurrentToken()==tokenCloseBrace)
        {
            // Skip it
            NextToken();

            if (CurrentToken()==tokenSemiColon)
            {
                NextToken();
            }

            // Pop scope stack...
            ScopeStack.Pop();

            // Check have something to pop!
            if (ScopeStack.IsEmpty())
            {
                Unexpected();
                return false;
            }

            continue;
        }

        // Generate definition?
        if (CurrentToken()==tokenGen)
        {
            while (true)
            {
                // Yes, find the end of the generator block (or, a new target definition)
                const wchar_t* pszEndScan[]= {L"#endgen", L"#target"};
                if (!ScanForward(pszEndScan, _countof(pszEndScan)))
                    return false;


                NextToken();

                if (CurrentToken()!=tokenTarget)
                    break;

            }

            Skip(tokenEndGen);
            continue;
        }

        // Get name of element - expect string literal or identifier...
        CUniString strName=GetStringLiteral();
        if (CurrentToken()!=tokenStringLiteral && CurrentToken()!=tokenIdentifier)
        {
            Unexpected(L"when parsing Node or value name ");
            return false;
        }
        NextToken();

        if (CurrentToken()==tokenPointer)
        {
            // Get the link to name
            NextToken();
            CUniString strLinkTo=GetStringLiteral();
            if (!Skip(tokenStringLiteral))
                return false;
            if (strLinkTo.IsEmpty())
            {
                SetError(L"Missing link reference name");
                return false;
            }

            // Start a new Node
            CResNode* pNewSection;
            pNewSection=ScopeStack.Top()->CreateNewNode(strName);

            pNewSection->SetLink(strLinkTo);

            Skip(tokenSemiColon);
            continue;
        }

        // Parse an optional assign before open brace...
        bool bHaveAssign=CurrentToken()==tokenEquals;
        if (bHaveAssign)
        {
            NextToken();
        }

        // Starting a Node?
        if (CurrentToken()==tokenOpenBrace)
        {
            // Skip it
            NextToken();

            // Start a new Node
            ScopeStack.Push(ScopeStack.Top()->CreateNewNode(strName));
            continue;
        }

        // Expect assignment
        if (!bHaveAssign)
        {
            if (!Skip(tokenEquals))
                return false;
            NextToken();
        }

        // Parse value...
        CUniString strValue;
        if (!ParseValue(strValue))
            return false;

        // Skip semicolon
        if (!Skip(tokenSemiColon))
            return false;

        // Store value...
        ScopeStack.Top()->SetValue(strName, strValue);

    }

    // Check nothing left on stack except the root node
    if (ScopeStack.GetSize()!=1)
    {
        SetError(L"Missing closing brace");
        return false;
    }

    // Done!
    return true;
}