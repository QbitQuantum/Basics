void
fpiw2i(Internal *i, void *v)
{
    Word w, word = *(Word*)v;
    short e;

    if(word < 0) {
        i->s = 1;
        word = -word;
    }
    else
        i->s = 0;
    if(word == 0) {
        SetZero(i);
        return;
    }
    if(word > 0) {
        for (e = 0, w = word; w; w >>= 1, e++)
            ;
    } else