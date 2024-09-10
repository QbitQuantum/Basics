static orxINLINE orxU32 orxMemory_CacheLineSize()
{
  SYSTEM_LOGICAL_PROCESSOR_INFORMATION *astProcessorInfoList;
  orxU32                                u32InfoListSize = 0, u32Result = orxMEMORY_KU32_DEFAULT_CACHE_LINE_SIZE, i, u32Number;

  /* Requests total size of processors info */
  GetLogicalProcessorInformation(0, (PDWORD)&u32InfoListSize);

  /* Allocates info list */
  astProcessorInfoList = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION *)orxMemory_Allocate(u32InfoListSize, orxMEMORY_TYPE_TEMP);

  /* Gets processors info */
  GetLogicalProcessorInformation(astProcessorInfoList, (PDWORD)&u32InfoListSize);

  /* For all processor info */
  for(i = 0, u32Number = u32InfoListSize / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
      i < u32Number;
      i++)
  {
    /* Found first level cache info? */
    if((astProcessorInfoList[i].Relationship == RelationCache)
    && (astProcessorInfoList[i].Cache.Level == 1))
    {
      /* Updates result */
      u32Result = astProcessorInfoList[i].Cache.LineSize;

      break;
    }
  }

  /* Frees info list */
  orxMemory_Free(astProcessorInfoList);

  /* Done! */
  return u32Result;
}