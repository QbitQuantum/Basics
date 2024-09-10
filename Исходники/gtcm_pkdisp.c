/* On OSF/1 (Digital Unix), pointers are 64 bits wide; the only exception to this is C programs for which one may
 * specify compiler and link editor options in order to use (and allocate) 32-bit pointers.  However, since C is
 * the only exception and, in particular because the operating system does not support such an exception, the argv
 * array passed to the main program is an array of 64-bit pointers.  Thus the C program needs to declare argv[]
 * as an array of 64-bit pointers and needs to do the same for any pointer it sets to an element of argv[].
 */
int main(int argc, char_ptr_t argv[])
{
	omi_fd	  	fd;
	char		buff[OMI_BUFSIZ], *bptr, *xptr, *end, *chr;
	int		cc, blen, bunches, i, n, len, buf[5], j, rdmr;
	omi_vi		mlen, xlen;
	omi_li		nx;
	omi_si		hlen;
	omi_req_hdr	rh;
	DCL_THREADGBL_ACCESS;

	GTM_THREADGBL_INIT;
	bunches = 0;
	if (argc == 3)
	{
		if (argv[1][0] != '-' || argv[1][1] != 'b' || argv[1][2] != '\0')
		{
			PRINTF("%s: bad command line arguments\n\t%s [ -b ] filename\n",
				argv[0], argv[0]);
			exit(-1);
		} else if (INV_FD_P((fd = open(argv[argc - 1], O_RDONLY))))
		{
			PRINTF("%s: open(\"%s\"): %s\n", argv[0], argv[argc - 1],
				STRERROR(errno));
			exit(-1);
		}
	} else if (argc == 2)
	{
		if (argv[1][0] == '-' && argv[1][1] == 'b' && argv[1][2] == '\0')
			fd = fileno(stdin);
		else if (INV_FD_P((fd = open(argv[argc - 1], O_RDONLY))))
		{
			PRINTF("%s: open(\"%s\"): %s\n", argv[0], argv[argc - 1],
				STRERROR(errno));
			exit(-1);
		}
	}
	else if (argc == 1)
		fd = fileno(stdin);
	else
	{
		PRINTF("%s: bad command line arguments\n\t%s [ -b ] [ filename ]\n", argv[0], argv[0]);
		exit(-1);
	}
	for (blen = 0, bptr = buff, n = 1, rdmr = 1; ; )
	{
		if (rdmr)
		{
			cc = (int)(ARRAYTOP(buff) - &bptr[blen]);
			if ((cc = (int)(read(fd, &bptr[blen], cc))) < 0)
			{
				PRINTF("%s: read(): %s", argv[0], STRERROR(errno));
				exit(-1);
			} else if (cc == 0)
				break;
			blen += cc;
			if (blen < OMI_VI_SIZ)
			{
				if (bptr != buff)
				{
					memmove(buff, bptr, blen);
					bptr = buff;
				}
				continue;
			}
		}
		xptr = bptr;
		OMI_VI_READ(&mlen, xptr);
		if (blen < mlen.value + 4)
		{
			if (bptr != buff)
			{
				memmove(buff, bptr, blen);
				bptr = buff;
			}
			rdmr = 1;
			continue;
		}
		rdmr = 0;
		PRINTF("Message %d, %ld bytes", n, (long)mlen.value);
		if (argc == 3 && bunches)
		{
			OMI_LI_READ(&nx, xptr);
			PRINTF(", %d transactions in bunch", nx.value);
			bptr += OMI_VI_SIZ + OMI_LI_SIZ;
			blen -= OMI_VI_SIZ + OMI_LI_SIZ;
		} else
		{
			nx.value = 1;
			xlen     = mlen;
		}
		puts("");
		for (i = 1; i <= nx.value; i++)
		{
			if (argc == 3 && bunches)
			{
				OMI_VI_READ(&xlen, xptr);
			}
			end = xptr + xlen.value;
			OMI_SI_READ(&hlen, xptr);
			OMI_LI_READ(&rh.op_class, xptr);
			OMI_SI_READ(&rh.op_type, xptr);
			OMI_LI_READ(&rh.user, xptr);
			OMI_LI_READ(&rh.group, xptr);
			OMI_LI_READ(&rh.seq, xptr);
			OMI_LI_READ(&rh.ref, xptr);
			if (rh.op_class.value == 1)
			{
				PRINTF("    %s (%ld bytes)", (omi_oprlist[rh.op_type.value])
				       ? omi_oprlist[rh.op_type.value] : "unknown",(long)xlen.value);
				if (argc == 3 && bunches)
				    PRINTF(", transaction #%d in bunch", i);
				puts("");
			} else
				PRINTF("    (%ld bytes)\n", (long)xlen.value);
			chr  = (char *)buf;
			while (xptr < end)
			{
				fputc('\t', stdout);
				if ((len = (int)(end - xptr)) > 20)
					len = 20;
				memcpy(chr, xptr, len);
				xptr += len;
				for (j = len; j < 20; j++)
					chr[j] = '\0';
				for (j = 0; j < 5; j++)
					PRINTF("%08x ", buf[j]);
				for (j = 0; j < 20; j++)
				{
					if (j >= len)
						chr[j] = ' ';
					else if (chr[j] < 32 || chr[j] > 126)
						chr[j] = '.';
				}
				PRINTF("%20s\n", chr);
			}
			bptr += xlen.value + 4;
			blen -= xlen.value + 4;
		}
		if (argc == 3)
			bunches = 1;
		n++;
	}
	return 0;
}