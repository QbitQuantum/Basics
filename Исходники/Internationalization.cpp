int32 FInternationalization::GetCultureIndex(const FString& Name)
{
#if UE_ENABLE_ICU
	static const int32 MaximumNameLength = 64;
	const int32 NameLength = Name.Len();
	check(NameLength < MaximumNameLength);
	char CanonicalName[MaximumNameLength];

	UErrorCode ICUStatus = U_ZERO_ERROR;
	uloc_canonicalize(TCHAR_TO_ANSI( *Name ), CanonicalName, MaximumNameLength, &ICUStatus);
#endif	

	const int32 CultureCount = AllCultures.Num();
	int32 i;
	for (i = 0; i < CultureCount; ++i)
	{
#if UE_ENABLE_ICU
		if( AllCultures[i]->GetName() == CanonicalName )
#else
		if( AllCultures[i]->GetName() == Name )
#endif
		{
			break;
		}
	}
	if(i >= CultureCount)
	{
		i = -1;
	}
	return i;
}