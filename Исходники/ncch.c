int FinaliseNcch(ncch_settings *set)
{
	u8 *ncch = set->out->buffer;

	ncch_hdr *hdr = (ncch_hdr*)ncch;
	u8 *exhdr = (u8*)(ncch + set->cryptoDetails.exhdrOffset);
	u8 *acexDesc = (u8*)(ncch + set->cryptoDetails.acexOffset);
	u8 *logo = (u8*)(ncch + set->cryptoDetails.logoOffset);
	u8 *exefs = (u8*)(ncch + set->cryptoDetails.exefsOffset);
	u8 *romfs = (u8*)(ncch + set->cryptoDetails.romfsOffset);

	// Taking Hashes
	if(set->cryptoDetails.exhdrSize)
		ctr_sha(exhdr,set->cryptoDetails.exhdrSize,hdr->exhdrHash,CTR_SHA_256);
	if(set->cryptoDetails.logoSize)
		ctr_sha(logo,set->cryptoDetails.logoSize,hdr->logoHash,CTR_SHA_256);
	if(set->cryptoDetails.exefsHashDataSize)
		ctr_sha(exefs,set->cryptoDetails.exefsHashDataSize,hdr->exefsHash,CTR_SHA_256);
	if(set->cryptoDetails.romfsHashDataSize)
		ctr_sha(romfs,set->cryptoDetails.romfsHashDataSize,hdr->romfsHash,CTR_SHA_256);

	// Signing NCCH
	int sig_result = Good;
	if(set->options.IsCfa) 
		sig_result = SignCFA(hdr,set->keys);
	else 
		sig_result = SignCXI(hdr,set->keys);
	if(sig_result != Good){
		fprintf(stderr,"[NCCH ERROR] Failed to sign %s header\n",set->options.IsCfa ? "CFA" : "CXI");
		return sig_result;
	}


	// Crypting NCCH\n");
	if(IsNcchEncrypted(hdr)){
		if(!SetNcchKeys(set->keys, hdr)){
			fprintf(stderr,"[NCCH ERROR] Failed to load NCCH AES key\n");
			return -1;
		}

		if(set->options.verbose){
			printf("[NCCH] NCCH AES keys:\n");
			memdump(stdout," > key0: ",set->keys->aes.ncchKey0,AES_128_KEY_SIZE);
			memdump(stdout," > key1: ",set->keys->aes.ncchKey1,AES_128_KEY_SIZE);
		}

		// Crypting Exheader/AcexDesc
		if(set->cryptoDetails.exhdrSize){
			CryptNcchRegion(exhdr,set->cryptoDetails.exhdrSize,0x0,&set->cryptoDetails,set->keys->aes.ncchKey0,ncch_exhdr);
			CryptNcchRegion(acexDesc,set->cryptoDetails.acexSize,set->cryptoDetails.exhdrSize,&set->cryptoDetails,set->keys->aes.ncchKey0,ncch_exhdr);
		}			

		// Crypting ExeFs Files
		if(set->cryptoDetails.exefsSize){
			exefs_hdr *exefsHdr = (exefs_hdr*)exefs;
			for(int i = 0; i < MAX_EXEFS_SECTIONS; i++){
				u8 *key = NULL;
				if(strncmp(exefsHdr->fileHdr[i].name,"icon",8) == 0 || strncmp(exefsHdr->fileHdr[i].name,"banner",8) == 0)
					key = set->keys->aes.ncchKey0;
				else
					key = set->keys->aes.ncchKey1;
								
				u32 offset = u8_to_u32(exefsHdr->fileHdr[i].offset,LE) + sizeof(exefs_hdr);
				u32 size = u8_to_u32(exefsHdr->fileHdr[i].size,LE);

				if(size)
					CryptNcchRegion((exefs+offset),align(size,set->options.blockSize),offset,&set->cryptoDetails,key,ncch_exefs);

			}
			// Crypting ExeFs Header
			CryptNcchRegion(exefs,sizeof(exefs_hdr),0x0,&set->cryptoDetails,set->keys->aes.ncchKey0,ncch_exefs);
		}

		// Crypting RomFs
		if(set->cryptoDetails.romfsSize)
			CryptNcchRegion(romfs,set->cryptoDetails.romfsSize,0x0,&set->cryptoDetails,set->keys->aes.ncchKey1,ncch_romfs);
	}

	return 0;
}