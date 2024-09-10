BOOL
NTAPI
RtlLargeStringToUnicodeString( PUNICODE_STRING DestinationString,
                               PLARGE_STRING SourceString)
{
  ANSI_STRING AnsiString;

  RtlInitUnicodeString(DestinationString, NULL);
  if (DestinationString && SourceString && SourceString->bAnsi)
  {
     RtlInitAnsiString(&AnsiString, (LPSTR)SourceString->Buffer);
     return NT_SUCCESS(RtlAnsiStringToUnicodeString(DestinationString, &AnsiString, TRUE));
  }
  else if (DestinationString && SourceString)
  {
     return RtlCreateUnicodeString(DestinationString, SourceString->Buffer);
  }
  else
     return FALSE;
}