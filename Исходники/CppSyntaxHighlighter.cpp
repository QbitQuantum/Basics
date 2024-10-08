void CppSyntaxHighlighter::highlightBlock(const QString &text)
{
    // states
    const int StateStandard = 0;
    const int StateCommentStart1 = 1;
    const int StateCCommentStart2 = 2;
    const int StateCppCommentStart2 = 3;
    const int StateCComment = 4;
    const int StateCppComment = 5;
    const int StateCCommentEnd1 = 6;
    const int StateCCommentEnd2 = 7;
    const int StateStringStart = 8;
    const int StateString = 9;
    const int StateStringEnd = 10;
    const int StateString2Start = 11;
    const int StateString2 = 12;
    const int StateString2End = 13;
    const int StateNumber = 14;
    const int StatePreProcessor = 15;

    // tokens
    const int InputAlpha = 0;
    const int InputNumber = 1;
    const int InputAsterix = 2;
    const int InputSlash = 3;
    const int InputParen = 4;
    const int InputSpace = 5;
    const int InputHash = 6;
    const int InputQuotation = 7;
    const int InputApostrophe = 8;
    const int InputSep = 9;

    static const uchar table[16][10] = {
        { StateStandard,      StateNumber,     StateStandard,       StateCommentStart1,    StateStandard,   StateStandard,   StatePreProcessor, StateStringStart, StateString2Start, StateStandard }, // StateStandard
        { StateStandard,      StateNumber,   StateCCommentStart2, StateCppCommentStart2, StateStandard,   StateStandard,   StatePreProcessor, StateStringStart, StateString2Start, StateStandard }, // StateCommentStart1
        { StateCComment,      StateCComment,   StateCCommentEnd1,   StateCComment,         StateCComment,   StateCComment,   StateCComment,     StateCComment,    StateCComment,     StateCComment }, // StateCCommentStart2
        { StateCppComment,    StateCppComment, StateCppComment,     StateCppComment,       StateCppComment, StateCppComment, StateCppComment,   StateCppComment,  StateCppComment,   StateCppComment }, // CppCommentStart2
        { StateCComment,      StateCComment,   StateCCommentEnd1,   StateCComment,         StateCComment,   StateCComment,   StateCComment,     StateCComment,    StateCComment,     StateCComment }, // StateCComment
        { StateCppComment,    StateCppComment, StateCppComment,     StateCppComment,       StateCppComment, StateCppComment, StateCppComment,   StateCppComment,  StateCppComment,   StateCppComment }, // StateCppComment
        { StateCComment,      StateCComment,   StateCCommentEnd1,   StateCCommentEnd2,     StateCComment,   StateCComment,   StateCComment,     StateCComment,    StateCComment,     StateCComment }, // StateCCommentEnd1
        { StateStandard,      StateNumber,     StateStandard,       StateCommentStart1,    StateStandard,   StateStandard,   StatePreProcessor, StateStringStart, StateString2Start, StateStandard }, // StateCCommentEnd2
        { StateString,        StateString,     StateString,         StateString,           StateString,     StateString,     StateString,       StateStringEnd,   StateString,       StateString }, // StateStringStart
        { StateString,        StateString,     StateString,         StateString,           StateString,     StateString,     StateString,       StateStringEnd,   StateString,       StateString }, // StateString
        { StateStandard,      StateStandard,   StateStandard,       StateCommentStart1,    StateStandard,   StateStandard,   StatePreProcessor, StateStringStart, StateString2Start, StateStandard }, // StateStringEnd
        { StateString2,       StateString2,    StateString2,        StateString2,          StateString2,    StateString2,    StateString2,      StateString2,     StateString2End,   StateString2 }, // StateString2Start
        { StateString2,       StateString2,    StateString2,        StateString2,          StateString2,    StateString2,    StateString2,      StateString2,     StateString2End,   StateString2 }, // StateString2
        { StateStandard,      StateStandard,   StateStandard,       StateCommentStart1,    StateStandard,   StateStandard,   StatePreProcessor, StateStringStart, StateString2Start, StateStandard }, // StateString2End
        { StateNumber,        StateNumber,     StateStandard,       StateCommentStart1,    StateStandard,   StateStandard,   StatePreProcessor, StateStringStart, StateString2Start, StateStandard }, // StateNumber
        { StatePreProcessor,  StateStandard,   StateStandard,       StateCommentStart1,    StateStandard,   StateStandard,   StatePreProcessor, StateStringStart, StateString2Start, StateStandard } // StatePreProcessor
    };

    QString buffer;
    QTextCharFormat emptyFormat;

    int state = StateStandard;
    const int previousState = previousBlockState();
    if (previousState != -1)
        state = previousState;

    BlockData *blockData = static_cast<BlockData *>(currentBlockUserData());
    if (blockData) {
        blockData->parentheses.clear();
    } else {
        blockData = new BlockData;
        setCurrentBlockUserData(blockData);
    }

    if (text.isEmpty()) {
        setCurrentBlockState(previousState);
        return;
    }

    int input = -1;
    int i = 0;
    bool lastWasBackSlash = false;
    bool makeLastStandard = false;

    static QString alphabeth = QString::fromLatin1("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
    static QString mathChars = QString::fromLatin1("xXeE");
    static QString numbers = QString::fromLatin1("0123456789");
    bool questionMark = false;
    bool resetLineState = true;
    QChar lastChar;
    QString firstWord;
    forever {
        QChar c = text.at(i);

        if (lastWasBackSlash) {
            input = InputSep;
        } else {
            switch (c.toAscii()) {
                case '*':
                    input = InputAsterix;
                    break;
                case '/':
                    input = InputSlash;
                    break;
                case '(': case '[': case '{':
                    input = InputParen;
                    if (state == StateStandard
                        || state == StateNumber
                        || state == StatePreProcessor
                        || state == StateCCommentEnd2
                        || state == StateCCommentEnd1
                        || state == StateString2End
                        || state == StateStringEnd
                       )
                        blockData->parentheses << Parenthesis(Parenthesis::Open, c, i);
                    break;
                case ')': case ']': case '}':
                    input = InputParen;
                    if (state == StateStandard
                        || state == StateNumber
                        || state == StatePreProcessor
                        || state == StateCCommentEnd2
                        || state == StateCCommentEnd1
                        || state == StateString2End
                        || state == StateStringEnd
                       ) {
                        blockData->parentheses << Parenthesis(Parenthesis::Closed, c, i);
                        /* #####
                        if (c == '}') {
                            if (checkFunctionEnd(string, i))
                                resetLineState = false;
                        }
                        */
                    }
                    break;
                case '#':
                    input = InputHash;
                    break;
                case '"':
                    input = InputQuotation;
                    break;
                case '\'':
                    input = InputApostrophe;
                    break;
                case ' ':
                    input = InputSpace;
                    if (firstWord == QLatin1String("function")
                        || firstWord == QLatin1String("constructor")
                        || firstWord == QLatin1String("class")
                        // || firstWord == QLatin1String("if")
                        // || firstWord == QLatin1String("for")
                        // || firstWord == QLatin1String("while")
                        // || firstWord == QLatin1String("else")
                       ) {
                        // #### paragData->lineState = ParagData::FunctionStart;
                        resetLineState = false;
                    }
                    break;
                case '1': case '2': case '3': case '4': case '5':
                case '6': case '7': case '8': case '9': case '0':
                    if (alphabeth.contains(lastChar)
                        && (!mathChars.contains(lastChar) || !numbers.contains(text.at(i - 1)))) {
                        input = InputAlpha;
                    } else {
                        if (input == InputAlpha && numbers.contains(lastChar))
                            input = InputAlpha;
                        else
                            input = InputNumber;
                    }
                    break;
                case ':': {
                              input = InputAlpha;
                              QChar nextChar = ' ';
                              if (i < text.length() - 1)
                                  nextChar = text.at(i + 1);
                              if (state == StateStandard && !questionMark &&
                                  lastChar != ':' && nextChar != ':' && lastChar.isLetter()) {
                                  for (int j = 0; j < i; ++j) {
                                      if (format(j) == emptyFormat)
                                          setFormat(j, 1, labelFormat);
                                  }
                              }
                              break;
                          }
                default: {
                             if ( c != QLatin1Char('\t') )
                                 firstWord += c;
                             const QString s = firstWord.simplified();
                             if ( s == QLatin1String("private")
                                  || s == QLatin1String("protected")
                                  || s == QLatin1String("public")
                                  || s == QLatin1String("static")
                                )
                                 firstWord.clear();
                             if (!questionMark && c == QLatin1Char('?'))
                                 questionMark = true;
                             if (c.isLetter() || c == QLatin1Char('_'))
                                 input = InputAlpha;
                             else
                                 input = InputSep;
                         } break;
            }
        }

        lastWasBackSlash = !lastWasBackSlash && c == QLatin1Char('\\');

        if (input == InputAlpha)
            buffer += c;

        state = table[state][input];

        switch (state) {
            case StateStandard: {
                                    setFormat(i, 1, emptyFormat);
                                    if (makeLastStandard)
                                        setFormat(i - 1, 1, emptyFormat);
                                    makeLastStandard = false;
                                    if (!buffer.isEmpty() && input != InputAlpha ) {
                                        highlightKeyword(i, buffer);
                                        buffer.clear();
                                    }
                                } break;
            case StateCommentStart1:
                                if (makeLastStandard)
                                    setFormat(i - 1, 1, emptyFormat);
                                makeLastStandard = true;
                                buffer.clear();
                                break;
            case StateCCommentStart2:
                                setFormat(i - 1, 2, commentFormat);
                                makeLastStandard = false;
                                buffer.clear();
                                break;
            case StateCppCommentStart2:
                                setFormat(i - 1, 2, commentFormat);
                                makeLastStandard = false;
                                buffer.clear();
                                break;
            case StateCComment:
                                if (makeLastStandard)
                                    setFormat(i - 1, 1, emptyFormat);
                                makeLastStandard = false;
                                setFormat(i, 1, commentFormat);
                                buffer.clear();
                                break;
            case StateCppComment:
                                if (makeLastStandard)
                                    setFormat(i - 1, 1, emptyFormat);
                                makeLastStandard = false;
                                setFormat(i, 1, commentFormat);
                                buffer.clear();
                                break;
            case StateCCommentEnd1:
                                if (makeLastStandard)
                                    setFormat(i - 1, 1, emptyFormat);
                                makeLastStandard = false;
                                setFormat(i, 1, commentFormat);
                                buffer.clear();
                                break;
            case StateCCommentEnd2:
                                if (makeLastStandard)
                                    setFormat(i - 1, 1, emptyFormat);
                                makeLastStandard = false;
                                setFormat(i, 1, commentFormat);
                                buffer.clear();
                                break;
            case StateStringStart:
                                if (makeLastStandard)
                                    setFormat(i - 1, 1, emptyFormat);
                                makeLastStandard = false;
                                setFormat(i, 1, emptyFormat);
                                buffer.clear();
                                break;
            case StateString:
                                if (makeLastStandard)
                                    setFormat(i - 1, 1, emptyFormat);
                                makeLastStandard = false;
                                setFormat(i, 1, stringFormat);
                                buffer.clear();
                                break;
            case StateStringEnd:
                                if (makeLastStandard)
                                    setFormat(i - 1, 1, emptyFormat);
                                makeLastStandard = false;
                                setFormat(i, 1, emptyFormat);
                                buffer.clear();
                                break;
            case StateString2Start:
                                if (makeLastStandard)
                                    setFormat(i - 1, 1, emptyFormat);
                                makeLastStandard = false;
                                setFormat(i, 1, emptyFormat);
                                buffer.clear();
                                break;
            case StateString2:
                                if (makeLastStandard)
                                    setFormat(i - 1, 1, emptyFormat);
                                makeLastStandard = false;
                                setFormat(i, 1, stringFormat);
                                buffer.clear();
                                break;
            case StateString2End:
                                if (makeLastStandard)
                                    setFormat(i - 1, 1, emptyFormat);
                                makeLastStandard = false;
                                setFormat(i, 1, emptyFormat);
                                buffer.clear();
                                break;
            case StateNumber:
                                if (makeLastStandard)
                                    setFormat(i - 1, 1, emptyFormat);
                                makeLastStandard = false;
                                setFormat( i, 1, numberFormat);
                                buffer.clear();
                                break;
            case StatePreProcessor:
                                if (makeLastStandard)
                                    setFormat(i - 1, 1, emptyFormat);
                                makeLastStandard = false;
                                setFormat(i, 1, preProcessorFormat);
                                buffer = QString::null;
                                break;
        }

        lastChar = c;
        i++;
        if (i >= text.length())
            break;
    }

    highlightKeyword(text.length(), buffer);

    /*
    if (resetLineState)
        paragData->lineState = ParagData::InFunction;
    string->setExtraData( paragData );
    */

    if (state == StateCComment 
        || state == StateCCommentEnd1
        || state == StateCCommentStart2
       ) {
        state = StateCComment;
    } else if (state == StateString) {
        state = StateString;
    } else if (state == StateString2) {
        state =  StateString2;
    } else {
        state = StateStandard;
    }

    if (blockData->parenthesisMatchStart != -1) {
        for (int pos = blockData->parenthesisMatchStart;
             pos < blockData->parenthesisMatchEnd; ++pos) {
            QTextCharFormat fmt = format(pos);
            fmt.merge(blockData->parenthesisMatchingFormat);
            setFormat(pos, 1, fmt);
        }
    }

    if (blockData->errorMarkerFormat.hasProperty(ErrorMarkerPropertyId)) {
        for (int i = 0; i < text.length(); ++i) {
            QTextCharFormat fmt = format(i);
            fmt.merge(blockData->errorMarkerFormat);
            setFormat(i, 1, fmt);
        }
    }

    setCurrentBlockState(state);
}