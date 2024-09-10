bool Parser::parseCharacterClass(JumpList& failures)
{
    bool invert = false;
    if (peek() == '^') {
        consume();
        invert = true;
    }

    CharacterClassConstructor constructor(m_ignoreCase);

    int ch;
    while ((ch = peek()) != ']') {
        switch (ch) {
        case EndOfPattern:
            setError(CharacterClassUnmatched);
            return false;

        case '\\': {
            consume();
            Escape escape = consumeEscape(true);

            switch (escape.type()) {
                case Escape::PatternCharacter: {
                    int character = PatternCharacterEscape::cast(escape).character();
                    if (character == '-')
                        constructor.flushBeforeEscapedHyphen();
                    constructor.put(character);
                    break;
                }
                case Escape::CharacterClass: {
                    const CharacterClassEscape& characterClassEscape = CharacterClassEscape::cast(escape);
                    ASSERT(!characterClassEscape.invert());
                    constructor.append(characterClassEscape.characterClass());
                    break;
                }
                case Escape::Error:
                    return false;
                case Escape::Backreference:
                case Escape::WordBoundaryAssertion: {
                    ASSERT_NOT_REACHED();
                    break;
                }
            }
            break;
        }

        default:
            consume();
            constructor.put(ch);
        }
    }
    consume();

    // lazily catch reversed ranges ([z-a])in character classes
    if (constructor.isUpsideDown()) {
        setError(CharacterClassOutOfOrder);
        return false;
    }

    constructor.flush();
    CharacterClass charClass = constructor.charClass();
    return parseCharacterClassQuantifier(failures, charClass, invert);
}