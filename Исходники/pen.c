HPEN
APIENTRY
NtGdiExtCreatePen(
    DWORD dwPenStyle,
    DWORD ulWidth,
    IN ULONG ulBrushStyle,
    IN ULONG ulColor,
    IN ULONG_PTR ulClientHatch,
    IN ULONG_PTR ulHatch,
    DWORD dwStyleCount,
    PULONG pUnsafeStyle,
    IN ULONG cjDIB,
    IN BOOL bOldStylePen,
    IN OPTIONAL HBRUSH hBrush)
{
    NTSTATUS Status = STATUS_SUCCESS;
    DWORD* pSafeStyle = NULL;
    HPEN hPen;

    if ((int)dwStyleCount < 0) return 0;
    if (dwStyleCount > 16)
    {
        EngSetLastError(ERROR_INVALID_PARAMETER);
        return 0;
    }

    if (dwStyleCount > 0)
    {
        if (pUnsafeStyle == NULL)
        {
            EngSetLastError(ERROR_INVALID_PARAMETER);
            return 0;
        }

        pSafeStyle = ExAllocatePoolWithTag(NonPagedPool,
                                           dwStyleCount * sizeof(DWORD),
                                           GDITAG_PENSTYLE);
        if (!pSafeStyle)
        {
            SetLastNtError(ERROR_NOT_ENOUGH_MEMORY);
            return 0;
        }
        _SEH2_TRY
        {
            ProbeForRead(pUnsafeStyle, dwStyleCount * sizeof(DWORD), 1);
            RtlCopyMemory(pSafeStyle,
            pUnsafeStyle,
            dwStyleCount * sizeof(DWORD));
        }
        _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
        {
            Status = _SEH2_GetExceptionCode();
        }
        _SEH2_END
        if(!NT_SUCCESS(Status))
        {
            SetLastNtError(Status);
            ExFreePoolWithTag(pSafeStyle, GDITAG_PENSTYLE);
            return 0;
        }
    }

    if (ulBrushStyle == BS_PATTERN)
    {
        _SEH2_TRY
        {
            ProbeForRead((PVOID)ulHatch, cjDIB, 1);
        }
        _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
        {
            Status = _SEH2_GetExceptionCode();
        }
        _SEH2_END
        if(!NT_SUCCESS(Status))
        {
            SetLastNtError(Status);
            if (pSafeStyle) ExFreePoolWithTag(pSafeStyle, GDITAG_PENSTYLE);
            return 0;
        }
    }