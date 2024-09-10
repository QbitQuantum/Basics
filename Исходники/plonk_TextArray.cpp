TextArray::TextArray (Text const &i00,
                      Text const &i01,
                      Text const &i02,
                      Text const &i03,
                      Text const &i04,
                      Text const &i05,
                      Text const &i06,
                      Text const &i07) throw()
:   Base (countStrings (i00, i01, i02, i03, i04, i05, i06, i07), false)
{
    Text *thisArray = this->getArray();
    
    if (i00.length() > 0) thisArray[ 0] = i00; else return;
    if (i01.length() > 0) thisArray[ 1] = i01; else return;
    if (i02.length() > 0) thisArray[ 2] = i02; else return;
    if (i03.length() > 0) thisArray[ 3] = i03; else return;
    if (i04.length() > 0) thisArray[ 4] = i04; else return;
    if (i05.length() > 0) thisArray[ 5] = i05; else return;
    if (i06.length() > 0) thisArray[ 6] = i06; else return;
    if (i07.length() > 0) thisArray[ 7] = i07; else return;
}