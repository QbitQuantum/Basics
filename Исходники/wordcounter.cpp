void addWord(char *place, char *word)
{
    char *current = place;
    char *parent = NULL;
    int resCmp = 0;
    for (;;)
    {
        resCmp = strCmp(word, current);
        if (resCmp > 0)
        {
            parent = current - 1;
            if (*parent)
                current = place + *parent + wordNodeHeaderSize;
            else
                break;
        }
        else if (resCmp < 0)
        {
            parent = current - 2;
            if (*parent)
                current = place + *parent + wordNodeHeaderSize;
            else
                break;
        }
        else
            break;
    }
    if (resCmp)
    {
        WordBST * bst = (WordBST *) (place - fullHeaderSize);
        if (bst->current + wordNodeHeaderSize + strlen(word) >= wordBSTSize)
            throw OverflowException();
        *parent = bst->current;
        bst->current += WordNodeInit(place + bst->current, word)
                      + wordNodeHeaderSize;
    }
    else
    {
        WordNode * node = (WordNode *) (current - wordNodeHeaderSize);
        node->counter++;
    }
}