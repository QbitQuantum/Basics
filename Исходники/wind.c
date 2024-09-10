// on x86, we dont have the luxury of saving the original ci_Options
// We attempt to guess semi-correct value of the first byte.
// Since x86 has no PatchGuard running (yet?), this needs to be only
// semi-accurate to feign the "secure" kernel status.
static ULONG_PTR guess_ci()
{
	DWORD dw, infoci[2] = { sizeof(infoci) };
	unsigned char infosb[0x18];
	unsigned char infobe[0x20];
	ULONG_PTR ret = 0;
	NTSTATUS status;

	status = NtQuerySystemInformation(SystemCodeIntegrityInformation, &infoci, sizeof(infoci), &dw);
	DBG("QueryCI status %08x", (unsigned)status);
	if (!NT_SUCCESS(status))
		return 0;
	dw = sizeof(infosb);
	status = NtQuerySystemInformation(SystemSecureBootPolicyInformation, &infosb, sizeof(infosb), &dw);
	DBG("QuerySecureBoot status %08x", (int)status);
	if (NT_SUCCESS(status)) {
		dw = sizeof(infobe);
	// 	if ( *(_BYTE *)(v5 + 0x14) & 0x80 )
	// 	{
	//      	LOWORD(v8) = g_CiOptions | 0x20;
	// 		g_CiOptions |= 0x20u;
	// 	}
		status = NtQuerySystemInformation(SystemBootEnvironmentInformation, &infobe, sizeof(infobe), &dw);
		DBG("QueryBootEnv status %08x", (int)status);
		if (NT_SUCCESS(status)) {
			if (infosb[0x14] & 0x80)
				ret |= 0x20;
		}
	}

	DBG("infoci is %d", (int)infoci[1]);
	if (infoci[1] & 1) // enabled
		ret |= 6;
	if (infoci[1] & 2) // testsign
		ret |= 8;

	return ret;
}