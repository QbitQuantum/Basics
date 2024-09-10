void winhostext_Query() {

	for (int i = 0; i<_SIZE; i++) {
		struct DirInfo * dirInfo = notifyHandles[i];

		if (dirInfo == NULL)
			break;

		if (dirInfo->notifyHandle == INVALID_HANDLE_VALUE)
			continue;

		DWORD singleWaitStatus = WaitForSingleObject(dirInfo->notifyHandle,0);
		if (singleWaitStatus == WAIT_OBJECT_0) {
			if (FindNextChangeNotification(dirInfo->notifyHandle)) {
				safeGuard = !safeGuard;
				if (safeGuard) {
					listProjectDirectory();
				}
			}
		} else if (singleWaitStatus == WAIT_TIMEOUT) {
		} else {
			printf("\n ERROR: Unhandled dwWaitStatus.\n");
		}
	}
}