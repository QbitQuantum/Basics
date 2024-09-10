/*
 * elf to a.out converter for freebsd/sparc64 bootblocks.
 */
int
main(int ac, char **av)
{
	Elf64_Half phentsize;
	Elf64_Half machine;
	Elf64_Half phnum;
	Elf64_Xword filesz;
	Elf64_Xword memsz;
	Elf64_Addr entry;
	Elf64_Off offset;
	Elf64_Off phoff;
	Elf64_Word type;
	unsigned char data;
	struct stat sb;
	struct exec a;
	Elf64_Phdr *p;
	Elf64_Ehdr *e;
	void *v;
	int efd;
	int fd;
	int c;
	int i;

	fd = STDIN_FILENO;
	while ((c = getopt(ac, av, "o:")) != -1)
		switch (c) {
		case 'o':
			if ((fd = open(optarg, O_CREAT|O_RDWR, 0644)) < 0)
				err(1, "%s", optarg);
			break;
		case '?':
		default:
			usage();
		}
	ac -= optind;
	av += optind;
	if (ac == 0)
		usage();

	if ((efd = open(*av, O_RDONLY)) < 0 || fstat(efd, &sb) < 0)
		err(1, NULL);
	v = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, efd, 0);
	if ((e = v) == MAP_FAILED)
		err(1, NULL);

	if (!IS_ELF(*e))
		errx(1, "not an elf file");
	if (e->e_ident[EI_CLASS] != ELFCLASS64)
		errx(1, "wrong class");
	data = e->e_ident[EI_DATA];
	if (data != ELFDATA2MSB && data != ELFDATA2LSB)
		errx(1, "wrong data format");
	if (e->e_ident[EI_VERSION] != EV_CURRENT)
		errx(1, "wrong elf version");
	machine = xe16toh(e->e_machine);
	if (machine != EM_SPARCV9 && machine != EM_ALPHA)
		errx(1, "wrong machine type");
	phentsize = xe16toh(e->e_phentsize);
	if (phentsize != sizeof(*p))
		errx(1, "phdr size mismatch");

	entry = xe64toh(e->e_entry);
	phoff = xe64toh(e->e_phoff);
	phnum = xe16toh(e->e_phnum);
	p = (Elf64_Phdr *)((char *)e + phoff);
	bzero(&a, sizeof(a));
	for (i = 0; i < phnum; i++) {
		type = xe32toh(p[i].p_type);
		switch (type) {
		case PT_LOAD:
			if (a.a_magic != 0)
				errx(1, "too many loadable segments");
			filesz = xe64toh(p[i].p_filesz);
			memsz = xe64toh(p[i].p_memsz);
			offset = xe64toh(p[i].p_offset);
			a.a_magic = htoxe32(A_MAGIC);
			a.a_text = htoxe32(filesz);
			a.a_bss = htoxe32(memsz - filesz);
			a.a_entry = htoxe32(entry);
			if (write(fd, &a, sizeof(a)) != sizeof(a) ||
			    write(fd, (char *)e + offset, filesz) != (ssize_t)filesz)
				err(1, NULL);
			break;
		default:
			break;
		}
	}

	return (0);
}