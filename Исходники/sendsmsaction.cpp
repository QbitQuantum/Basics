static QString strippedSmsNumber( const QString &number )
{
    QString result;

    for ( int i = 0; i < number.length(); ++i ) {
        const QChar character = number.at( i );
        if ( character.isDigit() || ( character == QLatin1Char( '+' ) && i == 0 ) ) {
            result += character;
        }
    }

    return result;
}