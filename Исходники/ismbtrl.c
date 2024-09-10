/*
 * @implemented
 */
int _ismbstrail( const unsigned char *start, const unsigned char *str)
{
    /* Note: this function doesn't check _ismbbtrail */
    if ((str > start) && _ismbslead(start, str-1))
        return -1;
    else
        return 0;
}