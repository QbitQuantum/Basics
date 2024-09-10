bool emit(const Token& token, std::ostream& output)
{
    static bool characterMode = false;
    static std::u16string characters;
    bool eof = false;

    if (characterMode && token.getType() != Token::Type::Character) {
        output << separator << "[\"Character\",\"" << espaceString(characters) << "\"]";
        separator = ",";
        characterMode = false;
        characters.clear();
    }

    switch (token.getType()) {
    case Token::Type::StartTag:
        output << separator << "[\"StartTag\",\"" << espaceString(token.getName()) << "\",{";
        separator = ",";
        for (auto i = token.getAttributes().begin(); i != token.getAttributes().end(); ++i) {
            if (i != token.getAttributes().begin())
                output << ',';
            auto attr = *i;
            output << '"' << espaceString(attr.getName()) << "\":\"" << attr.getValue() << '"';
        }
        output << '}';
        if (token.getFlags() & Token::SelfClosing)
            output << ",true";
        output << ']';
        break;
    case Token::Type::EndTag:
        output << separator << "[\"EndTag\",\"" << espaceString(token.getName()) << "\"]";
        separator = ",";
        break;
    case Token::Type::Comment:
        output << separator << "[\"Comment\",\"" << espaceString(token.getName()) << "\"]";
        separator = ",";
        break;
    case Token::Type::Doctype:
        output << separator << "[\"DOCTYPE\",\"" << espaceString(token.getName()) << "\",";
        separator = ",";
        if (!token.hasPublicId())
            output << "null,";
        else
            output << '"' << espaceString(token.getPublicId()) << "\",";
        if (!token.hasSystemId())
            output << "null,";
        else
            output << '"' << espaceString(token.getSystemId()) << "\",";
        output << ((token.getFlags() & Token::ForceQuirks) ? "false" : "true");
        output << ']';
        break;
    case Token::Type::Character:
        characterMode = true;
        characters += token.getChar();
        break;
    case Token::Type::EndOfFile:
        eof = true;
        break;
    case Token::Type::ParseError:
    default:
        output << separator << "\"ParseError\"";
        separator = ",";
        break;
    }
    return !eof;
}