int __cdecl main()
{
	PVOID address = ULongToPtr(1);
	SIZE_T length = 512;
	NTSTATUS status = ZwAllocateVirtualMemory(GetCurrentProcess(), &address, 0, &length, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	if (NT_SUCCESS(status))
	{
		*static_cast<volatile int*>(ULongToPtr(0)) = 0;
		puts_red(strcpy(static_cast<char*>(ULongToPtr(1)), "null page allocated"));
	}
	else switch (status)
	{
	case STATUS_INVALID_PARAMETER_2:
		puts_green("null page alloc failed (may Windows 8 or MS13-031)");
		break;
	case STATUS_CONFLICTING_ADDRESSES:
		puts_green("null page alloc failed (may EMET)");
		break;
	default:
		printf_red("!ZwAllocateVirtualMemory");
		printf("->0x%lx\n", status);
	}
	return EXIT_SUCCESS;
}