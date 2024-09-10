/*
 * Extension: report memory size
 */
size_t
gelf_msize(Elf *elf, Elf_Type type, size_t count, unsigned ver) {
    size_t n;

    if (elf) {
	if (elf->e_kind != ELF_K_ELF) {
	    seterr(ERROR_NOTELF);
	}
	else if (!valid_class(elf->e_class)) {
	    seterr(ERROR_UNKNOWN_CLASS);
	}
	else if (!valid_version(ver)) {
	    seterr(ERROR_UNKNOWN_VERSION);
	}
	else if (!valid_type(type)) {
	    seterr(ERROR_UNKNOWN_TYPE);
	}
	else if (!(n = _msize(elf->e_class, ver, type))) {
	    seterr(ERROR_UNKNOWN_TYPE);
	}
	else {
	    return count * n;
	}
    }
    return 0;
}