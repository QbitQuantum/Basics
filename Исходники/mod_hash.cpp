bool mod_hash::lm(wstring * chaine, wstring * hash)
{
	bool status = false;
	UNICODE_STRING maChaine;
	OEM_STRING maDestination;
	BYTE monTab[16];

	RtlInitUnicodeString(&maChaine, chaine->c_str());
	if(NT_SUCCESS(RtlUpcaseUnicodeStringToOemString(&maDestination, &maChaine, TRUE)))
	{
		if(status = NT_SUCCESS(SystemFunction006(maDestination.Buffer, monTab)))
			hash->assign(mod_text::stringOfHex(monTab, sizeof(monTab)));

		RtlFreeOemString(&maDestination);
	}
	return status;
}