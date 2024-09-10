VOID
ConditionSetValue(
	IN ConditionDataType Type,
	IN PWSTR StringValue,
	IN PCONDITION_ENTRY Entry
	)
{
	switch (Type) {

		case ConditionDataUlong:
			Entry->UlongValue = (ULONG)wcstol(StringValue, NULL, 16);
			break;

		case ConditionDataUlong64:
			Entry->Ulong64Value = (ULONG)_wcstoui64(StringValue, NULL, 16);
			break;

		case ConditionDataDouble:
		case ConditionDataString:
			StringCchCopy(Entry->StringValue, MAX_PATH, StringValue);
			break;

		default:
			StringCchCopy(Entry->StringValue, MAX_PATH, StringValue);
	}	
}