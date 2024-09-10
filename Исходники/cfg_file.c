void update_cfgfile_parameters(struct DirectoryEntry *pDirEnt,unsigned char slot_index)
{
	cfgfile * cfgf;

	readfile(pDirEnt,0,0xc,0xd);

	cfgf=(cfgfile *)&sectorBuffer;
	cfgf->update_cnt++;
	cfgf->slot_index=slot_index;

	writefile(pDirEnt,0,0xc,0xd);

	return;
}