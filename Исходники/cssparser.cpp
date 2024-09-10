//auto, #000000, 78px
QSharedPointer<Value> CSSParser::parseValue(){
#ifdef CSS_DEBUG
    qDebug() << Q_FUNC_INFO;
#endif /* CSS_DEBUG */
    QChar c = peekChar();
    if (c.isDigit()) {
        return parseLength();
    } else if (c == '#') {
        return parseColor();
    } else {
//        QSharedPointer<KeywordValue> ret = QSharedPointer<KeywordValue>(new KeywordValue(parseIdentifier()));
        return QSharedPointer<KeywordValue>(new KeywordValue(parseIdentifier()));
    }
    qDebug() << Q_FUNC_INFO << "enter a dead end";

}