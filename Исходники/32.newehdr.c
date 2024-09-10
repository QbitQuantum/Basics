static char*
_elf_newehdr(Elf *elf, unsigned cls) {
    size_t size;

    if (!elf) {
	return NULL;
    }
    elf_assert(elf->e_magic == ELF_MAGIC);
    if (elf->e_readable) {
	return _elf_getehdr(elf, cls);
    }
    else if (!elf->e_ehdr) {
	size = _msize(cls, _elf_version, ELF_T_EHDR);
	elf_assert(size);
	if ((elf->e_ehdr = (char*)malloc(size))) {
	    memset(elf->e_ehdr, 0, size);
	    elf->e_free_ehdr = 1;
	    elf->e_ehdr_flags |= ELF_F_DIRTY;
	    elf->e_kind = ELF_K_ELF;
	    elf->e_class = cls;
	    return elf->e_ehdr;
	}
	seterr(ERROR_MEM_EHDR);
    }
    else if (elf->e_class != cls) {
	seterr(ERROR_CLASSMISMATCH);
    }
    else {
	elf_assert(elf->e_kind == ELF_K_ELF);
	return elf->e_ehdr;
    }
    return NULL;
}