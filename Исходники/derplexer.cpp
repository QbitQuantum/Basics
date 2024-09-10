    bool derpGetTokens(
        const std::string &str,
        std::vector<DerpToken*> &outTokens,
        DerpErrorState &errorState,
        const std::string &fileName) {

        unsigned int i = 0;
        unsigned int lineNumber = 1;

        while(i < str.size()) {

            // Skip over whitespace.
            while(i < str.size() && isWhitespace(str[i])) {

                if(str[i] == '\n') lineNumber++;

                i++;
            }

            if(i >= str.size()) break;

            // Figure out token type with a big ugly if/else thinger.

            if(str[i] == '/' && (i + 1) < str.size() && str[i+1] == '/') {

                // C++ style comment. Just throw it away.
                i += 2;
                while(i < str.size()) {
                    if(str[i] == '\n') break;
                    i++;
                }

            } else if(str[i] == '#') {

                // Shell-script style comment. Just throw it away too.
                i++;
                while(i < str.size()) {
                    if(str[i] == '\n') break;
                    i++;
                }

            } else if(str[i] == '\"') {

                // Found a literal quoted string.
                DerpToken *stringToken = parseString(
                    str, i, fileName, lineNumber, errorState);
                if(!stringToken) {
                    return false;
                }

                outTokens.push_back(stringToken);

            } else if(isDigit(str[i])) {

                // Found a number
                outTokens.push_back(parseNumber(str, i, fileName, lineNumber));

            } else if(isValidSymbolChar(str[i], true)) {

                // Found either a symbol or a keyword.
                DerpToken *symbolToken = parseSymbolOrKeyword(
                    str, i, fileName, lineNumber, errorState);
                if(!symbolToken) {
                    return false;
                }

                outTokens.push_back(symbolToken);

            } else {

                // Found some special character.

                // TODO: Replace this with some table-based lookup.

                bool foundTwoCharacterOperator = false;

                // First check all the two-character operators.

                if(str.size() > (i + 1)) {

                    char twoCharOp[3] = {
                        str[i], str[i+1], 0
                    };

                    if(string(":=") == twoCharOp ||
                       string("&&") == twoCharOp ||
                       string("||") == twoCharOp ||
                       string("!=") == twoCharOp ||
                       string("==") == twoCharOp ||
                       string("++") == twoCharOp ||
                       string("--") == twoCharOp ||
                       string(">=") == twoCharOp ||
                       string("<=") == twoCharOp) {

                        foundTwoCharacterOperator = true;
                        outTokens.push_back(new DerpToken(twoCharOp, DERPTOKEN_MATHOP, fileName, lineNumber));
                        i += 2;
                    }

                }

                // If it wasn't a two-character operator, try the
                // single-character operators.

                if(!foundTwoCharacterOperator) {

                    switch(str[i]) {

                        case '{':

                            // Found an open curly.
                            outTokens.push_back(new DerpToken("{", DERPTOKEN_OPENCURLY, fileName, lineNumber));
                            i++;
                            break;

                        case '}':

                            // Found a closing curly.
                            outTokens.push_back(new DerpToken("}", DERPTOKEN_CLOSECURLY, fileName, lineNumber));
                            i++;
                            break;

                        case '[':

                            // Found an open curly.
                            outTokens.push_back(new DerpToken("[", DERPTOKEN_OPENBRACKET, fileName, lineNumber));
                            i++;
                            break;

                        case ']':

                            // Found a closing curly.
                            outTokens.push_back(new DerpToken("]", DERPTOKEN_CLOSEBRACKET, fileName, lineNumber));
                            i++;
                            break;

                        case '(':

                            // Found an open parenthesis.
                            outTokens.push_back(new DerpToken("(", DERPTOKEN_OPENPAREN, fileName, lineNumber));
                            i++;
                            break;

                        case ')':

                            // Found a closing parenthesis.
                            outTokens.push_back(new DerpToken("(", DERPTOKEN_CLOSEPAREN, fileName, lineNumber));
                            i++;
                            break;

                        case ';':

                            // End statement.
                            outTokens.push_back(new DerpToken(";", DERPTOKEN_ENDSTATEMENT, fileName, lineNumber));
                            i++;
                            break;

                        case ',':
                            outTokens.push_back(new DerpToken(",", DERPTOKEN_COMMA, fileName, lineNumber));
                            i++;
                            break;

                        case '+':
                        case '-':
                        case '*':
                        case '/':
                        case '!':
                        case '=':
                        case '<':
                        case '>':
                        case '.':

                            // Found math operator.
                            outTokens.push_back(new DerpToken(strFromChar(str[i]), DERPTOKEN_MATHOP, fileName, lineNumber));
                            i++;
                            break;

                        default:

                            // I have no idea what to do with this. Toss an error and return.

                            errorState.setFileAndLineDirect(
                                fileName,
                                lineNumber);

                            errorState.addError(
                                derpSprintf("Bad token: \"%c\"", str[i]));

                            return false;
                    }

                }

            }

            if(outTokens.size() > DERP_MAX_TOKENS) {

                errorState.setFileAndLineDirect(
                    fileName,
                    lineNumber);

                errorState.addError(
                    "Exceeded maximum number of tokens.");

                return false;
            }
        }

        return true;
    }