void EXPORT KppLogSendMessage(ATOMID idMethod, ATOMID idObj, BOOL bExit)
{
    WORD wLen = sprintf(return_buffer, "%4d : ", wLogCount++);
        
    wLen += KppGetAtomName(idMethod, return_buffer + wLen,
                           RET_BUFFER_LEN - wLen);
    strcpy(return_buffer + wLen, "->");
    wLen += 2;
    wLen += KppGetAtomName(idObj, return_buffer + wLen,
                           RET_BUFFER_LEN - wLen);
    strcpy(return_buffer + wLen, bExit ? "  )" : "  (");
    strcpy(return_buffer + wLen + 3, "\r\n");
    
    _lwrite(hLogFile, return_buffer, wLen + 5);
}