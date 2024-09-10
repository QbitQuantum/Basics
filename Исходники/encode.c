VOID NTAPI
RtlRunEncodeUnicodeString (IN OUT PUCHAR Hash,
                           IN OUT PUNICODE_STRING String)
{
   LARGE_INTEGER CurrentTime;
   PUCHAR ptr;
   USHORT i;
   NTSTATUS Status;

   ptr = (PUCHAR) String->Buffer;
   if (*Hash == 0)
   {
      Status = NtQuerySystemTime (&CurrentTime);
      if (NT_SUCCESS(Status))
      {
         for (i = 1; i < sizeof(LARGE_INTEGER) && (*Hash == 0); i++)
            *Hash |= *(PUCHAR)(((PUCHAR)&CurrentTime) + i);
      }

      if (*Hash == 0)
         *Hash = 1;
   }

   if (String->Length >= 1)
   {
      ptr[0] ^= (*Hash) | (UCHAR)0x43;
      if (String->Length > 1)
      {
         for (i = 1; i < String->Length; i++)
         {
            ptr[i] ^= ptr[i - 1] ^ (*Hash);
         }
      }
   }
}