/*
  Transforms 'int x = 3 + 4' into 'int x=3+4'. A white space is kept
  between 'int' and 'x' because it is meaningful in C++.
*/
static void trimWhiteSpace( QString& str )
{
    enum { Normal, MetAlnum, MetSpace } state = Normal;
    const int n = str.length();

    int j = -1;
    QChar *d = str.data();
    for ( int i = 0; i != n; ++i ) {
        const QChar c = d[i];
        if ( c.isLetterOrNumber() ) {
            if ( state == Normal ) {
                state = MetAlnum;
            } else {
                if ( state == MetSpace )
                    str[++j] = c;
                state = Normal;
            }
            str[++j] = c;
        } else if ( c.isSpace() ) {
            if ( state == MetAlnum )
                state = MetSpace;
        } else {
            state = Normal;
            str[++j] = c;
        }
    }
    str.resize(++j);
}