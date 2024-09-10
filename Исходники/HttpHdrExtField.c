HttpHdrExtField *
httpHdrExtFieldDup(HttpHdrExtField * f)
{
    assert(f);
    return httpHdrExtFieldDoCreate(
	strBuf(f->name), strLen(f->name),
	strBuf(f->value), strLen(f->value));
}