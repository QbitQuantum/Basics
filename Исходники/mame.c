void mame_file_output_callback(FILE *param, const char *format, va_list argptr)
{
	vfprintf(param, format, argptr);
}