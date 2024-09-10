int send_whole_file(char cmd, const char *fname, const char *datapth, int quick_read, unsigned long long *bytes, struct cntr *cntr, BFILE *bfd, FILE *fp, const char *extrameta, size_t elen)
{
	int ret=0;
	size_t s=0;
	MD5_CTX md5;
	char buf[4096]="";

	if(!MD5_Init(&md5))
	{
		logp("MD5_Init() failed\n");
		return -1;
	}

	if(extrameta)
	{
		size_t metalen=0;
		const char *metadata=NULL;

		metadata=extrameta;
		metalen=elen;

		// Send metadata in chunks, rather than all at once.
		while(metalen>0)
		{
			if(metalen>ZCHUNK) s=ZCHUNK;
			else s=metalen;

			if(!MD5_Update(&md5, metadata, s))
			{
				logp("MD5_Update() failed\n");
				ret=-1;
			}
			if(async_write(CMD_APPEND, metadata, s))
			{
				ret=-1;
			}

			metadata+=s;
			metalen-=s;

			*bytes+=s;
		}
	}
	else
	{
#ifdef HAVE_WIN32
		if(!ret && cmd==CMD_EFS_FILE)
		{
			struct winbuf mybuf;
			mybuf.md5=&md5;
			mybuf.quick_read=quick_read;
			mybuf.datapth=datapth;
			mybuf.cntr=cntr;
			mybuf.bytes=bytes;
			// The EFS read function, ReadEncryptedFileRaw(),
			// works in an annoying way. You have to give it a
			// function that it calls repeatedly every time the
			// read buffer is called.
			// So ReadEncryptedFileRaw() will not return until
			// it has read the whole file. I have no idea why
			// they do not have a plain 'read()' function for it.

			ReadEncryptedFileRaw((PFE_EXPORT_FUNC)write_efs,
				&mybuf, bfd->pvContext);
		}

		if(!ret && cmd!=CMD_EFS_FILE)
		{
		  while((s=(uint32_t)bread(bfd, buf, 4096))>0)
		  {
			*bytes+=s;
			if(!MD5_Update(&md5, buf, s))
			{
				logp("MD5_Update() failed\n");
				ret=-1;
				break;
			}
			if(async_write(CMD_APPEND, buf, s))
			{
				ret=-1;
				break;
			}
			if(quick_read)
			{
				int qr;
				if((qr=do_quick_read(datapth, cntr))<0)
				{
					ret=-1;
					break;
				}
				if(qr)
				{
					// client wants to interrupt
					break;
				}
			}
		  }
		}
#else
	//printf("send_whole_file: %s\n", fname);
		if(!ret) while((s=fread(buf, 1, 4096, fp))>0)
		{
			*bytes+=s;
			if(!MD5_Update(&md5, buf, s))
			{
				logp("MD5_Update() failed\n");
				ret=-1;
				break;
			}
			if(async_write(CMD_APPEND, buf, s))
			{
				ret=-1;
				break;
			}
			if(quick_read)
			{
				int qr;
				if((qr=do_quick_read(datapth, cntr))<0)
				{
					ret=-1;
					break;
				}
				if(qr)
				{
					// client wants to interrupt
					break;
				}
			}
		}
#endif
	}
	if(!ret)
	{
		unsigned char checksum[MD5_DIGEST_LENGTH+1];
		if(!MD5_Final(checksum, &md5))
		{
			logp("MD5_Final() failed\n");
			return -1;
		}
		return write_endfile(*bytes, checksum);
	}
	return ret;
}