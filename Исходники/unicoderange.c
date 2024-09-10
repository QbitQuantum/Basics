static int ncmp(const void *_ri1, const void *_ri2) {
    const struct rangeinfo *ri1 = _ri1, *ri2 = _ri2;

return( strcoll(_(ri1->range->name),_(ri2->range->name)));
}