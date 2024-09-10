int plugin_settings_setfloat(const char *splg, const char *sname, double sval)
{
	char tbuffer[512];

	gcvt(sval, 256, tbuffer);
	return plugin_settings_set(splg, sname, tbuffer);
}