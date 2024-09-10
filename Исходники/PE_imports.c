struct PE_get_imports_info* PE_get_imports (LOADED_IMAGE *im)
{
	struct PE_get_imports_info* rt=DMALLOC(struct PE_get_imports_info, 1, "struct PE_get_imports_info");
	bool PE32_plus=PE_is_PE32(im);
	rt->start_RVA=PE_get_import_descriptor_RVA(im, PE32_plus);
	IMAGE_IMPORT_DESCRIPTOR* import_dir=PE_get_import_descriptor(im, PE32_plus);

	if (import_dir==NULL)
	{
		free(rt);
		return NULL; // No imports
	};

	rt->import_descriptors_t=PE_count_import_descriptors (im);
	rt->dlls=DMALLOC(struct PE_get_imports_DLL_info, rt->import_descriptors_t, 
			"struct PE_get_imports_DLL_info");

	int j;
	IMAGE_IMPORT_DESCRIPTOR *i;
	for (i=import_dir, j=0; i->OriginalFirstThunk; i++, j++)
	{
		address* OriginalFirstThunk_a=(address*)ImageRvaToVa (im->FileHeader, im->MappedAddress, i->OriginalFirstThunk, NULL);
		char* name=(char*)ImageRvaToVa (im->FileHeader, im->MappedAddress, i->Name, NULL);
		struct PE_get_imports_DLL_info* DLL=rt->dlls+j;
		DLL->DLL_name=DSTRDUP(name,"char*");
		DLL->FirstThunk=i->FirstThunk;
		DLL->allocate_thunks=false;

		DLL->symbols_t=NULL_terminated_array_of_pointers_size((void**)OriginalFirstThunk_a);
		DLL->symbols=DMALLOC(char*, DLL->symbols_t, "char*");
		DLL->hints=DMALLOC(wyde, DLL->symbols_t, "wyde");
		
		for (address *s=OriginalFirstThunk_a, si=0; *s; s++, si++)
		{
			if (IS_SET(*s, REG_MSB))
			{
				DLL->hints[si]=(*s)&0xFFFF;
				DLL->symbols[si]=NULL;
			}
			else
			{
				byte *tmp=(byte*)ImageRvaToVa(im->FileHeader, im->MappedAddress, *s, NULL);
				DLL->hints[si]=*(wyde*)tmp;
				DLL->symbols[si]=DSTRDUP ((char*)(tmp+2), "symbol name");
			};
		};
	};

	return rt;
};