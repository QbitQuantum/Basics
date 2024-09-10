void tool_lookup(const vdfastvector<const char *>& args, const vdfastvector<const char *>& switches, bool amd64) {
	if (args.size() < 2)
		help_lookup();

	char *s;
	sint64 addr = _strtoi64(args[1], &s, 16);

	if (*s)
		fail("lookup: invalid address \"%s\"", args[0]);

	vdautoptr<IVDSymbolSource> pss(VDCreateSymbolSourceLinkMap());

	pss->Init(VDTextAToW(args[0]).c_str());

	const VDSymbol *sym = pss->LookupSymbol(addr);

	if (!sym)
		fail("symbol not found for address %08x", addr);

	const char *fn;
	int line;

	if (pss->LookupLine(addr, fn, line))
		printf("%08I64x   %s + %x [%s:%d]\n", addr, sym->name, addr-sym->rva, fn, line);
	else
		printf("%08I64x   %s + %x\n", addr, sym->name, addr-sym->rva);
}