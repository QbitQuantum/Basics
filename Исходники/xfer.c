/*
** Add the Linker link to the plugin text. The calling
** function must free the returned pointer.
*/
static Char* GetLink(Char* orig_text) {
  UInt16 length = 0;
  Char* linked_text = NULL;
  LinkerCPB command_block;
  UInt32 result;

  /* Bail if there is no text */
  if (!orig_text)
    return 0;

  length = StrLen(orig_text) + 1;
  if (p.flags & PFLAGS_XFER_BACKLINK && d.linker_available) 
    length += 5;

  linked_text = MemPtrNew(length);
  ASSERT(linked_text);
  StrCopy(linked_text, orig_text);

  if (!(p.flags & PFLAGS_XFER_BACKLINK && d.linker_available))
    return linked_text;

  MemSet(&command_block, sizeof(LinkerCPB), 0);
  command_block.creator = 'Linx'; /* maybe this is overkill, but .... */
  command_block.message = LinkerNewLinkMessage;
  /* command_block.linkTag is empty and to be filled by Linker */
  command_block.gotoTargetAppCreator = AppType; /* DiddleBug is the target */
  DmOpenDatabaseInfo(d.dbR, &(command_block.gotoLinkParams.dbID), NULL, NULL,
		     &(command_block.gotoLinkParams.dbCardNo), NULL);
  command_block.gotoLinkParams.recordNum = p.dbI;
  
  /* Signal Linker */
  SysAppLaunch(d.cardNo, d.dbID, 0, linkerAppLaunchCmdSignalLinker,
	       &command_block, &result);

  /* Add the link text */
  command_block.linkTag[5] = 0x00; /* just to be sure */
  StrCat(linked_text, command_block.linkTag);

  return linked_text;
}