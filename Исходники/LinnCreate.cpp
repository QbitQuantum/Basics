le32 LinnCreate::createInode(char *inputFile, struct stat *st)
{
    LinnGroup *group;
    LinnInode *inode;
    BitArray inodeMap(super->inodesPerGroup);
    u32 gn, in;

    /* Loop all available LinnGroups. */
    for (gn = 0; gn < LINN_GROUP_COUNT(super); gn++)
    {
	/* Point to the correct LinnGroup. */
	group = BLOCKPTR(LinnGroup, super->groupsTable) + gn;
	
	/* Does it have any free inodes? */
	if (!group->freeInodesCount)
	{
	    group = ZERO;
	    continue;
	}
	else
	    break;
    }
    /* Did we find an appropriate group? */
    if (!group)
    {
	printf("%s: no free inode available for `%s'\n",
		prog, inputFile);
	exit(EXIT_FAILURE);
    }
    /* Find an empty inode number. */
    inodeMap.setArray(BLOCKPTR(u8, group->inodeMap),
		    super->inodesPerGroup);
    in = inodeMap.setNext();

    /* Instantiate the inode. */
    inode = createInode(in, FILETYPE_FROM_ST(st),
			    FILEMODE_FROM_ST(st), st->st_uid, st->st_gid);

    /* Insert file contents. */
    if (S_ISREG(st->st_mode))
    {
	insertFile(inputFile, inode, st);
    }
    /* Debug out. */
    if (verbose)
    {
	printf("%s inode=%u size=%u\n", inputFile, in, inode->size);
    }
    return in;
}