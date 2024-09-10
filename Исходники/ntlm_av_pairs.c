void ntlm_get_target_computer_name(PUNICODE_STRING pName, COMPUTER_NAME_FORMAT type)
{
	char* name;
	DWORD nSize = 0;

	GetComputerNameExA(type, NULL, &nSize);
	name = malloc(nSize);
	GetComputerNameExA(type, name, &nSize);

	if (type == ComputerNameNetBIOS)
		CharUpperA(name);

	pName->Length = strlen(name) * 2;
	pName->Buffer = (PWSTR) malloc(pName->Length);
	MultiByteToWideChar(CP_ACP, 0, name, strlen(name),
			(LPWSTR) pName->Buffer, pName->Length / 2);

	pName->MaximumLength = pName->Length;

	free(name);
}