static void function1 (struct _file_ * file, signed index, flag_t flags) 

{
	static signed image = 0;
	static uint32_t offset = 0;
	struct nvm_header1 nvm_header;
	if (read (file->file, &nvm_header, sizeof (nvm_header)) != sizeof (nvm_header)) 
	{
		error (1, errno, NVM_HDR_CANTREAD, file->name, image);
	}
	if (LE32TOH (nvm_header.HEADERVERSION) != 0x60000000) 
	{
		error (1, 0, NVM_HDR_VERSION, file->name, image);
	}
	if (checksum32 (&nvm_header, sizeof (nvm_header), 0)) 
	{
		error (1, 0, NVM_HDR_CHECKSUM, file->name, image);
	}
	if (nvm_header.NEXTHEADER) 
	{
		error (1, 0, NVM_HDR_LINK, file->name, image);
	}
	if (index) 
	{
		offset += sizeof (nvm_header);
		offset += LE32TOH (nvm_header.IMAGELENGTH);
		nvm_header.NEXTHEADER = HTOLE32 (offset);
	}
	nvm_header.HEADERCHECKSUM = 0;
	nvm_header.HEADERCHECKSUM = checksum32 (&nvm_header, sizeof (nvm_header), 0);
	if (write (STDOUT_FILENO, &nvm_header, sizeof (nvm_header)) != sizeof (nvm_header)) 
	{
		error (1, errno, NVM_HDR_CANTSAVE, file->name, image);
	}
	copyimage (file, LE32TOH (nvm_header.IMAGELENGTH), image);
	return;
}