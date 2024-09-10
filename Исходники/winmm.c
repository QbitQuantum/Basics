/**************************************************************************
 * 				auxGetDevCapsA		[WINMM.@]
 */
UINT WINAPI auxGetDevCapsA(UINT_PTR uDeviceID, LPAUXCAPSA lpCaps, UINT uSize)
{
    AUXCAPSW	acW;
    UINT	ret;

    if (lpCaps == NULL)        return MMSYSERR_INVALPARAM;

    ret = auxGetDevCapsW(uDeviceID, &acW, sizeof(acW));

    if (ret == MMSYSERR_NOERROR) {
	AUXCAPSA acA;
	acA.wMid           = acW.wMid;
	acA.wPid           = acW.wPid;
	acA.vDriverVersion = acW.vDriverVersion;
	WideCharToMultiByte( CP_ACP, 0, acW.szPname, -1, acA.szPname,
                             sizeof(acA.szPname), NULL, NULL );
	acA.wTechnology    = acW.wTechnology;
	acA.dwSupport      = acW.dwSupport;
	memcpy(lpCaps, &acA, min(uSize, sizeof(acA)));
    }
    return ret;
}