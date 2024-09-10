bool StandardEncryption::EncryptFile(PCHAR szSource, PCHAR szDestination, PCHAR szPassword, bool bEncrypt) {
	//-------------------------------------------------------------------
	// Parameters passed are:
	//  szSource, the name of the input, a plaintext file.
	//  szDestination, the name of the output, an encrypted file to be 
	//   created.
	//  szPassword, either NULL if a password is not to be used or the 
	//   string that is the password.
	//-------------------------------------------------------------------
	// Declare and initialize local variables.

	FILE *hSource; 
	FILE *hDestination; 

	HCRYPTPROV hCryptProv; 
	HCRYPTKEY hKey;
	HCRYPTKEY hXchgKey; 
	HCRYPTHASH hHash; 

	PBYTE pbKeyBlob; 
	DWORD dwKeyBlobLen; 

	PBYTE pbBuffer; 
	DWORD dwBlockLen; 
	DWORD dwBufferLen; 
	DWORD dwCount; 
 
	unsigned long ltemp = 0;

	char szSpeed[SIZE_STRING];
	char szAverage[SIZE_STRING];
	
	//-------------------------------------------------------------------
	// Open source file. 

	if(hSource = fopen(szSource,"rb")) {
	   //printf("The source plaintext file, %s, is open. \n", szSource);
	} else {
	   MyHandleError("Error opening source plaintext file!");
	   return false;
	} 
	//-------------------------------------------------------------------
	// Open destination file. 

	if(hDestination = fopen(szDestination,"wb")) {
		 //printf("Destination file %s is open. \n", szDestination);
	} else {
		MyHandleError("Error opening destination ciphertext file!"); 
		return false;
	}
	// Get the handle to the default provider. 
	if(CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_AES , CRYPT_VERIFYCONTEXT)) {
	//if(CryptAcquireContext(&hCryptProv, NULL, MS_ENHANCED_PROV, PROV_RSA_FULL , 0)) {
	   //printf("A cryptographic provider has been acquired. \n");
	} else {
	   MyHandleError("Error during CryptAcquireContext!");
	   return false;
	}
	//-------------------------------------------------------------------
	// Create the session key.
	if(!szPassword ) { 
		return false;
	} else { 
		//-------------------------------------------------------------------
		// The file will be encrypted with a session key derived from a
		// password.
		// The session key will be recreated when the file is decrypted
		// only if the password used to create the key is available.

		//-------------------------------------------------------------------
		// Create a hash object. 
		if(CryptCreateHash(hCryptProv, CALG_MD5, 0, 0, &hHash)) {
			//printf("A hash object has been created. \n");
		} else { 
			 MyHandleError("Error during CryptCreateHash!");
			 return false;
		}

		//-------------------------------------------------------------------
		// Hash the password.
		if(CryptHashData(hHash, (BYTE *)szPassword, strlen(szPassword), 0)) {
			//printf("The password has been added to the hash. \n");
		} else {
			MyHandleError("Error during CryptHashData."); 
			return false;
		}

		//-------------------------------------------------------------------
		// Derive a session key from the hash object. 
		if(CryptDeriveKey(hCryptProv, ENCRYPT_ALGORITHM, hHash, KEYLENGTH, &hKey)) {
			//printf("An encryption key is derived from the password hash. \n"); 
		} else {
			MyHandleError("Error during CryptDeriveKey!");
			return false;
		}
		//-------------------------------------------------------------------
		// Destroy hash object. 
		if(hHash) {
			if(!(CryptDestroyHash(hHash))) {
			   MyHandleError("Error during CryptDestroyHash"); 
			   return false;
			}
			hHash = 0;
		}
	} 

	//-------------------------------------------------------------------
	// The session key is now ready. If it is not a key derived from a 
	// password, the session key encrypted with the encrypter's private 
	// key has been written to the destination file.
	 
	//-------------------------------------------------------------------
	// Determine the number of bytes to encrypt at a time. 
	// This must be a multiple of ENCRYPT_BLOCK_SIZE.
	// ENCRYPT_BLOCK_SIZE is set by a #define statement.

	dwBlockLen = 1000 - 1000 % ENCRYPT_BLOCK_SIZE; 

	//-------------------------------------------------------------------
	// Determine the block size. If a block cipher is used, 
	// it must have room for an extra block. 

	if(ENCRYPT_BLOCK_SIZE > 1) 
		dwBufferLen = dwBlockLen + ENCRYPT_BLOCK_SIZE; 
	else 
		dwBufferLen = dwBlockLen; 
    
	//-------------------------------------------------------------------
	// Allocate memory. 
	if(pbBuffer = (BYTE *)malloc(dwBufferLen)) {
		//printf("Memory has been allocated for the buffer. \n");
	} else { 
		MyHandleError("Out of memory."); 
		return false;
	}
	
	// Write / Read the header information from the file.
	// If we are encrypting then we need to write header information
	// if decrypting we need to skip past the header information providing
	// header information exists.
	
	if (bEncrypt == true) {
		fwrite (&m_lMagicone, 1, sizeof (unsigned long), hDestination);
		fwrite (&m_lMagictwo, 1, sizeof (unsigned long), hDestination);
		fwrite (&m_lMagicthree, 1, sizeof (unsigned long), hDestination);
		fwrite (&m_lMagicfour, 1, sizeof (unsigned long), hDestination);
	} else {
		ltemp = 0;
		fread (&ltemp, 1, sizeof (unsigned long), hSource);
		fread (&ltemp, 1, sizeof (unsigned long), hSource);
		fread (&ltemp, 1, sizeof (unsigned long), hSource);
		fread (&ltemp, 1, sizeof (unsigned long), hSource);
	}

	//-------------------------------------------------------------------
	// In a do loop, encrypt the source file, 
	// and write to the source file. 
	m_lastprogressvalue = 0;
	m_bmaxprogressredone = false;
	m_ispeedtrigger = 0;
	unsigned long ltimereading = 0;
	unsigned long long lbytesreading = 0;
	int ispeed = 0;
	int iaverage = 0;
	m_lastbytesreading = 0;
	m_lasttimereading = 0;
	do 
	{ 
		//-------------------------------------------------------------------
		// Read up to dwBlockLen bytes from the source file. 
		dwCount = fread(pbBuffer, 1, dwBlockLen, hSource); 
		if(ferror(hSource)) { 
			MyHandleError("Error reading plaintext!");
			return false;
		}
	 
		//-------------------------------------------------------------------
		// Encrypt / Decrypt data.
		if (bEncrypt == true) {
			if(!CryptEncrypt(hKey, 0, feof(hSource), 0, pbBuffer, &dwCount, dwBufferLen)) {
			   MyHandleError("Error during Encrypt.");
			   return false;
			}		
		} else {
			if(!CryptDecrypt(hKey, 0, feof(hSource), 0, pbBuffer, &dwCount)) {
			   MyHandleError("Error during Decrypt.");
			   return false;
			}
		}

		//-------------------------------------------------------------------
		// Write data to the destination file. 
		fwrite(pbBuffer, 1, dwCount, hDestination); 
		ltotalbytesprocessed+=dwCount;

		//OutputInt ("ltotalprocessed: ", ltotalbytesprocessed);
		int idivvalue = 1000;

		if (ltotalbytes > 0 && ltotalbytes <= 1000) {
			idivvalue = 1;
		}

		if (ltotalbytes > 1000 && ltotalbytes <= 10000) {
			idivvalue = 10;
		}

		if (ltotalbytes > 10000 && ltotalbytes <= 100000) {
			idivvalue = 100;
		}

		if (ltotalbytes > 100000 && ltotalbytes <= 1000000) {
			idivvalue = 1000;
		}

		if (ltotalbytes > 1000000 && ltotalbytes <= 10000000) {
			idivvalue = 10000;
		}

		if (ltotalbytes > 10000000 && ltotalbytes <= 100000000) {
			idivvalue = 100000;
		}

		if (ltotalbytes > 100000000 && ltotalbytes <= 1000000000) {
			idivvalue = 1000000;
		}

		if (ltotalbytes > 1000000000 && ltotalbytes <= 10000000000) {
			idivvalue = 10000000;
		}

		if (ltotalbytes > 10000000000 && ltotalbytes <= 100000000000) {
			idivvalue = 100000000;
		}

		if (ltotalbytes > 100000000000 && ltotalbytes <= 1000000000000) {
			idivvalue = 1000000000;
		}

		if (ltotalbytes > 1000000000000 && ltotalbytes <= 10000000000000) {
			idivvalue = 10000000000;
		}

		if (ltotalbytes > 10000000000000 && ltotalbytes <= 100000000000000) {
			idivvalue = 100000000000;
		}

		if (ltotalbytes > 100000000000000 && ltotalbytes <= 1000000000000000) {
			idivvalue = 1000000000000;
		}


		unsigned int progressvalue = (40000 / (ltotalbytes / idivvalue)) * ((ltotalbytesprocessed) / idivvalue);
		
		//if (m_bmaxprogressredone == false) {
		//	if ((progressvalue-m_lastprogressvalue) > 0) {			
		//		SendMessage(m_hwndprogress, PBM_SETRANGE, 0L, MAKELONG (0, 40000-((progressvalue-m_lastprogressvalue)*20)));
		//		m_bmaxprogressredone = true;
		//		//OutputInt ("max progress now at: ", 40000-((progressvalue-m_lastprogressvalue)*20));
		//	}
		//}
		if (progressvalue != m_lastprogressvalue) {
			//OutputInt ("progressvalue: ", progressvalue);
			SendMessage (m_hwndprogress, PBM_SETPOS, progressvalue, 0L);
		}

		m_lastprogressvalue = progressvalue;

		//m_ispeedtrigger++;
		if ((GetTickCount () - m_lasttickcount) > 100) {
			//m_ispeedtrigger = 0;
			m_lasttickcount = GetTickCount ();
			
			ltimereading = GetTickCount ();
			lbytesreading = ltotalbytesprocessed;


			if ((ltimereading-m_lasttimereading) < 1000) {
				ispeed = (1000000 / ((ltimereading-m_lasttimereading)*1000)) * (ltotalbytesprocessed-m_lastbytesreading);

				ZeroMemory (szSpeed, SIZE_STRING);

				if (ispeed > 0 && ispeed <= 1000) {
					sprintf_s (szSpeed, "Speed: %i Bytes/sec (%i %% complete)", ispeed, ((100*progressvalue) / 40000));
				}

				if (ispeed > 1000 && ispeed <= 1000000) {
					sprintf_s (szSpeed, "Speed: %i KB/sec (%i %% complete)", ispeed / 1000, ((100*progressvalue) / 40000));
				}

				if (ispeed > 1000000) {
					sprintf_s (szSpeed, "Speed: %i MB/sec (%i %% complete)", ispeed / 1000000, ((100*progressvalue) / 40000));
				}
				
				m_addedspeed+=ispeed;
				m_iaveragetrigger++;
				

				if (m_iaveragetrigger > 120) {
					iaverage = m_addedspeed / m_iaveragetrigger;
					
					m_addedspeed = 0;
					m_iaveragetrigger = 0;
					
					ZeroMemory (szAverage, SIZE_STRING);

					if (iaverage > 0 && iaverage <= 1000) {
						if ((((ltotalbytes-ltotalbytesprocessed) / iaverage) / 60) == 0) {
							sprintf_s (szAverage, "      Average Speed: %i Bytes/sec      Time Remaining: Less than a minute", iaverage);
						} else {
							sprintf_s (szAverage, "      Average Speed: %i Bytes/sec      Time Remaining: %i mins", iaverage, ((ltotalbytes-ltotalbytesprocessed) / iaverage) / 60);
						}
						
					}

					if (iaverage > 1000 && iaverage <= 1000000) {
						if ((((ltotalbytes-ltotalbytesprocessed) / iaverage) / 60) == 0) {
							sprintf_s (szAverage, "      Average Speed: %i KB/sec      Time Remaining: Less than a minute",  iaverage / 1000);
						} else {
							sprintf_s (szAverage, "      Average Speed: %i KB/sec      Time Remaining: %i mins", iaverage / 1000, ((ltotalbytes-ltotalbytesprocessed) / iaverage) / 60);
						}
						
					}

					if (iaverage > 1000000) {
						if ((((ltotalbytes-ltotalbytesprocessed) / iaverage) / 60) == 0) {
							sprintf_s (szAverage, "      Average Speed: %i MB/sec      Time Remaining: Less than a minute", iaverage / 1000000);
						} else {
							sprintf_s (szAverage, "      Average Speed: %i MB/sec      Time Remaining: %i mins", iaverage / 1000000, ((ltotalbytes-ltotalbytesprocessed) / iaverage) / 60);
						}
						
					}
					
					ZeroMemory (m_szLastaverage, SIZE_STRING);
					strcpy_s (m_szLastaverage, SIZE_STRING, szAverage);
				}

				strcat_s (szSpeed, SIZE_STRING, m_szLastaverage);

				SetDlgItemText (m_hwndspeed, ID_LBLSPEED, szSpeed);
			} else {
				//SetDlgItemText (m_hwndspeed, ID_LBLSPEED, "Calculating speed...");
			}


			m_lastbytesreading = ltotalbytesprocessed;
			m_lasttimereading = ltimereading;
		}

		if(ferror(hDestination)) { 
			//MyHandleError("Error writing ciphertext.");
			return false;
		}
	}
	while(!feof(hSource)); 
	//-------------------------------------------------------------------
	// End the do loop when the last block of the source file has been
	// read, encrypted, and written to the destination file.

	//-------------------------------------------------------------------
	// Close files.
	//SendMessage (m_hwndprogress, PBM_SETPOS, 40000, 0L);

	if(hSource)
	{
		if(fclose(hSource)) {
			MyHandleError("Error closing source file");
			return false;
		}
			
	}
	if(hDestination)
	{
		if(fclose(hDestination)) {
			MyHandleError("Error closing destination file");
			return false;
		}
			
	}

	//-------------------------------------------------------------------
	// Free memory. 

	if(pbBuffer) {
		free(pbBuffer); 
	}
		 
	 
	//-------------------------------------------------------------------
	// Destroy the session key. 
	if(hKey)
	{
		if(!(CryptDestroyKey(hKey))) {
			MyHandleError("Error during CryptDestroyKey");
			return false;
		}
			
	}

	//-------------------------------------------------------------------
	// Release the provider handle. 

	if(hCryptProv)
	{
		if(!(CryptReleaseContext(hCryptProv, 0))) {
			MyHandleError("Error during CryptReleaseContext");
			return false;
		}
			
	}
	return true;
} // end Encryptfile