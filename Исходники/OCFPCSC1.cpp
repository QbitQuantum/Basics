/*
 * Class:     com_ibm_opencard_terminal_pcsc10_OCFPCSC1
 * Method:    SCardDisconnect
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_com_ibm_opencard_terminal_pcsc10_OCFPCSC1_SCardDisconnect
(JNIEnv *env, jobject obj, jint card, jint disposition) {

    long          returnCode;
    CONTEXT_INFO  cInfo;

    // get the contextInfo from the table
    cInfo = getContextInfoViaCardHandle((SCARDHANDLE)card);
    if (cInfo.context == 0) {
        throwPcscException(env, obj, "SCardDisconnect", "PC/SC Wrapper Error: couldn't get context information record", 0);
        return;
    }

    returnCode = SCardDisconnect((SCARDHANDLE)card, (DWORD)disposition);
    if ((returnCode != SCARD_S_SUCCESS) && (returnCode != SCARD_W_REMOVED_CARD)) {
        throwPcscException(env, obj, "SCardDisconnect", "PC/SC Error SCardDisconnect", returnCode);
        return;
    }

    // delete cardHandle and active protocol in context info record
    cInfo.cardHandle = 0;
    cInfo.protocol = 0;

    // store the modified context informations
    if (setContextInformation(cInfo) != 0) {
        throwPcscException(env, obj, "SCardDisconnect", "PC/SC Wrapper Error: update of context information record failed", 0);
        return;
    }

    return;
}