BOOL CreatePrivateExponentOneKey(LPTSTR szProvider, 
                                 DWORD dwProvType,
                                 LPTSTR szContainer,
                                 DWORD dwKeySpec,
                                 HCRYPTPROV *hProv, 
                                 HCRYPTKEY *hPrivateKey)
{
   BOOL fReturn = FALSE;
   BOOL fResult;
   int n;
   LPBYTE keyblob = NULL;
   DWORD dwkeyblob;
   DWORD dwBitLen;
   BYTE *ptr;

   __try
   {
      *hProv = 0;
      *hPrivateKey = 0;

      if ((dwKeySpec != AT_KEYEXCHANGE) && (dwKeySpec != AT_SIGNATURE))  __leave;

      // Try to create new container
      fResult = CryptAcquireContext(hProv, szContainer, szProvider, 
                                    dwProvType, CRYPT_NEWKEYSET);
      if (!fResult)
      {
         // If the container exists, open it
         if (GetLastError() == NTE_EXISTS)
         {
            fResult = CryptAcquireContext(hProv, szContainer, szProvider, dwProvType, 0);
            if (!fResult)
            {
               // No good, leave
               __leave;
            }
         }
         else
         {
            // No good, leave
            __leave;
         }
      }

      // Generate the private key
      fResult = CryptGenKey(*hProv, dwKeySpec, CRYPT_EXPORTABLE, hPrivateKey);
      if (!fResult) __leave;

      // Export the private key, we'll convert it to a private
      // exponent of one key
      fResult = CryptExportKey(*hPrivateKey, 0, PRIVATEKEYBLOB, 0, NULL, &dwkeyblob);
      if (!fResult) __leave;      

      keyblob = (LPBYTE)LocalAlloc(LPTR, dwkeyblob);
      if (!keyblob) __leave;

      fResult = CryptExportKey(*hPrivateKey, 0, PRIVATEKEYBLOB, 0, keyblob, &dwkeyblob);
      if (!fResult) __leave;


      CryptDestroyKey(*hPrivateKey);
      *hPrivateKey = 0;

      // Get the bit length of the key
      memcpy(&dwBitLen, &keyblob[12], 4);      

      // Modify the Exponent in Key BLOB format
      // Key BLOB format is documented in SDK

      // Convert pubexp in rsapubkey to 1
      ptr = &keyblob[16];
      for (n = 0; n < 4; n++)
      {
         if (n == 0) ptr[n] = 1;
         else ptr[n] = 0;
      }

      // Skip pubexp
      ptr += 4;
      // Skip modulus, prime1, prime2
      ptr += (dwBitLen/8);
      ptr += (dwBitLen/16);
      ptr += (dwBitLen/16);

      // Convert exponent1 to 1
      for (n = 0; n < (dwBitLen/16); n++)
      {
         if (n == 0) ptr[n] = 1;
         else ptr[n] = 0;
      }

      // Skip exponent1
      ptr += (dwBitLen/16);

      // Convert exponent2 to 1
      for (n = 0; n < (dwBitLen/16); n++)
      {
         if (n == 0) ptr[n] = 1;
         else ptr[n] = 0;
      }

      // Skip exponent2, coefficient
      ptr += (dwBitLen/16);
      ptr += (dwBitLen/16);

      // Convert privateExponent to 1
      for (n = 0; n < (dwBitLen/8); n++)
      {
         if (n == 0) ptr[n] = 1;
         else ptr[n] = 0;
      }
      
      // Import the exponent-of-one private key.      
      if (!CryptImportKey(*hProv, keyblob, dwkeyblob, 0, 0, hPrivateKey))
      {                 
         __leave;
      }

      fReturn = TRUE;
   }
   __finally
   {
      if (keyblob) LocalFree(keyblob);

      if (!fReturn)
      {
         if (*hPrivateKey) CryptDestroyKey(*hPrivateKey);
         if (*hProv) CryptReleaseContext(*hProv, 0);
      }
   }

   return fReturn;
}