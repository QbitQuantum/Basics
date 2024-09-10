void LetterButton::toggleCase()
{
    if ( skip ) {
        // Don't toggle case the first time
        skip=false;
        return;
    }

    QChar ch = text()[0];
    QChar nch = ch.toLower();
    if ( ch == nch )
        nch = ch.toUpper();
    setText(QString(nch));
}