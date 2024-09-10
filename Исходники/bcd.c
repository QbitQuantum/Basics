NTSTATUS
BcdDeleteElement (
    _In_ HANDLE ObjectHandle,
    _In_ ULONG Type
    )
{
    NTSTATUS Status;
    HANDLE ElementsHandle, ElementHandle;
    WCHAR TypeString[22];

    /* Open the elements key */
    Status = BiOpenKey(ObjectHandle, L"Elements", &ElementsHandle);
    if (NT_SUCCESS(Status))
    {
        /* Convert the element ID into a string */
        if (!_ultow(Type, TypeString, 16))
        {
            /* Failed to do so */
            Status = STATUS_UNSUCCESSFUL;
        }
        else
        {
            /* Open the element specifically */
            Status = BiOpenKey(ElementHandle, TypeString, &ElementHandle);
            if (NT_SUCCESS(Status))
            {
                /* Delete it */
                Status = BiDeleteKey(ElementHandle);
                if (NT_SUCCESS(Status))
                {
                    /* No point in closing the handle anymore */
                    ElementHandle = NULL;
                }
            }
            else
            {
                /* The element doesn't exist */
                Status = STATUS_NOT_FOUND;
            }

            /* Check if we should close the key */
            if (ElementHandle)
            {
                /* Do it */
                BiCloseKey(ElementHandle);
            }
        }
    }

    /* Check if we should close the elements handle */
    if (ElementsHandle)
    {
        /* Do it */
        BiCloseKey(ElementsHandle);
    }

    /* Return whatever the result was */
    return Status;
}