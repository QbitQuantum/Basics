U_CFUNC void
ustr_cpy(struct UString *dst,
     const struct UString *src,
     UErrorCode *status)
{
    if(U_FAILURE(*status) || dst == src)
        return;

    if(dst->fCapacity < src->fLength) {
        ustr_resize(dst, ALLOCATION(src->fLength), status);
        if(U_FAILURE(*status))
            return;
    }
    if(src->fChars == NULL || dst->fChars == NULL){
        return;
    }
    u_memcpy(dst->fChars, src->fChars, src->fLength);
    dst->fLength = src->fLength;
    dst->fChars[dst->fLength] = 0x0000;
}