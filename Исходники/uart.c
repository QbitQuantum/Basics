int uart_scanf(const char *fmt, ...){
    va_list ap;
    int count;

    va_start(ap, fmt);
	#ifndef SIMULATE
    count = uart_vscanf(fmt, ap);
	#else
    count = vscanf(fmt, ap);
	#endif

    va_end(ap);

    return count;
}