void __fastcall TVersionInfo::InitializeTranslationTable(void)
{
  #pragma pack(push, 1)
    union TTranslationTableEntry
    {
      struct struct_Codes
      {
        WORD LanguageCode;
        WORD CharsetCode;
      } Codes;

      DWORD RawData;
	};
  #pragma pack(pop)

  void *xlatebuffer;
  unsigned int BufferLength = 0;

  UnicodeString TempString;

  QueryValue(L"\\VarFileInfo\\Translation",xlatebuffer, BufferLength);
  TTranslationTableEntry* ATranslationTableEntry;
  ATranslationTableEntry = static_cast<TTranslationTableEntry*>(xlatebuffer);
  // We assume that the translation table is stored correctly;
  // the operating system provides no other means to retrieve
  // the count of items, so dividing table size by
  // sizeof(table entry) is the only means to achieve this.
  assert(BufferLength % sizeof(TTranslationTableEntry) == 0);

  while (BufferLength != 0)
  {
    TempString = L"";
	TempString.sprintf(L"%.4X%.4X", ATranslationTableEntry->Codes.LanguageCode,
                                  ATranslationTableEntry->Codes.CharsetCode);

    FTranslations->AddObject(TempString, reinterpret_cast<TObject*>(ATranslationTableEntry->RawData));

    ATranslationTableEntry++;
    BufferLength = BufferLength - sizeof(TTranslationTableEntry);
  }

  if ((FTranslations->Count == 0) && FHasVersionInfo)
  {
    // Interestingly, there was *NO* translation
    // data stored inside the buffer - for whatever
    // reason there might be.
    // The operating system mandates a language-charset
    // identifier, though, when it comes to querying
    // for string data.
    // Resolution: create a fake entry which is
    //             language-neutral and which uses
    //             the Unicode charset.

    TTranslationTableEntry TranslationCode;
    TranslationCode.Codes.LanguageCode = MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL);
    TranslationCode.Codes.CharsetCode = 0x04b0; // Unicode

    TempString = L"";
	TempString.sprintf(L"%.4X%.4X", TranslationCode.Codes.LanguageCode,
                                  TranslationCode.Codes.CharsetCode );

    FTranslations->AddObject(TempString, reinterpret_cast<TObject*>(TranslationCode.RawData));
  }

  // By default pick the first language-charset entry
  // for display / analysis.
  FLanguageCharsetIndex = 0;
}