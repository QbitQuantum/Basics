void WriteELF::Write(const vector<uint64_t>& instructions, const DebugInfo& info, const char* filename)
{
	// File name symbol
	{	auto& sym = AddSymbol(filename);
		sym.st_info = (STB_LOCAL<<4) | STT_FILE;
		sym.st_shndx = SHN_ABS;
	}

	const size_t code_size = instructions.size() * sizeof(uint64_t);

	// Code fragment symbol, name = file name
	if (!NoStandardSymbols)
	{	string name = stripextension(strippath(filename));
		replacenonalphanum(name);
		AddGlobalSymbol(name).st_size = code_size;
		// End Symbol
		name.append("_end");
		AddGlobalSymbol(name).st_value = code_size;
		// Size symbol
		name.erase(name.size() - 4);
		name.append("_size");
		auto& sym = AddGlobalSymbol(name);
		sym.st_shndx = SHN_ABS;
		sym.st_value = code_size;
	}

	// Export global symbol table
	for (auto sym : info.GlobalsByName)
	{	auto& value = AddGlobalSymbol(sym.first);
		value.st_value = (Elf32_Addr)sym.second.iValue;
		if (sym.second.Type == V_INT)
			value.st_shndx = SHN_ABS;
	}

	// write header
	WriteRaw(Hdr);
	// write section table
	WriteRaw(Sect0);
	WriteRaw(SectSNST);
	Elf32_Shdr sect = SectCode;
	sect.sh_size = code_size;
	WriteRaw(sect);
	sect = SectSym;
	sect.sh_offset += code_size;
	size_t sym_size = Symbols.size() * sizeof(Elf32_Sym);
	sect.sh_size = sym_size;
	WriteRaw(sect);
	sect = SectSymST;
	sect.sh_offset += code_size + sym_size;
	sect.sh_size = SymbolNames.size() + 1;
	WriteRaw(sect);
	// write section names
	WriteRaw(SNST);
	// write code
	checkedwrite(Target, &instructions.front(), code_size);
	// write symbol table
	checkedwrite(Target, &Symbols.front(), sizeof(Elf32_Sym) * Symbols.size());
	// write symbol names
	checkedwrite(Target, SymbolNames.c_str(), SymbolNames.size() + 1);
}