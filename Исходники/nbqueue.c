BOOLEAN
ExRemoveHeadNBQueue (
    IN PVOID Header,
    OUT PULONG64 Value
    )

/*++

Routine Description:

    This function removes a queue entry from the head of the specified
    non-blocking queue and returns the associated data value.

Arguments:

    Header - Supplies an opaque pointer to a non-blocking queue header.

    Value - Supplies a pointer to a variable that receives the queue
        element value.

Return Value:

    If an entry is removed from the specified non-blocking queue, then
    TRUE is returned as the function value. Otherwise, FALSE is returned.

--*/

{

    NBQUEUE_POINTER Head;
    PNBQUEUE_NODE HeadNode;
    NBQUEUE_POINTER Insert;
    NBQUEUE_POINTER Next;
    PNBQUEUE_NODE NextNode;
    PNBQUEUE_HEADER QueueHead;
    NBQUEUE_POINTER Tail;
    PNBQUEUE_NODE TailNode;

    //
    // The following loop is executed until an entry can be removed from
    // the specified non-blocking queue or until it can be determined that
    // the queue is empty.
    //

    QueueHead = (PNBQUEUE_HEADER)Header;
    do {

        //
        // Read the head queue pointer, the tail queue pointer, and the
        // next queue pointer of the head queue pointer making sure the
        // three pointers are coherent.
        //

        Head.Data = ReadForWriteAccess((volatile LONG64 *)(&QueueHead->Head.Data));
        Tail.Data = *((volatile LONG64 *)(&QueueHead->Tail.Data));
        HeadNode = UnpackNBQPointer(&Head);
        Next.Data = *((volatile LONG64 *)(&HeadNode->Next.Data));
        if (Head.Data == *((volatile LONG64 *)(&QueueHead->Head.Data))) {

            //
            // If the queue header node is equal to the queue tail node,
            // then either the queue is empty or the tail pointer is falling
            // behind. Otherwise, there is an entry in the queue that can
            // be removed.
            //

            NextNode = UnpackNBQPointer(&Next);
            TailNode = UnpackNBQPointer(&Tail);
            if (HeadNode == TailNode) {

                //
                // If the next node of head pointer is NULL, then the queue
                // is empty. Otherwise, attempt to move the tail forward.
                //

                if (NextNode == NULL) {
                    return FALSE;

                } else {
                    PackNBQPointer(&Insert, NextNode);
                    Insert.Count = Tail.Count + 1;
                    InterlockedCompareExchange64(&QueueHead->Tail.Data,
                                                 Insert.Data,
                                                 Tail.Data);
                }

            } else {

                //
                // There is an entry in the queue that can be removed.
                //

                *Value = NextNode->Value;
                PackNBQPointer(&Insert, NextNode);
                Insert.Count = Head.Count + 1;
                if (InterlockedCompareExchange64(&QueueHead->Head.Data,
                                                 Insert.Data,
                                                 Head.Data) == Head.Data) {

                    break;
                }
            }
        }

    } while (TRUE);

    //
    // Free the node that was removed for the list by inserting the node
    // in the associated SLIST.
    //

    InterlockedPushEntrySList(QueueHead->SlistHead,
                              (PSLIST_ENTRY)HeadNode);

    return TRUE;
}