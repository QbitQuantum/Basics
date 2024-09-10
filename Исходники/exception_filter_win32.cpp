void setWindowsUnhandledExceptionFilter() {
    filtLast = SetUnhandledExceptionFilter(exceptionFilter);
}