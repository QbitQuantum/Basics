/*
* SfcVerifyFile
*
* Purpose:
*
* Verify file to be legit ZeroAccess signed binary.
*
*/
BOOL SfcVerifyFile(
	_In_ HCRYPTPROV  hProv,
	_In_ HCRYPTKEY hKey,
	_In_ MD5_CTX *ctx,
	_In_ PBYTE Image,
	_In_ DWORD ImageSize
	)
{
	HCRYPTHASH          lh_hash = 0;
	ULONG               CRC, SignSize = 0;
	BYTE                e_sign[128];
	PBYTE               p_resource_sign;
	PIMAGE_NT_HEADERS32 phdr;
	BOOL                bResult = FALSE;
	LDR_RESOURCE_INFO   resInfo;

	phdr = (PIMAGE_NT_HEADERS32)RtlImageNtHeader(Image);
	while (phdr != NULL) {

		resInfo.Type = (ULONG_PTR)RT_RCDATA; //type
		resInfo.Name = 1;           //id
		resInfo.Lang = 0;          //lang

		p_resource_sign = SfLdrQueryResourceDataEx(Image, &resInfo, &SignSize);
		if (p_resource_sign == NULL)
			break;

		if (SignSize != 128)
			break;

		if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &lh_hash))
			break;

		CRC = phdr->OptionalHeader.CheckSum;

		memcpy(e_sign, p_resource_sign, sizeof(e_sign));
		memset(p_resource_sign, 0, sizeof(e_sign));

		phdr->OptionalHeader.CheckSum = 0;

		MD5Update(ctx, Image, ImageSize);

		phdr->OptionalHeader.CheckSum = CRC;
		memcpy(p_resource_sign, e_sign, sizeof(e_sign));

		MD5Final(ctx);

		if (!CryptSetHashParam(lh_hash, HP_HASHVAL, (const BYTE *)&ctx->digest, 0)) {
			CryptDestroyHash(lh_hash);
			break;
		}

		bResult = CryptVerifySignatureW(lh_hash, (const BYTE *)&e_sign, sizeof(e_sign), hKey, 0, 0);
		CryptDestroyHash(lh_hash);
		break;
	}
	return bResult;
}