/**
 * Allocates a object.
 *
 * \param Object A variable which receives a pointer to the newly allocated object.
 * \param ObjectSize The size of the object.
 * \param Flags A combination of flags specifying how the object is to be allocated.
 * \li \c PHOBJ_RAISE_ON_FAIL An exception will be raised if the object cannot be
 * allocated.
 * \param ObjectType The type of the object.
 */
__mayRaise NTSTATUS PhCreateObject(
    __out PVOID *Object,
    __in SIZE_T ObjectSize,
    __in ULONG Flags,
    __in PPH_OBJECT_TYPE ObjectType
    )
{
    NTSTATUS status = STATUS_SUCCESS;
    PPH_OBJECT_HEADER objectHeader;

#ifdef PHOBJ_STRICT_CHECKS
    /* Check the flags. */
    if ((Flags & PHOBJ_VALID_FLAGS) != Flags) /* Valid flag mask */
    {
        status = STATUS_INVALID_PARAMETER_3;
    }
#else
    assert(!((Flags & PHOBJ_VALID_FLAGS) != Flags));
#endif

#ifdef PHOBJ_STRICT_CHECKS
    if (NT_SUCCESS(status))
    {
#endif
        /* Allocate storage for the object. Note that this includes
         * the object header followed by the object body. */
        objectHeader = PhpAllocateObject(ObjectType, ObjectSize, Flags);

#ifndef PHOBJ_ALLOCATE_NEVER_NULL
        if (!objectHeader)
            status = STATUS_NO_MEMORY;
#endif
#ifdef PHOBJ_STRICT_CHECKS
    }
#endif

#ifndef PHOBJ_ALLOCATE_NEVER_NULL
    if (!NT_SUCCESS(status))
    {
        if (!(Flags & PHOBJ_RAISE_ON_FAIL))
            return status;
        else
            PhRaiseStatus(status);
    }
#endif

    /* Object type statistics. */
    _InterlockedIncrement((PLONG)&ObjectType->NumberOfObjects);

    /* Initialize the object header. */
    objectHeader->RefCount = 1;
    // objectHeader->Flags is initialized by PhpAllocateObject.
    objectHeader->Size = ObjectSize;
    objectHeader->Type = ObjectType;

    REF_STAT_UP(RefObjectsCreated);

#ifdef DEBUG
    {
        USHORT capturedFrames;

        capturedFrames = RtlCaptureStackBackTrace(1, 16, objectHeader->StackBackTrace, NULL);
        memset(
            &objectHeader->StackBackTrace[capturedFrames],
            0,
            sizeof(objectHeader->StackBackTrace) - capturedFrames * sizeof(PVOID)
            );
    }

    PhAcquireQueuedLockExclusive(&PhDbgObjectListLock);
    InsertTailList(&PhDbgObjectListHead, &objectHeader->ObjectListEntry);
    PhReleaseQueuedLockExclusive(&PhDbgObjectListLock);

    {
        PPH_CREATE_OBJECT_HOOK dbgCreateObjectHook;

        dbgCreateObjectHook = PhDbgCreateObjectHook;

        if (dbgCreateObjectHook)
        {
            dbgCreateObjectHook(
                PhObjectHeaderToObject(objectHeader),
                ObjectSize,
                Flags,
                ObjectType
                );
        }
    }
#endif

    /* Pass a pointer to the object body back to the caller. */
    *Object = PhObjectHeaderToObject(objectHeader);

    return status;
}