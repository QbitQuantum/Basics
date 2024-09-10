// appends data to the UserIPQueue
void clsGlobalDataQueue::UserIPStore(User * pUser) {
    if(UserIPQueue.szLen == 0) {
        UserIPQueue.szLen = sprintf(UserIPQueue.sBuffer, "$UserIP %s %s|", pUser->sNick, pUser->sIP);
        UserIPQueue.bHaveDollars = false;
    } else {
        int iDataLen = sprintf(msg, "%s %s$$|", pUser->sNick, pUser->sIP);
        if(CheckSprintf(iDataLen, 128, "clsGlobalDataQueue::UserIPStore") == true) {
            if(UserIPQueue.bHaveDollars == false) {
                UserIPQueue.sBuffer[UserIPQueue.szLen-1] = '$';
                UserIPQueue.sBuffer[UserIPQueue.szLen] = '$';
                UserIPQueue.bHaveDollars = true;
                UserIPQueue.szLen += 2;
            }
            if(UserIPQueue.szSize < UserIPQueue.szLen+iDataLen) {
                size_t szAllignLen = Allign256(UserIPQueue.szLen+iDataLen);
                char * pOldBuf = UserIPQueue.sBuffer;
#ifdef _WIN32
                UserIPQueue.sBuffer = (char *)HeapReAlloc(clsServerManager::hLibHeap, HEAP_NO_SERIALIZE, (void *)pOldBuf, szAllignLen);
#else
				UserIPQueue.sBuffer = (char *)realloc(pOldBuf, szAllignLen);
#endif
                if(UserIPQueue.sBuffer == NULL) {
                    UserIPQueue.sBuffer = pOldBuf;

					AppendDebugLog("%s - [MEM] Cannot reallocate %" PRIu64 " bytes in clsGlobalDataQueue::UserIPStore\n", (uint64_t)szAllignLen);

                    return;
                }
                UserIPQueue.szSize = (uint32_t)(szAllignLen-1);
            }
            memcpy(UserIPQueue.sBuffer+UserIPQueue.szLen-1, msg, iDataLen);
            UserIPQueue.szLen += iDataLen-1;
            UserIPQueue.sBuffer[UserIPQueue.szLen] = '\0';
        }
    }
}