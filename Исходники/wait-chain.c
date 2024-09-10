void PrintWaitChain(__in DWORD ThreadId)
/*++

Routine Description:

    Enumerates all threads (or optionally only threads for one
    process) in the system. It the calls the WCT API on each thread.

Arguments:

    ThreadId--Specifies the thread ID to analyze.

Return Value:

    (none)

--*/
{
    WAITCHAIN_NODE_INFO NodeInfoArray[WCT_MAX_NODE_COUNT];
    DWORD Count, i;
    BOOL IsCycle;

    printf("%d: ", ThreadId);

    Count = WCT_MAX_NODE_COUNT;

    // Make a synchronous WCT call to retrieve the wait chain.
    if (!GetThreadWaitChain(g_WctHandle, NULL, WCTP_GETINFO_ALL_FLAGS, ThreadId, &Count, NodeInfoArray, &IsCycle)) {
        printf("Error (0X%x)\n", GetLastError());
        return;
    }

    // Check if the wait chain is too big for the array we passed in.
    if (Count > WCT_MAX_NODE_COUNT) {
        printf("Found additional nodes %d\n", Count);
        Count = WCT_MAX_NODE_COUNT;
    }

    // Loop over all the nodes returned and print useful information.
    for (i = 0; i < Count; i++) {
        switch (NodeInfoArray[i].ObjectType) {
        case WctThreadType:
            // A thread node contains process and thread ID.
            printf("[%x:%x:%s]->", NodeInfoArray[i].ThreadObject.ProcessId, NodeInfoArray[i].ThreadObject.ThreadId,
                   ((NodeInfoArray[i].ObjectStatus == WctStatusBlocked) ? "b" : "r"));
            break;

        default:
            // A synchronization object.

            // Some objects have names...
            if (NodeInfoArray[i].LockObject.ObjectName[0] != L'\0') {
                printf("[%s:%S]->", STR_OBJECT_TYPE[NodeInfoArray[i].ObjectType - 1].Desc,
                       NodeInfoArray[i].LockObject.ObjectName);
            } else {
                printf("[%s]->", STR_OBJECT_TYPE[NodeInfoArray[i].ObjectType - 1].Desc);
            }
            if (NodeInfoArray[i].ObjectStatus == WctStatusAbandoned) {
                printf("<abandoned>");
            }
            break;
        }
    }

    printf("[End]");

    // Did we find a deadlock?
    if (IsCycle) {
        printf(" !!!Deadlock!!!");
    }

    printf("\n");
}