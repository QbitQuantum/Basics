void MemoryUtils::ForEachSection(void *handle, const std::function<void(const IMAGE_SECTION_HEADER *)>& functor)
{
	IMAGE_NT_HEADERS *pNtHdr = ImageNtHeader(handle);
	auto pSectHdr = (IMAGE_SECTION_HEADER *)(pNtHdr + 1);
	
	int n_sect = pNtHdr->FileHeader.NumberOfSections;
	for (int i = 0; i < n_sect; ++i) {
		functor(pSectHdr);
		++pSectHdr;
	}
}