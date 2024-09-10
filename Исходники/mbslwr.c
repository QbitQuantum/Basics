/*
 * @implemented
 */
unsigned char * _mbslwr(unsigned char *x)
{
    unsigned char *y=x;

    if (x == NULL)
    {
        return NULL;
    }

    while (*y) 
    {
        if (!_ismbblead(*y)) 
        {
            *y = tolower(*y);
            y++;
        } 
        else
        {
            *y = _mbctolower(*(unsigned short *)y);
            y++;
        }
    }
    return x;
}