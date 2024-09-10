/**
 * Creates a Media Source Reader.
 *
 * @param env JNI env
 * @param path path
 * @param ppMediaSrcReader media source reader
 * @return HRESULT
 */
HRESULT mf_createMediaSourceReader(JNIEnv *env, jstring path, IMFSourceReader **ppMediaSrcReader) {

    HRESULT res = S_OK;
    const LPWSTR pwszFilePath = (LPWSTR)env->GetStringChars(path, NULL);

    res = MFCreateSourceReaderFromURL(
        pwszFilePath, 
        NULL, 
        ppMediaSrcReader);
	if (HRESULT_CODE(res) == ERROR_FILE_NOT_FOUND
			|| HRESULT_CODE(res) == ERROR_PATH_NOT_FOUND
			|| HRESULT_CODE(res) == ERROR_NOT_DOS_DISK
			|| HRESULT_CODE(res) == ERROR_BAD_NETPATH) {
		const char * filePath = env->GetStringUTFChars(path, NULL);
        throwFileNotFoundExceptionIfError(env, res, filePath);
	    env->ReleaseStringUTFChars(path, filePath);
        goto bail;
	}
    if (res != S_OK) {
        throwUnsupportedAudioFileExceptionIfError(env, res, "Failed to create source reader from url");
        goto bail;
    }

bail:

    env->ReleaseStringChars(path, (jchar *)pwszFilePath);

    return res;
}