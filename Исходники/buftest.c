int test_newbuf(void)
{
    Buf *buf = newbuf();

    /* newbuf sets shiftstate to initial shift state */
    assert(mbsinit(&buf->shiftstate));
    return 0;
}