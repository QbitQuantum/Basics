void CheckNullPointer::nullPointerByCheckAndDeRef()
{
    // Check if pointer is NULL and then dereference it..

    // used to check if a variable is a pointer.
    // TODO: Use isPointer?
    std::set<unsigned int> pointerVariables;

    for (const Token *tok = _tokenizer->tokens(); tok; tok = tok->next())
    {
        if (Token::Match(tok, "* %var% [;,)=]"))
            pointerVariables.insert(tok->next()->varId());

        else if (Token::simpleMatch(tok, "if ("))
        {
            // TODO: investigate false negatives:
            // - handle "while"?
            // - if there are logical operators
            // - if (x) { } else { ... }

            // If the if-body ends with a unknown macro then bailout
            {
                // goto the end parenthesis
                const Token *endpar = tok->next()->link();
                const Token *endbody = Token::simpleMatch(endpar, ") {") ? endpar->next()->link() : 0;
                if (endbody &&
                    Token::Match(endbody->tokAt(-3), "[;{}] %var% ;") &&
                    isUpper(endbody->tokAt(-2)->str()))
                    continue;
            }

            // vartok : token for the variable
            const Token *vartok = 0;
            if (Token::Match(tok, "if ( ! %var% )|&&"))
                vartok = tok->tokAt(3);
            else if (Token::Match(tok, "if|while ( %var% )|&&"))
                vartok = tok->tokAt(2);
            else
                continue;

            // variable id for pointer
            const unsigned int varid(vartok->varId());
            if (varid == 0)
                continue;

            const unsigned int linenr = vartok->linenr();

            // Check if variable is a pointer. TODO: Use isPointer?
            if (pointerVariables.find(varid) == pointerVariables.end())
                continue;

            // if this is true then it is known that the pointer is null
            bool null = true;

            // start token = inside the if-body
            const Token *tok1 = tok->next()->link()->tokAt(2);

            // indentlevel inside the if-body is 1
            unsigned int indentlevel = 1;

            if (Token::Match(tok, "if|while ( %var% )|&&"))
            {
                // pointer might be null
                null = false;

                // start token = first token after the if/while body
                tok1 = tok1->previous()->link();
                tok1 = tok1 ? tok1->next() : NULL;
                if (!tok1)
                    continue;

                // indentlevel at the base level is 0
                indentlevel = 0;
            }

            // Name of the pointer
            const std::string &pointerName = vartok->str();

            // Count { and } for tok2
            for (const Token *tok2 = tok1; tok2; tok2 = tok2->next())
            {
                if (tok2->str() == "{")
                    ++indentlevel;
                else if (tok2->str() == "}")
                {
                    if (indentlevel == 0)
                        break;
                    --indentlevel;

                    if (null && indentlevel == 0)
                    {
                        // skip all "else" blocks because they are not executed in this execution path
                        while (Token::simpleMatch(tok2, "} else {"))
                            tok2 = tok2->tokAt(2)->link();
                        null = false;
                    }
                }

                if (Token::Match(tok2, "goto|return|continue|break|throw|if|switch"))
                {
                    if (Token::Match(tok2, "return * %varid%", varid))
                        nullPointerError(tok2, tok->strAt(3), linenr);
                    break;
                }

                // parameters to sizeof are not dereferenced
                if (Token::Match(tok2, "decltype|sizeof ("))
                {
                    tok2 = tok2->next()->link();
                    continue;
                }

                // calling unknown function (abort/init)..
                if (Token::simpleMatch(tok2, ") ;") &&
                    (Token::Match(tok2->link()->tokAt(-2), "[;{}] %var% (") ||
                     Token::Match(tok2->link()->tokAt(-5), "[;{}] ( * %var% ) (")))
                {
                    break;
                }

                if (tok2->varId() == varid)
                {
                    // unknown: this is set to true by isPointerDeRef if
                    //          the function fails to determine if there
                    //          is a dereference or not
                    bool unknown = false;

                    if (Token::Match(tok2->previous(), "[;{}=] %var% = 0 ;"))
                        ;

                    else if (CheckNullPointer::isPointerDeRef(tok2, unknown))
                        nullPointerError(tok2, pointerName, linenr);

                    else
                        break;
                }
            }
        }
    }
}