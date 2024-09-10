int
printTapeEntry(struct budb_tapeEntry *teptr)
{
    time_t written = teptr->written;
    time_t expires = teptr->expires;

    printf("name = %s\n", teptr->name);
    printf("flags = 0x%x", teptr->flags);
    if (teptr->flags & BUDB_TAPE_TAPEERROR)
	printf(": Error");
    if (teptr->flags & BUDB_TAPE_DELETED)
	printf(": Deleted");
    if (teptr->flags & BUDB_TAPE_BEINGWRITTEN)
	printf(": In progress");
    if (teptr->flags & BUDB_TAPE_ABORTED)
	printf(": Aborted");
    if (teptr->flags & BUDB_TAPE_STAGED)
	printf(": Staged");
    if (teptr->flags & BUDB_TAPE_WRITTEN)
	printf(": Successful");
    printf("\n");
    printf("written = %s", ctime(&written));
    printf("expires = %s", cTIME(&expires));
    printf("kBytes Tape Used = %u\n", teptr->useKBytes);
    printf("nMBytes Data = %d\n", teptr->nMBytes);
    printf("nBytes  Data = %d\n", teptr->nBytes);
    printf("nFiles = %d\n", teptr->nFiles);
    printf("nVolumes = %d\n", teptr->nVolumes);
    printf("seq = %d\n", teptr->seq);
    printf("labelPos = %d\n", teptr->labelpos);
    printf("useCount = %d\n", teptr->useCount);
    printf("dump = %d\n", teptr->dump);
    return 0;
}