bool MacroExpander::collectMacroArgs(const Macro &macro,
                                     const Token &identifier,
                                     std::vector<MacroArg> *args)
{
    Token token;
    getToken(&token);
    assert(token.type == '(');

    args->push_back(MacroArg());
    for (int openParens = 1; openParens != 0; )
    {
        getToken(&token);

        if (token.type == Token::LAST)
        {
            mDiagnostics->report(Diagnostics::PP_MACRO_UNTERMINATED_INVOCATION,
                                 identifier.location, identifier.text);
            // Do not lose EOF token.
            ungetToken(token);
            return false;
        }

        bool isArg = false; // True if token is part of the current argument.
        switch (token.type)
        {
          case '(':
            ++openParens;
            isArg = true;
            break;
          case ')':
            --openParens;
            isArg = openParens != 0;
            break;
          case ',':
            // The individual arguments are separated by comma tokens, but
            // the comma tokens between matching inner parentheses do not
            // seperate arguments.
            if (openParens == 1)
                args->push_back(MacroArg());
            isArg = openParens != 1;
            break;
          default:
            isArg = true;
            break;
        }
        if (isArg)
        {
            MacroArg &arg = args->back();
            // Initial whitespace is not part of the argument.
            if (arg.empty())
                token.setHasLeadingSpace(false);
            arg.push_back(token);
        }
    }

    const Macro::Parameters &params = macro.parameters;
    // If there is only one empty argument, it is equivalent to no argument.
    if (params.empty() && (args->size() == 1) && args->front().empty())
    {
        args->clear();
    }
    // Validate the number of arguments.
    if (args->size() != params.size())
    {
        Diagnostics::ID id = args->size() < macro.parameters.size() ?
            Diagnostics::PP_MACRO_TOO_FEW_ARGS :
            Diagnostics::PP_MACRO_TOO_MANY_ARGS;
        mDiagnostics->report(id, identifier.location, identifier.text);
        return false;
    }

    // Pre-expand each argument before substitution.
    // This step expands each argument individually before they are
    // inserted into the macro body.
    for (std::size_t i = 0; i < args->size(); ++i)
    {
        MacroArg &arg = args->at(i);
        TokenLexer lexer(&arg);
        MacroExpander expander(&lexer, mMacroSet, mDiagnostics);

        arg.clear();
        expander.lex(&token);
        while (token.type != Token::LAST)
        {
            arg.push_back(token);
            expander.lex(&token);
        }
    }
    return true;
}