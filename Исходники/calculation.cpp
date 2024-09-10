//------------------------------------------------------------------------------
QString StringMod::getPosAlphabet(const QChar word) {
    QString res = word;
    char alphabet[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n',
        'o','p','q','r','s','t','u','v','w','x','y','z','0','1',
        '2','3','4','5','6','7','8','9','-'};
    for (int i = 0; i < sizeof(alphabet); ++i) {
        if (word.toLower()==alphabet[i]) {
            res = QString::number(i+1);
            break;
        }
    }
    return res;
}