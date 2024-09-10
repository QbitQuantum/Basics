my::LongInt my::operator *(my::LongInt const &_a, unsigned char const b)
{
    unsigned int digit = Pow(2, CHAR_BIT);
    LongInt retVal;
    unsigned int help;
    unsigned char r = 0;
    for (unsigned int i = 0; i < _a.number.GetSize(); i++){
        help = _a.number[i] * b + r;
        r = help / digit;
        retVal.number[i] = help % digit;
    }
    if (r != 0)
        retVal.number.PushBack(r);
    return retVal;
}