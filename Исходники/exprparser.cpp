    int ExprParser::parseArguments (const std::string& arguments, Scanner& scanner,
        std::vector<Interpreter::Type_Code>& code)
    {
        bool optional = false;
        int optionalCount = 0;

        ExprParser parser (getErrorHandler(), getContext(), mLocals, mLiterals, true);
        StringParser stringParser (getErrorHandler(), getContext(), mLiterals);

        std::stack<std::vector<Interpreter::Type_Code> > stack;

        for (std::string::const_iterator iter (arguments.begin()); iter!=arguments.end();
            ++iter)
        {
            if (*iter=='/')
            {
                optional = true;
            }
            else if (*iter=='S' || *iter=='c' || *iter=='x')
            {
                stringParser.reset();

                if (optional || *iter=='x')
                    stringParser.setOptional (true);

                if (*iter=='c') stringParser.smashCase();
                scanner.scan (stringParser);

                if (optional && stringParser.isEmpty())
                    break;

                if (*iter!='x')
                {
                    std::vector<Interpreter::Type_Code> tmp;
                    stringParser.append (tmp);

                    stack.push (tmp);

                    if (optional)
                        ++optionalCount;
                }
            }
            else
            {
                parser.reset();

                if (optional || *iter == 'X')
                    parser.setOptional (true);

                scanner.scan (parser);

                if (optional && parser.isEmpty())
                    break;

                if (*iter != 'X')
                {
                    std::vector<Interpreter::Type_Code> tmp;

                    char type = parser.append (tmp);

                    if (type!=*iter)
                        Generator::convert (tmp, type, *iter);

                    stack.push (tmp);

                    if (optional)
                        ++optionalCount;
                }
            }
        }

        while (!stack.empty())
        {
            std::vector<Interpreter::Type_Code>& tmp = stack.top();

            std::copy (tmp.begin(), tmp.end(), std::back_inserter (code));

            stack.pop();
        }

        return optionalCount;
    }