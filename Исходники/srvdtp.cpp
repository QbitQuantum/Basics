void SrvDTP::sendFile(const char *pathname, uint32_t nslice, uint32_t sindex, uint16_t slicecap)
{
	//cout << endl  << endl << pathname << endl << endl;
	Packet & packet = *(this->ppacket);
	char buf[MAXLINE];
	Database * pdb = psrvPI->getPDB();
	string inode = getInode(pathname);
	std::map<string, string> selectParamMap = {  {"INODE", inode} };
    if (pdb->select("file", selectParamMap))
    {
       vector< map<string ,string> > resultMapVector = pdb->getResult();
       if (!resultMapVector.empty())
       {
       		string dbAccess = resultMapVector[0]["ACCESS"];
       		unsigned long long access = std::stoull(dbAccess) + 1;
       		snprintf(buf, MAXLINE, "%llu", access);
       		dbAccess = buf;

       		std::map<string, string> updateParamMap = { {"ACCESS", dbAccess} };
       		if (pdb->update("file", resultMapVector[0]["ID"], updateParamMap))
			{
				cout << "update ACCESS+1 ok" <<endl;
			} else {
				printf("\033[31mupdate ACCESS+1 error\033[0m\n");
			}

       } else {
          printf("\033[31mINODE not exist\033[0m\n");
       }
    } else {
       Error::msg("\033[31mDatabase select error\033[0m\n");
    }   

	int n;
	//uint32_t nslice =0, sindex = 0;

	// off64_t curpos = sindex * slicecap;
	// if ( lseek64(fileno(psrvPI->getFp()), curpos, SEEK_SET) < 0)
	// {
	// 	packet.sendSTAT_ERR(strerror_r(errno, buf, MAXLINE));
	// 	return;
	// } else {
	// 	printf("Recv file [%s %u/%u] now\n", pathname, sindex, nslice);
	// 	// send STAT_OK
	// 	packet.sendSTAT_OK();
	// }
	
	string sizestr = getFilesize(string(pathname));
	if (sizestr.empty())
	{
		packet.sendSTAT_ERR("getFilesize() failed");
		return;
	}
	// confirm enough space to write on client host
	packet.sendSTAT(STAT_SIZE, sizestr);

	psrvPI->recvOnePacket();
	if (packet.getTagid() == TAG_STAT && packet.getStatid() == STAT_ERR) 
	{
		return;
	} else if (packet.getTagid() == TAG_STAT && packet.getStatid() == STAT_OK)
	{
		;
	} else {
		Error::msg("unknown packet");
		packet.print();
		return;
	}

	//if ( (fp = fopen(pathname, "rb")) == NULL)
	if ( psrvPI->setFp(fopen(pathname, "rb")) == NULL)
	{
		// send STAT_ERR Response
		// GNU-specific strerror_r: char *strerror_r(int errnum, char *buf, size_t buflen);
		packet.sendSTAT_ERR(strerror_r(errno, buf, MAXLINE));
		return;
	} else if ( (n = getFileNslice(pathname, &nslice)) <= 0)  {
		if ( n == 0) {
			printf("EOF[%s]: 0 bytes\n", pathname);
			Fclose(&psrvPI->getFp());
			packet.sendSTAT_OK();
			packet.sendDATA_TEXT(getFileSizeString(pathname));
			packet.sendDATA_FILE(0, 0, 0, NULL);
			packet.sendSTAT_EOF("EOF: 0 bytes");
			return;
		} else if ( n == -2) {
			snprintf(buf, MAXLINE, "Too large file size");
			packet.sendSTAT_ERR(buf);
		} else {
			snprintf(buf, MAXLINE, "File stat error");
			packet.sendSTAT_ERR(buf);
		}
		return;
	} else {
		// send STAT_OK
		packet.sendSTAT_OK();
	}

	packet.sendDATA_TEXT(getFileSizeString(pathname));

	char body[PBODYCAP];
	printf("Send [%s] now\n", pathname);

	while( (n = fread(body, sizeof(char), PBODYCAP, psrvPI->getFp())) >0 )
	{
		packet.sendDATA_FILE(nslice, ++sindex, n, body);
	}
	
	// send EOF
	Fclose(&psrvPI->getFp());
	printf("EOF [%s]\n", pathname);
	packet.sendSTAT_EOF();
}