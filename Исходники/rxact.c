NTSTATUS
NTAPI
RtlAddAttributeActionToRXact(
    PRXACT_CONTEXT Context,
    ULONG ActionType,
    PUNICODE_STRING KeyName,
    HANDLE KeyHandle,
    PUNICODE_STRING ValueName,
    ULONG ValueType,
    PVOID ValueData,
    ULONG ValueDataSize)
{
    ULONG ActionSize;
    ULONG RequiredSize;
    ULONG BufferSize;
    ULONG CurrentOffset;
    PRXACT_DATA NewData;
    PRXACT_ACTION Action;

    /* Validate ActionType parameter */
    if ((ActionType != RXactDeleteKey) && (ActionType != RXactSetValueKey))
    {
        return STATUS_INVALID_PARAMETER;
    }

    /* Calculate the size of the new action record */
    ActionSize = ALIGN_UP_BY(ValueName->Length, sizeof(ULONG)) +
                 ALIGN_UP_BY(ValueDataSize, sizeof(ULONG)) +
                 ALIGN_UP_BY(KeyName->Length, sizeof(ULONG)) +
                 ALIGN_UP_BY(sizeof(RXACT_ACTION), sizeof(ULONG));

    /* Calculate the new buffer size we need */
    RequiredSize = ActionSize + Context->Data->CurrentSize;

    /* Check for integer overflow */
    if (RequiredSize < ActionSize)
    {
        return STATUS_NO_MEMORY;
    }

    /* Check if the buffer is large enough */
    BufferSize = Context->Data->BufferSize;
    if (RequiredSize > BufferSize)
    {
        /* Increase by a factor of 2, until it is large enough */
        while (BufferSize < RequiredSize)
        {
            BufferSize *= 2;
        }

        /* Allocate a new buffer from the heap */
        NewData = RtlAllocateHeap(RtlGetProcessHeap(), 0, BufferSize);
        if (NewData == NULL)
        {
            return STATUS_NO_MEMORY;
        }

        /* Copy the old buffer to the new one */
        RtlCopyMemory(NewData, Context->Data, Context->Data->CurrentSize);

        /* Free the old buffer and use the new one */
        RtlFreeHeap(RtlGetProcessHeap(), 0, Context->Data);
        Context->Data = NewData;
        NewData->BufferSize = BufferSize;
    }

    /* Get the next action record */
    Action = (RXACT_ACTION *)((PUCHAR)Context->Data + Context->Data->CurrentSize);

    /* Fill in the fields */
    Action->Size = ActionSize;
    Action->Type = ActionType;
    Action->KeyName = *KeyName;
    Action->ValueName = *ValueName;
    Action->ValueType = ValueType;
    Action->ValueDataSize = ValueDataSize;
    Action->KeyHandle = KeyHandle;

    /* Copy the key name (and convert the pointer to a buffer offset) */
    CurrentOffset = Context->Data->CurrentSize + sizeof(RXACT_ACTION);
    Action->KeyName.Buffer = UlongToPtr(CurrentOffset);
    RtlCopyMemory((PUCHAR)Context->Data + CurrentOffset,
                  KeyName->Buffer,
                  KeyName->Length);

    /* Copy the value name (and convert the pointer to a buffer offset) */
    CurrentOffset += ALIGN_UP_BY(KeyName->Length, sizeof(ULONG));
    Action->ValueName.Buffer = UlongToPtr(CurrentOffset);
    RtlCopyMemory((PUCHAR)Context->Data + CurrentOffset,
                  ValueName->Buffer,
                  ValueName->Length);

    /* Update the offset */
    CurrentOffset += ALIGN_UP_BY(ValueName->Length, sizeof(ULONG));

    /* Is this a set action? */
    if (ActionType == RXactSetValueKey)
    {
        /* Copy the key value data as well */
        Action->ValueData = UlongToPtr(CurrentOffset);
        RtlCopyMemory((PUCHAR)Context->Data + CurrentOffset,
                      ValueData,
                      ValueDataSize);
        CurrentOffset += ALIGN_UP_BY(ValueDataSize, sizeof(ULONG));
    }

    /* Update data site and action count */
    Context->Data->CurrentSize = CurrentOffset;
    Context->Data->ActionCount++;

    return STATUS_SUCCESS;
}