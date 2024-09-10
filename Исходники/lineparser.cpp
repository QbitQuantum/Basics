    bool LineParser::parseKeyword (int keyword, const TokenLoc& loc, Scanner& scanner)
    {
        if (mState==BeginState || mState==ExplicitState)
        {
            switch (keyword)
            {
                case Scanner::K_enable:

                    Generator::enable (mCode, mLiterals, mExplicit);
                    mState = EndState;
                    return true;

                case Scanner::K_disable:

                    Generator::disable (mCode, mLiterals, mExplicit);
                    mState = EndState;
                    return true;
            }

            // check for custom extensions
            if (const Extensions *extensions = getContext().getExtensions())
            {
                std::string argumentType;

                if (extensions->isInstruction (keyword, argumentType, mState==ExplicitState))
                {
                    int optionals = mExprParser.parseArguments (argumentType, scanner, mCode, true);

                    extensions->generateInstructionCode (keyword, mCode, mLiterals, mExplicit, optionals);
                    mState = EndState;
                    return true;
                }
            }

            if (mAllowExpression)
            {
                if (keyword==Scanner::K_getdisabled || keyword==Scanner::K_getdistance)
                {
                    scanner.putbackKeyword (keyword, loc);
                    parseExpression (scanner, loc);
                    mState = EndState;
                    return true;
                }

                if (const Extensions *extensions = getContext().getExtensions())
                {
                    char returnType;
                    std::string argumentType;

                    if (extensions->isFunction (keyword, returnType, argumentType,
                        !mExplicit.empty()))
                    {
                        scanner.putbackKeyword (keyword, loc);
                        parseExpression (scanner, loc);
                        mState = EndState;
                        return true;
                    }
                }
            }
        }

        if (mState==BeginState)
        {
            switch (keyword)
            {
                case Scanner::K_short: mState = ShortState; return true;
                case Scanner::K_long: mState = LongState; return true;
                case Scanner::K_float: mState = FloatState; return true;
                case Scanner::K_set: mState = SetState; return true;
                case Scanner::K_messagebox: mState = MessageState; return true;

                case Scanner::K_return:

                    Generator::exit (mCode);
                    mState = EndState;
                    return true;

                case Scanner::K_startscript:

                    mExprParser.parseArguments ("c", scanner, mCode, true);
                    Generator::startScript (mCode);
                    mState = EndState;
                    return true;

                case Scanner::K_stopscript:

                    mExprParser.parseArguments ("c", scanner, mCode, true);
                    Generator::stopScript (mCode);
                    mState = EndState;
                    return true;
            }
        }
        else if (mState==SetLocalVarState && keyword==Scanner::K_to)
        {
            mExprParser.reset();
            scanner.scan (mExprParser);

            std::vector<Interpreter::Type_Code> code;
            char type = mExprParser.append (code);

            Generator::assignToLocal (mCode, mLocals.getType (mName),
                mLocals.getIndex (mName), code, type);

            mState = EndState;
            return true;
        }
        else if (mState==SetGlobalVarState && keyword==Scanner::K_to)
        {
            mExprParser.reset();
            scanner.scan (mExprParser);

            std::vector<Interpreter::Type_Code> code;
            char type = mExprParser.append (code);

            Generator::assignToGlobal (mCode, mLiterals, mType, mName, code, type);

            mState = EndState;
            return true;
        }
        else if (mState==SetMemberVarState2 && keyword==Scanner::K_to)
        {
            mExprParser.reset();
            scanner.scan (mExprParser);

            std::vector<Interpreter::Type_Code> code;
            char type = mExprParser.append (code);

            Generator::assignToMember (mCode, mLiterals, mType, mMemberName, mName, code, type);

            mState = EndState;
            return true;
        }

        if (mAllowExpression)
        {
            if (keyword==Scanner::K_getsquareroot || keyword==Scanner::K_menumode ||
                keyword==Scanner::K_random || keyword==Scanner::K_scriptrunning ||
                keyword==Scanner::K_getsecondspassed)
            {
                scanner.putbackKeyword (keyword, loc);
                parseExpression (scanner, loc);
                mState = EndState;
                return true;
            }
        }

        return Parser::parseKeyword (keyword, loc, scanner);
    }