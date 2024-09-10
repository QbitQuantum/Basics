JNIEXPORT void JNICALL Java_com_microsoft_tfs_jni_internal_filesystem_NativeFileSystem_nativeSetOwner(JNIEnv *env,
	jclass cls, jstring jPath, jstring jOwnerSIDString)
{
    const WCHAR * path= NULL;
    const WCHAR * ownerSIDString = NULL;
    PSID ownerSID = NULL;
    DWORD result = 0;

    if (jPath == NULL)
    {
       	throwRuntimeExceptionString(env, "path must not be null");
		goto cleanup;
    }

	if (jOwnerSIDString == NULL)
	{
		throwRuntimeExceptionString(env, "user must not be null");
		goto cleanup;
	}

    if ((ownerSIDString = javaStringToPlatformChars(env, jOwnerSIDString)) == NULL)
	{
		// String allocation failed, exception already thrown
		goto cleanup;
	}
    
	if (ConvertStringSidToSidW(ownerSIDString, &ownerSID) == FALSE)
	{
		throwRuntimeExceptionCode(env, GetLastError(), "Error converting string %S sid to sid", ownerSIDString);
		goto cleanup;
	}

    if ((path = javaStringToPlatformChars(env, jPath)) == NULL)
	{
		// String allocation failed, exception already thrown
		goto cleanup;
	}

	result = SetNamedSecurityInfoW((WCHAR *) path, SE_FILE_OBJECT, OWNER_SECURITY_INFORMATION, 
		ownerSID, NULL, NULL, NULL);
    if (result != ERROR_SUCCESS)
	{
		throwRuntimeExceptionCode(env, result, "Error getting file security info for %S", path);
		goto cleanup;
	}

cleanup:

	if (ownerSIDString != NULL)
	{
	   releasePlatformChars(env, jOwnerSIDString, ownerSIDString);
	}
	if (path != NULL)
	{
		releasePlatformChars(env, jPath, path);
	}
	if (ownerSID != NULL)
	{
		LocalFree(ownerSID);
	}
}