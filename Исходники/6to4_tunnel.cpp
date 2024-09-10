// ----------------------------------------------------------------------------
// TTunnelParser::NextToken
// Returns the next token type in the input stream. iToken gets the value of
// the (string) token.
// ----------------------------------------------------------------------------
//
TTunnelParser::TTokenType TTunnelParser::NextToken ()
{
    TChar ch;
    TTokenType val;

    SkipSpaceAndMark ();
    if (Eos ())
        val = ETokenTypeEof;
    else
    {
        ch = Get ();
        switch (ch)
        {
        case '{':
            val = ETokenTypeBraceLeft;
            break;
        case '}':
            val = ETokenTypeBraceRight;
            break;
        case '(':
            val = ETokenTypeParLeft;
            break;
        case ')':
            val = ETokenTypeParRight;
            break;
        case '=':
            val = ETokenTypeEqual;
            break;
        case ',':
            val = ETokenTypeComma;
            break;
        case '#':
            val = ETokenTypeComment;
            while (!Eos())
            {
                ch = Get();
                if (ch == '\n' || ch == '\r')
                    break;
            }
            break;
        default:
            // Integers, ip addresses, etc. are mapped to strings.
            val = ETokenTypeString;
            while (!Eos ())
            {
                ch = Peek ();
                if (ch == '{' || ch == '}' ||
                        ch == '(' || ch == ')' ||
                        ch == '=' || ch == '#' ||
                        ch == ',' || ch.IsSpace ())
                    break;
                Inc ();
            }
        }
    }

    iToken.Set (MarkedToken ());
    SkipSpaceAndMark ();

    return val;
}