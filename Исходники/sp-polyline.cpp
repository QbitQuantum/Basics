void SPPolyLine::set(SPObject *object, unsigned int key, const gchar *value)
{
    SPPolyLine *polyline = SP_POLYLINE(object);

    switch (key) {
	case SP_ATTR_POINTS: {
            SPCurve * curve;
            const gchar * cptr;
            char * eptr;
            gboolean hascpt;

            if (!value) break;
            curve = new SPCurve ();
            hascpt = FALSE;

            cptr = value;
            eptr = NULL;

            while (TRUE) {
                gdouble x, y;

                while (*cptr != '\0' && (*cptr == ',' || *cptr == '\x20' || *cptr == '\x9' || *cptr == '\xD' || *cptr == '\xA')) {
                    cptr++;
                }
                if (!*cptr) break;

                x = g_ascii_strtod (cptr, &eptr);
                if (eptr == cptr) break;
                cptr = eptr;

                while (*cptr != '\0' && (*cptr == ',' || *cptr == '\x20' || *cptr == '\x9' || *cptr == '\xD' || *cptr == '\xA')) {
                    cptr++;
                }
                if (!*cptr) break;

                y = g_ascii_strtod (cptr, &eptr);
                if (eptr == cptr) break;
                cptr = eptr;
                if (hascpt) {
                    curve->lineto(x, y);
                } else {
                    curve->moveto(x, y);
                    hascpt = TRUE;
                }
            }
		
            (SP_SHAPE (polyline))->setCurve (curve, TRUE);
            curve->unref();
            break;
	}
	default:
            if (((SPObjectClass *) SPPolyLineClass::static_parent_class)->set) {
                ((SPObjectClass *) SPPolyLineClass::static_parent_class)->set (object, key, value);
            }
            break;
    }
}