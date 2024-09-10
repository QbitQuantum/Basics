    bool FileParser::parseSpecial (int code, const TokenLoc& loc, Scanner& scanner)
    {
        if (code==Scanner::S_newline)
        {
            if (mState==BeginState)
            {
                // ignore empty lines
                return true;
            }

            if (mState==BeginCompleteState)
            {
                // parse the script body
                mScriptParser.reset();

                scanner.scan (mScriptParser);

                mState = EndNameState;
                scanner.allowNameStartingwithDigit();
                return true;
            }

            if (mState==EndCompleteState || mState==EndNameState)
            {
                // we are done here -> ignore the rest of the script
                return false;
            }
        }

        return Parser::parseSpecial (code, loc, scanner);
    }