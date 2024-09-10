static HGLOBAL gmem_realloc(HGLOBAL *hg, unsigned size)
{
 HGLOBAL hn;
 if (hn = *hg? GlobalReAlloc(*hg, size, loGMEM_FLAG):
               GlobalAlloc(loGMEM_FLAG, size)) *hg = hn;
/* else
   {
    UL_WARNING((LOGID, "%!L gmem_alloc(%u) FAILED", size));
   }*/
 return hn;
}