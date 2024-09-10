static int SerialPort_getLineStatus(GORILLA_METHOD_PARAMETERS) {
    HANDLE win32Handle;
    int status;
    
    win32Handle = SerialPort_property__win32Handle_entity(GORILLA_METHOD_PARAM_PASSTHRU);
    if (GetCommModemStatus(win32Handle, (LPDWORD)&status) == FALSE) {
        zend_throw_exception(NULL, "failed to get line status", 641 TSRMLS_CC);
        return 0;
    }
    
    return status;
}