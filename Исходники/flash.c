EFI_STATUS flash(VOID *data, UINTN size, CHAR16 *label)
{
	UINTN i;

#ifndef USER
	/* special case for writing inside esp partition */
	CHAR16 esp[] = L"/ESP/";
	if (!StrnCmp(esp, label, StrLen(esp)))
		return flash_into_esp(data, size, &label[ARRAY_SIZE(esp) - 1]);
#endif
	/* special cases */
	for (i = 0; i < ARRAY_SIZE(LABEL_EXCEPTIONS); i++)
		if (!StrCmp(LABEL_EXCEPTIONS[i].name, label))
			return LABEL_EXCEPTIONS[i].flash_func(data, size);

	return flash_partition(data, size, label);
}