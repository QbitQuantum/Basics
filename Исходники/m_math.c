/*
 * Math library extensions to AG_Label(3).
 */
static void
PrintReal(AG_Label *lbl, char *s, size_t len, int fPos)
{
	M_Real r = AG_LABEL_ARG(lbl,M_Real);
#if defined(QUAD_PRECISION)
	Snprintf(s, len, "%llf", r);
#else
	Snprintf(s, len, "%f", r);
#endif
}