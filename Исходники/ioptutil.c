BITARRAY *callocbit(int size)
{
    BITARRAY *rv = cAlloc(sizeof(BITARRAY) - 1 + (size + (BITINTBITS-1))/BITINTBITS * sizeof(BITINT));
    rv->count = size;
    return rv;
}