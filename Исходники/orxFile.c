/** Inits the File Module
 */
orxSTATUS orxFASTCALL orxFile_Init()
{
  orxSTATUS eResult = orxSTATUS_SUCCESS;

  /* Was not already initialized? */
  if(!(sstFile.u32Flags & orxFILE_KU32_STATIC_FLAG_READY))
  {
    /* Cleans static controller */
    orxMemory_Zero(&sstFile, sizeof(orxFILE_STATIC));

#ifdef __orxWINDOWS__

    /* Increases C runtime stdio limit */
    _setmaxstdio(2048);

#endif /* __orxWINDOWS__ */

    /* Updates status */
    sstFile.u32Flags |= orxFILE_KU32_STATIC_FLAG_READY;
  }

  /* Done! */
  return eResult;
}