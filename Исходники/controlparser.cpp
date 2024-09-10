    bool ControlParser::parseIfBody (int keyword, const TokenLoc& loc, Scanner& scanner)
    {
        if (keyword==Scanner::K_endif || keyword==Scanner::K_elseif ||
            keyword==Scanner::K_else)
        {
            std::pair<Codes, Codes> entry;

            if (mState!=IfElseBodyState)
                mExprParser.append (entry.first);

            std::copy (mCodeBlock.begin(), mCodeBlock.end(),
                std::back_inserter (entry.second));

            mIfCode.push_back (entry);

            mCodeBlock.clear();

            if (keyword==Scanner::K_endif)
            {
                // store code for if-cascade
                Codes codes;

                for (IfCodes::reverse_iterator iter (mIfCode.rbegin());
                    iter!=mIfCode.rend(); ++iter)
                {
                    Codes block;

                    if (iter!=mIfCode.rbegin())
                        Generator::jump (iter->second, codes.size()+1);

                    if (!iter->first.empty())
                    {
                        // if or elseif
                        std::copy (iter->first.begin(), iter->first.end(),
                            std::back_inserter (block));
                        Generator::jumpOnZero (block, iter->second.size()+1);
                    }

                    std::copy (iter->second.begin(), iter->second.end(),
                        std::back_inserter (block));

                   std::swap (codes, block);

                   std::copy (block.begin(), block.end(), std::back_inserter (codes));
                }

                std::copy (codes.begin(), codes.end(), std::back_inserter (mCode));

                mIfCode.clear();
                mState = IfEndifState;
            }
            else if (keyword==Scanner::K_elseif)
            {
                mExprParser.reset();
                scanner.scan (mExprParser);

                mState = IfElseifEndState;
            }
            else if (keyword==Scanner::K_else)
            {
                mState = IfElseJunkState; /// \todo should be IfElseEndState; add an option for that
            }

            return true;
        }
        else if (keyword==Scanner::K_if || keyword==Scanner::K_while)
        {
            // nested
            ControlParser parser (getErrorHandler(), getContext(), mLocals, mLiterals);

            if (parser.parseKeyword (keyword, loc, scanner))
                scanner.scan (parser);

            parser.appendCode (mCodeBlock);

            return true;
        }
        else
        {
            mLineParser.reset();
            if (mLineParser.parseKeyword (keyword, loc, scanner))
                scanner.scan (mLineParser);

            return true;
        }
    }