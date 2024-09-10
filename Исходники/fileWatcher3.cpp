int _tmain(int argc, _TCHAR *argv[]) {
    InitializeCriticalSection(&csOutput);

    for (int i = 0; i < 26; i++) {
        watchRootInfos[i].driveLetter = 'A' + i;
        watchRootInfos[i].bInitialized = false;
        watchRootInfos[i].bUsed = false;
    }

    char buffer[8192];
    while (true) {
        if (!gets_s(buffer, sizeof(buffer) - 1))
            break;

        if (!strcmp(buffer, "ROOTS")) {
            MarkAllRootsUnused();
            FreeWatchRootsList();
            bool failed = false;
            while (true) {
                if (!gets_s(buffer, sizeof(buffer) - 1)) {
                    failed = true;
                    break;
                }
                if (buffer[0] == '#')
                    break;
                int driveLetterPos = 0;
                char *pDriveLetter = buffer;
                if (*pDriveLetter == '|')
                    pDriveLetter++;

                AddWatchRoot(pDriveLetter);

                _strupr_s(buffer, sizeof(buffer) - 1);
                char driveLetter = *pDriveLetter;
                if (driveLetter >= 'A' && driveLetter <= 'Z') {
                    watchRootInfos[driveLetter - 'A'].bUsed = true;
                }
            }
            if (failed)
                break;

            UpdateRoots(true);
        }

        if (!strcmp(buffer, "EXIT"))
            break;
    }

    MarkAllRootsUnused();
    UpdateRoots(false);

    DeleteCriticalSection(&csOutput);
}