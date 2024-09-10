QValidator::State AddressValidator::validate( QString& string, int& pos ) const
{
    Q_UNUSED( pos )

    State result = QValidator::Acceptable;
    if( mCodecId == ExpressionCoding )
    {
        string = string.trimmed();
        if( ! expressionRegex.exactMatch(string) )
            result = QValidator::Invalid;
        //only prefix has been typed:
        if( string == QStringLiteral("+")
            || string == QStringLiteral("-")
            || string.endsWith(QLatin1Char('x')) ) // 0x at end
            result = QValidator::Intermediate;
    }
    else
    {
        const int stringLength = string.length();
        for( int i=0; i<stringLength; ++i )
        {
            const QChar c = string.at( i );
            if( !mValueCodec->isValidDigit( c.toLatin1() ) && !c.isSpace() )
            {
                result = QValidator::Invalid;
                break;
            }
        }
    }
    if( string.isEmpty() )
        result = QValidator::Intermediate;
    return result;
}