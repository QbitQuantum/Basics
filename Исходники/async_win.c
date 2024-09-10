int async_fibre_init_dispatcher(async_fibre *fibre)
{
    LPVOID dispatcher;

    dispatcher = (LPVOID)TlsGetValue(asyncwindispatch);
    if (dispatcher == NULL) {
        fibre->fibre = ConvertThreadToFiber(NULL);
        if (fibre->fibre == NULL) {
            fibre->converted = 0;
            fibre->fibre = GetCurrentFiber();
            if (fibre->fibre == NULL)
                return 0;
        } else {
            fibre->converted = 1;
        }
        if (TlsSetValue(asyncwindispatch, (LPVOID)fibre->fibre) == 0)
            return 0;
    } else {
        fibre->fibre = dispatcher;
    }
    return 1;
}