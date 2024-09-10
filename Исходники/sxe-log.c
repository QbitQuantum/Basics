void
sxe_log_entry(unsigned id, unsigned int verbosity, const char * file, int line, const char *fmt, ...)
{
    char  log_buffer[SXE_LOG_BUFFER_SIZE];
    va_list  ap;
    unsigned i;
    unsigned prefix_length;

    SXE_CHECK_LOG_INITIALIZE();
    SXE_CHECK_VERBOSITY_BEFORE_ANYTHING_ELSE();

    prefix_length   = sxe_log_buffer_set_prefix(log_buffer, id, verbosity);
    i               = prefix_length;
    va_start(ap, fmt);

    if (sxe_log_safe_append(log_buffer, &i,  SNPRINTF(&log_buffer[i], SXE_LOG_BUFFER_SIZE - i, "%*s+ ", SXE_LOG_INDENT * 2, ""))
    &&  sxe_log_safe_append(log_buffer, &i, VSNPRINTF(&log_buffer[i], SXE_LOG_BUFFER_SIZE - i, fmt, ap))) {
        sxe_log_safe_append(log_buffer, &i,  SNPRINTF(&log_buffer[i], SXE_LOG_BUFFER_SIZE - i, "\n"));
    }

    sxe_log_line_out_escaped(log_buffer);
    i = prefix_length;
    sxe_log_safe_append(log_buffer, &i,  SNPRINTF(&log_buffer[i], SXE_LOG_BUFFER_SIZE - i, "%*s  { // %s:%d\n",
                        SXE_LOG_INDENT * 2, "", file, line));
    sxe_log_line_out_escaped(log_buffer);
    SXE_LOG_SET_INDENT(SXE_LOG_INDENT + 1);
} /* sxe_log_entry() */