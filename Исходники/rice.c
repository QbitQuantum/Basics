void
phRiceSegDel(RICE_SEG *rseg)
{
   if(rseg != NULL) {
      shFree(rseg->len);
      shFree(rseg->blocks);
      shFree(rseg);
   }
}