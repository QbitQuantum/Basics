void
MemoryProtectionExceptionHandler::uninstall()
{
    if (sExceptionHandlerInstalled) {
        MOZ_ASSERT(!sHandlingException);

        // Restore the previous exception handler.
        MOZ_ALWAYS_TRUE(RemoveVectoredExceptionHandler(sVectoredExceptionHandler));

        sExceptionHandlerInstalled = false;
    }
}