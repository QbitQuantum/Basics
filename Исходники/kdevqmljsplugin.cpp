// Finds how many spaces the given string has at one end.
// direction=+1 -> left end of the string, -1 for right end.
int spacesAtCorner(const QString& string, int direction = +1) {
    int spaces = 0;
    QString::const_iterator it;
    for ( it = direction == 1 ? string.begin() : string.end()-1 ; it != string.end(); it += direction ) {
        if ( ! it->isSpace() ) break;
        spaces += 1;
    }
    return spaces;
}