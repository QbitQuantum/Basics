static bool CharMatch(QChar ref, QChar test)
// ----------------------------------------------------------------------------
//   Character matching function used by incremental search
// ----------------------------------------------------------------------------
//   * Comparison is case-insensitive
//   * Space and underscore are equivalent
//   * Accent folding: a letter without accent matches itself and the same
//     letter with any accent; but an accented letter matches only itself.
//     For instance:   CharMatch('e', 'é') => true
//                     CharMatch('e', 'e') => true
//                     CharMatch('é', 'e') => false
{
    static QMap<QChar, QChar> fold;

    if (fold.empty())
    {
#       define F(from, to) fold[QChar(from)] = QChar(to)
        F(0xE0, 'a'); F(0xE1, 'a'); F(0xE2, 'a'); F(0xE3, 'a'); F(0xE4, 'a');
        F(0xE5, 'a');
        F(0xE8, 'e'); F(0xE9, 'e'); F(0xEA, 'e'); F(0xEB, 'e');
        F(0xEC, 'i'); F(0xED, 'i'); F(0xEE, 'i'); F(0xEF, 'i');
        F(0xF2, 'o'); F(0xF3, 'o'); F(0xF4, 'o'); F(0xF5, 'o'); F(0xF6, 'o');
        F(0xF8, 'o');
        F(0xF9, 'u'); F(0xFA, 'u'); F(0xFB, 'u'); F(0xFC, 'u');
        F(0xFD, 'y'); F(0xFF, 'y');
#       undef F
    }

    if (test.toLower() == ref.toLower())
        return true;
    if ((test.isSpace() || test == '_') &&
        ( ref.isSpace() ||  ref == '_'))
        return true;
    if (fold.contains(test) && fold[test] == ref)
        return true;

    return false;
}