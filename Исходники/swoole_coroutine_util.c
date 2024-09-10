static PHP_METHOD(swoole_coroutine_util, fread)
{
    coro_check(TSRMLS_C);

    zval *handle;
    zend_long length = 0;

#ifdef FAST_ZPP
    ZEND_PARSE_PARAMETERS_START(1, 2)
        Z_PARAM_RESOURCE(handle)
        Z_PARAM_OPTIONAL
        Z_PARAM_LONG(length)
    ZEND_PARSE_PARAMETERS_END_EX(RETURN_FALSE);
#else
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r|l", &handle, &length) == FAILURE)
    {
        return;
    }
#endif

    int fd = swoole_convert_to_fd(handle TSRMLS_CC);

    struct stat file_stat;
    if (fstat(fd, &file_stat) < 0)
    {
        RETURN_FALSE;
    }

    off_t _seek = lseek(fd, 0, SEEK_CUR);
    if (length <= 0 || file_stat.st_size - _seek < length)
    {
        length = file_stat.st_size - _seek;
    }

    swAio_event ev;
    bzero(&ev, sizeof(swAio_event));

    ev.nbytes = length + 1;
    ev.buf = emalloc(ev.nbytes);
    if (!ev.buf)
    {
        RETURN_FALSE;
    }

    php_context *context = emalloc(sizeof(php_context));

    ((char *) ev.buf)[length] = 0;
    ev.flags = 0;
    ev.type = SW_AIO_READ;
    ev.object = context;
    ev.callback = aio_onReadCompleted;
    ev.fd = fd;
    ev.offset = _seek;

    if (!SwooleAIO.init)
    {
        php_swoole_check_reactor();
        swAio_init();
    }

    swTrace("fd=%d, offset=%ld, length=%ld", fd, ev.offset, ev.nbytes);

    int ret = swAio_dispatch(&ev);
    if (ret < 0)
    {
        efree(context);
        RETURN_FALSE;
    }

    context->onTimeout = NULL;
    context->state = SW_CORO_CONTEXT_RUNNING;

    coro_save(context);
    coro_yield();
}