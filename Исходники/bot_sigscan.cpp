bool CSignatureFunction::getLibraryInfo(const void *libPtr, DynLibInfo &lib)
{
	uintptr_t baseAddr;

	if (libPtr == NULL)
	{
		return false;
	}

#ifdef _WIN32


	MEMORY_BASIC_INFORMATION info;
	IMAGE_DOS_HEADER *dos;
	IMAGE_NT_HEADERS *pe;
	IMAGE_FILE_HEADER *file;
	IMAGE_OPTIONAL_HEADER *opt;

	if (!VirtualQuery(libPtr, &info, sizeof(MEMORY_BASIC_INFORMATION)))
	{
		return false;
	}

	baseAddr = reinterpret_cast<uintptr_t>(info.AllocationBase);

	// All this is for our insane sanity checks :o 
	dos = reinterpret_cast<IMAGE_DOS_HEADER *>(baseAddr);
	pe = reinterpret_cast<IMAGE_NT_HEADERS *>(baseAddr + dos->e_lfanew);
	file = &pe->FileHeader;
	opt = &pe->OptionalHeader;

	// Check PE magic and signature 
	if (dos->e_magic != IMAGE_DOS_SIGNATURE || pe->Signature != IMAGE_NT_SIGNATURE || opt->Magic != IMAGE_NT_OPTIONAL_HDR32_MAGIC)
	{
		return false;
	}

	// Check architecture, which is 32-bit/x86 right now
		// Should change this for 64-bit if Valve gets their act together
	
	if (file->Machine != IMAGE_FILE_MACHINE_I386)
	{
		return false;
	}

	//For our purposes, this must be a dynamic library 
	if ((file->Characteristics & IMAGE_FILE_DLL) == 0)
	{
		return false;
	}

	//Finally, we can do this
	lib.memorySize = opt->SizeOfImage;

#else
	Dl_info info;
	Elf32_Ehdr *file;
	Elf32_Phdr *phdr;
	uint16_t phdrCount;

	if (!dladdr(libPtr, &info))
	{
		return false;
	}

	if (!info.dli_fbase || !info.dli_fname)
	{
		return false;
	}

	// This is for our insane sanity checks :o 
	baseAddr = reinterpret_cast<uintptr_t>(info.dli_fbase);
	file = reinterpret_cast<Elf32_Ehdr *>(baseAddr);

	// Check ELF magic 
	if (memcmp(ELFMAG, file->e_ident, SELFMAG) != 0)
	{
		return false;
	}

	// Check ELF version 
	if (file->e_ident[EI_VERSION] != EV_CURRENT)
	{
		return false;
	}

	// Check ELF architecture, which is 32-bit/x86 right now
		// Should change this for 64-bit if Valve gets their act together
		
	if (file->e_ident[EI_CLASS] != ELFCLASS32 || file->e_machine != EM_386 || file->e_ident[EI_DATA] != ELFDATA2LSB)
	{
		return false;
	}

	// For our purposes, this must be a dynamic library/shared object 
	if (file->e_type != ET_DYN)
	{
		return false;
	}

	phdrCount = file->e_phnum;
	phdr = reinterpret_cast<Elf32_Phdr *>(baseAddr + file->e_phoff);

	for (uint16_t i = 0; i < phdrCount; i++)
	{
		Elf32_Phdr &hdr = phdr[i];

		// We only really care about the segment with executable code 
		if (hdr.p_type == PT_LOAD && hdr.p_flags == (PF_X|PF_R))
		{
			// From glibc, elf/dl-load.c:
			// c->mapend = ((ph->p_vaddr + ph->p_filesz + GLRO(dl_pagesize) - 1) 
			//             & ~(GLRO(dl_pagesize) - 1));
			//
			// In glibc, the segment file size is aligned up to the nearest page size and
			// added to the virtual address of the segment. We just want the size here.
			
			lib.memorySize = PAGE_ALIGN_UP(hdr.p_filesz);
			break;
		}
	}
#endif

	lib.baseAddress = reinterpret_cast<void *>(baseAddr);

	return true;
}