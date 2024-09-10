INT
APIENTRY
NtGdiDescribePixelFormat(HDC  hDC,
                         INT  PixelFormat,
                         UINT  BufSize,
                         LPPIXELFORMATDESCRIPTOR  pfd)
{
    PDC pdc;
    PPDEVOBJ ppdev;
    INT Ret = 0;
    PIXELFORMATDESCRIPTOR pfdSafe;
    NTSTATUS Status = STATUS_SUCCESS;

    if (!BufSize) return 0;

    pdc = DC_LockDc(hDC);
    if (!pdc)
    {
        EngSetLastError(ERROR_INVALID_HANDLE);
        return 0;
    }

    if (!pdc->ipfdDevMax) IntGetipfdDevMax(pdc);

    if ( BufSize < sizeof(PIXELFORMATDESCRIPTOR) ||
            PixelFormat < 1 ||
            PixelFormat > pdc->ipfdDevMax )
    {
        EngSetLastError(ERROR_INVALID_PARAMETER);
        goto Exit;
    }

    ppdev = pdc->ppdev;

    if (ppdev->flFlags & PDEV_META_DEVICE)
    {
        UNIMPLEMENTED;
        goto Exit;
    }

    if (ppdev->DriverFunctions.DescribePixelFormat)
    {
        Ret = ppdev->DriverFunctions.DescribePixelFormat(
                  ppdev->dhpdev,
                  PixelFormat,
                  sizeof(PIXELFORMATDESCRIPTOR),
                  &pfdSafe);
    }

    _SEH2_TRY
    {
        ProbeForWrite( pfd,
        sizeof(PIXELFORMATDESCRIPTOR),
        1);
        RtlCopyMemory(&pfdSafe, pfd, sizeof(PIXELFORMATDESCRIPTOR));
    }
    _SEH2_EXCEPT(EXCEPTION_EXECUTE_HANDLER)
    {
        Status = _SEH2_GetExceptionCode();
    }
    _SEH2_END;

    if (!NT_SUCCESS(Status)) SetLastNtError(Status);

Exit:
    DC_UnlockDc(pdc);
    return Ret;
}