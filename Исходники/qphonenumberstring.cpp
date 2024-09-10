QChar QPhoneNumberString::translatedToVanity(const QChar c) {
    if ( c.isNull() ) return QChar();
    if ( c.isNumber() ) return c;
    if ( c.isSpace() ) return QChar('1');
    QChar vanityChar = m_VanityChars[ c.toLower() ];
    if ( vanityChar.isNull() )
        kDebug() << " did not found char "
                 << c << hex << c.unicode()
                 << "\" to translate.";
    return( vanityChar );
}