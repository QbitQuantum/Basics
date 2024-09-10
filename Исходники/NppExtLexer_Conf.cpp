static void Colourise_Doc(unsigned int startPos, int length, int, WordList *keywordLists[], Accessor &styler)
{
    int state = sID::DEFAULT;
    char chNext = styler[startPos];
    int lengthDoc = startPos + length;
    // create a buffer large enough to take the largest chunk...
    char *buffer = new char[length];
    int bufferCount = 0;

    // this assumes that we have 2 keyword list in conf.properties
    WordList &directives = *keywordLists[0];
    WordList &params = *keywordLists[1];
    WordList &USERDEF = *keywordLists[2];

    // go through all provided text segment
    // using the hand-written state machine shown below
    styler.StartAt(startPos);
    styler.StartSegment(startPos);
    for (int i = startPos; i < lengthDoc; i++) {
        char ch = chNext;
        chNext = styler.SafeGetCharAt(i + 1);

        if (styler.IsLeadByte(ch)) {
            chNext = styler.SafeGetCharAt(i + 2);
            i++;
            continue;
        }
        switch(state) {
        case sID::DEFAULT:
            if( ch == '\n' || ch == '\r' || ch == '\t' || ch == ' ') {
                // whitespace is simply ignored here...
                styler.ColourTo(i,sID::DEFAULT);
                break;
            } else if( ch == '#' ) {
                // signals the start of a comment...
                state = sID::COMMENT;
                styler.ColourTo(i,sID::COMMENT);
            } else if( ch == '.' /*|| ch == '/'*/) {
                // signals the start of a file...
                state = sID::EXTENSION;
                styler.ColourTo(i,sID::EXTENSION);
            } else if( ch == '"') {
                state = sID::STRING;
                styler.ColourTo(i,sID::STRING);
            } else if( ispunct(ch) ) {
                // signals an operator...
                // no state jump necessary for this
                // simple case...
                styler.ColourTo(i,sID::OPERATOR);
            } else if( isalpha(ch) ) {
                // signals the start of an identifier
                bufferCount = 0;
                buffer[bufferCount++] = static_cast<char>(tolower(ch));
                state = sID::IDENTIFIER;
            } else if( isdigit(ch) ) {
                // signals the start of a number
                bufferCount = 0;
                buffer[bufferCount++] = ch;
                //styler.ColourTo(i,sID::NUMBER);
                state = sID::NUMBER;
            } else {
                // style it the default style..
                styler.ColourTo(i,sID::DEFAULT);
            }
            break;

        case sID::COMMENT:
            // if we find a newline here,
            // we simply go to default state
            // else continue to work on it...
            if( ch == '\n' || ch == '\r' ) {
                state = sID::DEFAULT;
            } else {
                styler.ColourTo(i,sID::COMMENT);
            }
            break;

        case sID::EXTENSION:
            // if we find a non-alphanumeric char,
            // we simply go to default state
            // else we're still dealing with an extension...
            if( isalnum(ch) || (ch == '_') ||
                    (ch == '-') || (ch == '$') ||
                    (ch == '/') || (ch == '.') || (ch == '*') )
            {
                styler.ColourTo(i,sID::EXTENSION);
            } else {
                state = sID::DEFAULT;
                chNext = styler[i--];
            }
            break;

        case sID::STRING:
            // if we find the end of a string char, we simply go to default state
            // else we're still dealing with an string...
            if( (ch == '"' && styler.SafeGetCharAt(i-1)!='\\') || (ch == '\n') || (ch == '\r') ) {
                state = sID::DEFAULT;
            }
            styler.ColourTo(i,sID::STRING);
            break;

        case sID::IDENTIFIER:
            // stay  in CONF_IDENTIFIER state until we find a non-alphanumeric
            if( isalnum(ch) || (ch == '_') || (ch == '-') || (ch == '/') || (ch == '$') || (ch == '.') || (ch == '*')) {
                buffer[bufferCount++] = static_cast<char>(tolower(ch));
            } else {
                state = sID::DEFAULT;
                buffer[bufferCount] = '\0';

                // check if the buffer contains a keyword, and highlight it if it is a keyword...
                if(directives.InList(buffer)) {
                    styler.ColourTo(i-1,sID::DIRECTIVE );
                } else if(params.InList(buffer)) {
                    styler.ColourTo(i-1,sID::PARAMETER );
                } else if(USERDEF.InList(buffer)) {
                    styler.ColourTo(i-1,sID::USERDEF );
                } else if(strchr(buffer,'/') || strchr(buffer,'.')) {
                    styler.ColourTo(i-1,sID::EXTENSION);
                } else {
                    styler.ColourTo(i-1,sID::DEFAULT);
                }

                // push back the faulty character
                chNext = styler[i--];

            }
            break;

        case sID::NUMBER:
            // stay  in CONF_NUMBER state until we find a non-numeric
            if( isdigit(ch) || ch == '.') {
                buffer[bufferCount++] = ch;
            } else {
                state = sID::DEFAULT;
                buffer[bufferCount] = '\0';

                // Colourize here...
                if( strchr(buffer,'.') ) {
                    // it is an IP address...
                    styler.ColourTo(i-1,sID::IP);
                } else {
                    // normal number
                    styler.ColourTo(i-1,sID::NUMBER);
                }

                // push back a character
                chNext = styler[i--];
            }
            break;

        }
    }
    delete []buffer;
}