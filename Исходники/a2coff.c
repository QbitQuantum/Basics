int
main(int argc, char *argv[])
{
	struct exec head;
	struct ecoff_exechdr ehead;
	struct ecoff_scnhdr escn[3];
	int infd, outfd;
	int n;

	if (argc != 3)
		usage();

	infd = open(argv[1], O_RDONLY);
	if (infd < 0)
		err(1, argv[1]);

	outfd = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (outfd < 0)
		err(1, argv[2]);

	n = read(infd, &head, sizeof(head));
	if (n < sizeof(head))
		err(1, "read");

	if (N_BADMAG(head)) {
		printf("%s: bad magic number\n", argv[1]);
		exit(1);
	}

	if (head.a_trsize || head.a_drsize) {
		printf("%s: has relocations\n", argv[1]);
		exit(1);
	}

	/*
	 * Header
	 */

	ehead.f.f_magic = 0x016d;		/* MC88OMAGIC */
	ehead.f.f_nscns = 3;
	ehead.f.f_timdat = 0;			/* ignored */
	ehead.f.f_symptr = 0;			/* ignored */
	ehead.f.f_nsyms = 0;			/* ignored */
	ehead.f.f_opthdr = sizeof ehead.a;
	ehead.f.f_flags = 0x020f;
		/* F_RELFLG | F_EXEC | F_LNNO | 8 | F_AR16WR */

	ehead.a.magic = N_GETMAGIC(head);
	ehead.a.vstamp = 0;			/* ignored */
	ehead.a.tsize = head.a_text;		/* ignored */
	ehead.a.dsize = head.a_data;		/* ignored */
	ehead.a.bsize = head.a_bss;		/* ignored */
	ehead.a.entry = head.a_entry;
	ehead.a.text_start = N_TXTADDR(head);	/* ignored */
	ehead.a.data_start = N_DATADDR(head);	/* ignored */

	n = write(outfd, &ehead, sizeof(ehead));
	if (n != sizeof(ehead))
		err(1, "write");

	/*
	 * Sections.
	 * Note that we merge .bss into .data since the PROM will not
	 * clear it and locore does not do this either.
	 */

	strncpy(escn[0].s_name, ".text", sizeof escn[0].s_name);
	escn[0].s_paddr = N_TXTADDR(head);	/* ignored, 1:1 mapping */
	escn[0].s_size = round(head.a_text, 8);
	escn[0].s_scnptr = round(sizeof(ehead) + sizeof(escn), 0x10);
	escn[0].s_relptr = 0;
	escn[0].s_lnnoptr = 0;
	escn[0].s_nlnno = 0;
	escn[0].s_flags = 0x20;	/* STYP_TEXT */

	strncpy(escn[1].s_name, ".data", sizeof escn[1].s_name);
	escn[1].s_paddr = N_DATADDR(head);		/* ignored, 1:1 mapping */
	escn[1].s_scnptr = escn[0].s_scnptr + escn[0].s_size;
	escn[1].s_size = round(head.a_data + head.a_bss, 8);
	escn[1].s_relptr = 0;
	escn[1].s_lnnoptr = 0;
	escn[1].s_nlnno = 0;
	escn[1].s_flags = 0x40;	/* STYP_DATA */

	strncpy(escn[2].s_name, ".bss", sizeof escn[2].s_name);
	escn[2].s_paddr = N_BSSADDR(head) + head.a_bss;	/* ignored, 1:1 mapping */
	escn[2].s_scnptr = 0;		/* nothing in the file */
	escn[2].s_size = 0;
	escn[2].s_relptr = 0;
	escn[2].s_lnnoptr = 0;
	escn[2].s_nlnno = 0;
	escn[2].s_flags = 0x80;	/* STYP_BSS */

	/* adjust load addresses */
	escn[0].s_paddr += (head.a_entry & ~(__LDPGSZ - 1)) - __LDPGSZ;
	escn[1].s_paddr += (head.a_entry & ~(__LDPGSZ - 1)) - __LDPGSZ;
	escn[2].s_paddr += (head.a_entry & ~(__LDPGSZ - 1)) - __LDPGSZ;
	escn[0].s_vaddr = escn[0].s_paddr;
	escn[1].s_vaddr = escn[1].s_paddr;
	escn[2].s_vaddr = escn[2].s_paddr;

	n = write(outfd, &escn, sizeof(escn));
	if (n != sizeof(escn))
		err(1, "write");

	/*
	 * Copy text section
	 */

#ifdef DEBUG
	printf("copying %s: source %lx dest %lx size %x\n",
	    escn[0].s_name, N_TXTOFF(head), escn[0].s_scnptr, head.a_text);
#endif
	lseek(outfd, escn[0].s_scnptr, SEEK_SET);
	lseek(infd, N_TXTOFF(head), SEEK_SET);
	copybits(infd, outfd, head.a_text);

	/*
	 * Copy data section
	 */

#ifdef DEBUG
	printf("copying %s: source %lx dest %lx size %x\n",
	    escn[1].s_name, N_DATOFF(head), escn[1].s_scnptr, head.a_data);
#endif
	lseek(outfd, escn[1].s_scnptr, SEEK_SET);
	lseek(infd, N_DATOFF(head), SEEK_SET);
	copybits(infd, outfd, head.a_data);

	/*
	 * ``Copy'' bss section
	 */

#ifdef DEBUG
	printf("copying %s: size %lx\n",
	    escn[2].s_name, round(head.a_data + head.a_bss, 8) - head.a_data);
#endif
	zerobits(outfd, round(head.a_data + head.a_bss, 8) - head.a_data);

	close(infd);
	close(outfd);
	exit(0);
}