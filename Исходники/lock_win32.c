LOCK_HANDLE Lock_Init(void)
{
    /* Codes_SRS_LOCK_10_002: [Lock_Init on success shall return a valid lock handle which should be a non NULL value] */
    /* Codes_SRS_LOCK_10_003: [Lock_Init on error shall return NULL ] */
    HANDLE result = CreateSemaphoreW(NULL, 1, 1, NULL);
    if (result == NULL)
    {
        LogError("CreateSemaphore failed.");
    }

    return (LOCK_HANDLE)result;
}