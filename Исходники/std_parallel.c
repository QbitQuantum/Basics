void NS_DIM_PREFIX BElementScatterBndS (BNDS **bnds, int n, int cnt, char *data)
{
  INT size,i;
  BNDS *bs;

  memcpy(&i,data,sizeof(INT));
  while (i != -1)
  {
    data += CEIL(sizeof(INT));
    bs = (BNDS *) data;
    size = BND_SIZE(bs);

    PRINTDEBUG(dom,1,("BElementScatterBndS(): %d me %d\n",i,size));

    if (bnds[i] == NULL)
    {
      bs = (BNDS *) memmgr_AllocOMEM((size_t)size,TypeBndS,0,0);
      memcpy(bs,data,size);
      bnds[i] = bs;
    }
    data += CEIL(size);
    memcpy(&i,data,sizeof(INT));
  }
}