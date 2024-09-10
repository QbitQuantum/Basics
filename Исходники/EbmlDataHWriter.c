void Ebml_Serialize(EbmlGlobal *glob, const void *buffer_in, unsigned long len)
{
    //assert(buf);

    const unsigned char *const p = (const unsigned char *)(buffer_in);
    const unsigned char *const q = p + len;

    _Serialize(glob, p, q);
}