VOID
FASTCALL
ObpFreeObject (
    IN PVOID Object
    )

/*++

Routine Description:

    This routine undoes ObpAllocateObject.  It returns the object back to free pool.

Arguments:

    Object - Supplies a pointer to the body of the object being freed.

Return Value:

    None.

--*/

{
    POBJECT_HEADER ObjectHeader;
    POBJECT_TYPE ObjectType;
    POBJECT_HEADER_QUOTA_INFO QuotaInfo;
    POBJECT_HEADER_HANDLE_INFO HandleInfo;
    POBJECT_HEADER_NAME_INFO NameInfo;
    POBJECT_HEADER_CREATOR_INFO CreatorInfo;
    PVOID FreeBuffer;
    ULONG NonPagedPoolCharge;
    ULONG PagedPoolCharge;

    PAGED_CODE();

    //
    //  Get the address of the object header.
    //

    ObjectHeader = OBJECT_TO_OBJECT_HEADER(Object);
    ObjectType = ObjectHeader->Type;

    //
    //  Now from the header determine the start of the allocation.  We need
    //  to backup based on what precedes the header.  The order is very
    //  important and must be the inverse of that used by ObpAllocateObject
    //

    FreeBuffer = ObjectHeader;

    CreatorInfo = OBJECT_HEADER_TO_CREATOR_INFO( ObjectHeader );

    if (CreatorInfo != NULL) {

        FreeBuffer = CreatorInfo;
    }

    NameInfo = OBJECT_HEADER_TO_NAME_INFO( ObjectHeader );

    if (NameInfo != NULL) {

        FreeBuffer = NameInfo;
    }

    HandleInfo = OBJECT_HEADER_TO_HANDLE_INFO( ObjectHeader );

    if (HandleInfo != NULL) {

        FreeBuffer = HandleInfo;
    }

    QuotaInfo = OBJECT_HEADER_TO_QUOTA_INFO( ObjectHeader );

    if (QuotaInfo != NULL) {

        FreeBuffer = QuotaInfo;
    }

#if DBG

    //
    //  On a checked build echo out frees
    //

    if (ObpShowAllocAndFree) {

        DbgPrint( "OB: Free  %lx (%lx) - Type: %wZ\n", ObjectHeader, ObjectHeader, &ObjectType->Name );
    }
#endif

    //
    //  Decrement the number of objects of this type
    //

    InterlockedDecrement((PLONG)&ObjectType->TotalNumberOfObjects);

    //
    //  Check where we were in the object initialization phase.  This
    //  flag really only tests if we have charged quota for this object.
    //  This is because the object create info and the quota block charged
    //  are unioned together.
    //

    if (ObjectHeader->Flags & OB_FLAG_NEW_OBJECT) {

        if (ObjectHeader->ObjectCreateInfo != NULL) {

            ObpFreeObjectCreateInformation( ObjectHeader->ObjectCreateInfo );

            ObjectHeader->ObjectCreateInfo = NULL;
        }

    } else {

        if (ObjectHeader->QuotaBlockCharged != NULL) {

            if (QuotaInfo != NULL) {

                PagedPoolCharge = QuotaInfo->PagedPoolCharge +
                                  QuotaInfo->SecurityDescriptorCharge;

                NonPagedPoolCharge = QuotaInfo->NonPagedPoolCharge;

            } else {

                PagedPoolCharge = ObjectType->TypeInfo.DefaultPagedPoolCharge;

                if (ObjectHeader->Flags & OB_FLAG_DEFAULT_SECURITY_QUOTA ) {

                    PagedPoolCharge += SE_DEFAULT_SECURITY_QUOTA;
                }

                NonPagedPoolCharge = ObjectType->TypeInfo.DefaultNonPagedPoolCharge;
            }

            PsReturnSharedPoolQuota( ObjectHeader->QuotaBlockCharged,
                                     PagedPoolCharge,
                                     NonPagedPoolCharge );

            ObjectHeader->QuotaBlockCharged = NULL;
        }
    }

    if ((HandleInfo != NULL) &&
        ((ObjectHeader->Flags & OB_FLAG_SINGLE_HANDLE_ENTRY) == 0)) {

        //
        //  If a handle database has been allocated, then free the memory.
        //

        ExFreePool( HandleInfo->HandleCountDataBase );

        HandleInfo->HandleCountDataBase = NULL;
    }

    //
    //  If a name string buffer has been allocated, then free the memory.
    //

    if (NameInfo != NULL && NameInfo->Name.Buffer != NULL) {

        ExFreePool( NameInfo->Name.Buffer );

        NameInfo->Name.Buffer = NULL;
    }

    PERFINFO_REMOVE_OBJECT_FROM_ALLOCATED_TYPE_LIST(CreatorInfo, ObjectHeader);

    //
    //  Trash type field so we don't get far if we attempt to
    //  use a stale object pointer to this object.
    //
    //  Win64 Note: trash it by zero-extended it. 
    //                sign-extension will create a valid kernel address.


    ObjectHeader->Type = UIntToPtr(0xBAD0B0B0); 
    ExFreePoolWithTag( FreeBuffer,
                       (ObjectType == NULL ? 'TjbO' : ObjectType->Key) |
                            PROTECTED_POOL );

    return;
}