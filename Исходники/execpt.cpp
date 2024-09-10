void MCExecPoint::setstringf(const char *p_spec, ...)
{
	va_list t_args;
	int t_count;

#if defined(_HAS_VSCPRINTF)
	va_start(t_args, p_spec);
	t_count = _vscprintf(p_spec, t_args);
	va_end(t_args);
#elif defined(_HAS_VSNPRINTF)
	va_start(t_args, p_spec);
	t_count = vsnprintf(nil, 0, p_spec, t_args);
	va_end(t_args);
#else
#error MCExecPoint::setstringf not implemented
#endif

	va_start(t_args, p_spec);
	vsprintf(getbuffer(t_count + 1), p_spec, t_args);
	va_end(t_args);

	setstrlen();
}