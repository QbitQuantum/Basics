OVR_PUBLIC_FUNCTION(void) ovr_GetLastErrorInfo(ovrErrorInfo* errorInfo)
{
	const char* error = VR_GetVRInitErrorAsEnglishDescription(g_InitError);
	strncpy_s(errorInfo->ErrorString, error, sizeof(ovrErrorInfo::ErrorString));
	errorInfo->Result = REV_InitErrorToOvrError(g_InitError);
}