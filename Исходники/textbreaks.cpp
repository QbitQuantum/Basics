static inline bool isWordSeparator(const QChar character)
{
    return character.isSpace() || character.isMark() || character.isPunct() || character.isSymbol();
}