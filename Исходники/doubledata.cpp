/* This function returns \a number rounded using \a precision as precision indicator.
   The assumption is that the digit in position <code>precision+1</code> is used to work
   out what rounding rule to apply. This means the <code>precision+1</code>. digit in \a number
   must still be correct.
   */
QString roundDigits( const QString number, int precision ) {
    QString rounded = number;
    int point = number.indexOf( '.' ) ;
    if ( point > -1 && point <= precision-1 ) {
        bool up = (number.at(precision+1).isDigit() && number.at(precision+1) >= QChar('5')  );
        if ( !up ) {
            return rounded;
        }
        for ( int i = precision; i>= 0 ; i-- ) {
            if ( !up ) {
                return rounded;
            }
            QChar current = rounded.at(i);
            if ( !current.isDigit() ) {
                continue;
            }
            QChar newCurrent = (current == QChar('9')) ? QChar('0') : QChar(current.toAscii()+1) ;
            up = (newCurrent == QChar('0') );
            rounded = rounded.replace( i , 1,  newCurrent );
        }
    }
    return rounded;
}