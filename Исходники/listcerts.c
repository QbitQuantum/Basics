int
do_attribute_value(void *context, long state_index,
                   unsigned char tag,
                   const void *value, long vlen)
{
    CHAR16 *ptr;

    ptr = ASCII_to_UCS2(value, (int)vlen);
    StrCat(tmpbuf, ptr);
    FreePool(ptr);

    return 0;
}