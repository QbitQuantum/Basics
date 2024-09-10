NTSTATUS ApfCreateDataSection(PAPFCONTROL *ApfDataSectionPointer)
{
    NTSTATUS Status;
    STRING ApfDataSectionName;
    UNICODE_STRING ApfDataSectionUnicodeName;
    OBJECT_ATTRIBUTES ObjectAttributes;
    LARGE_INTEGER AllocationSize;
    ULONG ViewSize;
    PAPFCONTROL DataSectionPointer;
	
    //
    // Initialize object attributes
    //
    RtlInitString(&ApfDataSectionName, DATA_SEC_NAME);
	
    Status = RtlAnsiStringToUnicodeString(
		&ApfDataSectionUnicodeName,
		&ApfDataSectionName,
		TRUE);

    if (NT_SUCCESS(Status)) {
	InitializeObjectAttributes(
		&ObjectAttributes,
		&ApfDataSectionUnicodeName,
		OBJ_OPENIF | OBJ_CASE_INSENSITIVE,
		NULL,
		&SecDescriptor);
    }
#ifdef ERRORDBG
    else {
	KdPrint (("WAP: RtlAnsiStringToUnicodeString() failed in "
	    "ApfCreateDataSection, %lx\n", Status));
    }
#endif
	
    AllocationSize.HighPart = 0;

    // Need a slot to account for calibration data
    //
    AllocationSize.LowPart = (API_COUNT + 1) * sizeof(APFDATA);
	
    // Create a read-write section
    //
    Status = NtCreateSection(&ApfDataSectionHandle,
		 SECTION_MAP_READ | SECTION_MAP_WRITE,
		 &ObjectAttributes,
		 &AllocationSize,
		 PAGE_READWRITE,
		 SEC_COMMIT,
		 NULL);
    if (NT_SUCCESS(Status)) {
	ViewSize = AllocationSize.LowPart;
	DataSectionPointer = NULL;
		
	// Map the section
	//
	Status = NtMapViewOfSection(ApfDataSectionHandle,
			MyProcess,
			(PVOID *)&DataSectionPointer,
			0,
			AllocationSize.LowPart,
			NULL,
			&ViewSize,
			ViewUnmap,
			0L,
			PAGE_READWRITE);
#ifdef ERRORDBG
    	if (!NT_SUCCESS(Status)) {
	    KdPrint (("WAP: NtMapViewOfSection() failed in ApfCreateDataSection,"
		" %lx\n", Status));
        }
#endif
	*ApfDataSectionPointer = DataSectionPointer;
    }
#ifdef ERRORDBG
    else {
	KdPrint (("WAP: NtCreateSection() failed in ApfCreateDataSection "
	    "%lx\n", Status));
    }
#endif
	
    return(Status);

} /* ApfCreateDataSection () */