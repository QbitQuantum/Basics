bool COSOperator::getSystemMemory(irr::u32* Total, irr::u32* Avail)
{
#if defined(_IRR_WINDOWS_API_)
	MEMORYSTATUS MemoryStatus;
	MemoryStatus.dwLength = sizeof(MEMORYSTATUS);

	// cannot fail
	GlobalMemoryStatus(&MemoryStatus);

	if (Total)
		*Total = (irr::u32)(MemoryStatus.dwTotalPhys>>10);
	if (Avail)
		*Avail = (irr::u32)(MemoryStatus.dwAvailPhys>>10);
	
	_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
	return true;

#elif defined(_IRR_POSIX_API_) // || defined(MACOSX)
        long ps = sysconf(_SC_PAGESIZE);
        long pp = sysconf(_SC_PHYS_PAGES);
        long ap = sysconf(_SC_AVPHYS_PAGES);
 
	if ((ps==-1)||(pp==-1)||(ap==-1))
		return false;

	if (Total)
		*Total = ((ps*(long long)pp)>>10);
	if (Avail)
		*Avail = ((ps*(long long)ap)>>10);
	return true;
#endif
	// TODO: implement for OSX 
	return false;
}