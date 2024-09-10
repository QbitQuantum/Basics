GElf_Phdr*
gelf_getphdr(Elf *elf, int ndx, GElf_Phdr *dst) {
    GElf_Phdr buf;
    char *tmp;
    size_t n;

    if (!elf) {
	return NULL;
    }
    elf_assert(elf->e_magic == ELF_MAGIC);
    tmp = _elf_getphdr(elf, elf->e_class);
    if (!tmp) {
	return NULL;
    }
    if (ndx < 0 || ndx >= elf->e_phnum) {
	seterr(ERROR_BADINDEX);
	return NULL;
    }
    n = _msize(elf->e_class, _elf_version, ELF_T_PHDR);
    if (n == 0) {
	seterr(ERROR_UNIMPLEMENTED);
	return NULL;
    }
    if (!dst) {
	dst = &buf;
    }
    if (elf->e_class == ELFCLASS64) {
	*dst = *(Elf64_Phdr*)(tmp + ndx * n);
    }
    else if (elf->e_class == ELFCLASS32) {
	Elf32_Phdr *src = (Elf32_Phdr*)(tmp + ndx * n);

	check_and_copy(GElf_Word,  dst, src, p_type,   NULL);
	check_and_copy(GElf_Word,  dst, src, p_flags,  NULL);
	check_and_copy(GElf_Off,   dst, src, p_offset, NULL);
	check_and_copy(GElf_Addr,  dst, src, p_vaddr,  NULL);
	check_and_copy(GElf_Addr,  dst, src, p_paddr,  NULL);
	check_and_copy(GElf_Xword, dst, src, p_filesz, NULL);
	check_and_copy(GElf_Xword, dst, src, p_memsz,  NULL);
	check_and_copy(GElf_Xword, dst, src, p_align,  NULL);
    }
    else {
	if (valid_class(elf->e_class)) {
	    seterr(ERROR_UNIMPLEMENTED);
	}
	else {
	    seterr(ERROR_UNKNOWN_CLASS);
	}
	return NULL;
    }
    if (dst == &buf) {
	dst = (GElf_Phdr*)malloc(sizeof(GElf_Phdr));
	if (!dst) {
	    seterr(ERROR_MEM_PHDR);
	    return NULL;
	}
	*dst = buf;
    }
    return dst;
}