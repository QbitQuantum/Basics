void sp_polygon_set(SPObject *object, unsigned int key, const gchar *value)
{
    SPPolygon *polygon = SP_POLYGON(object);

    switch (key) {
        case SP_ATTR_POINTS: {
            if (!value) {
                /* fixme: The points attribute is required.  We should handle its absence as per
                 * http://www.w3.org/TR/SVG11/implnote.html#ErrorProcessing. */
                break;
            }
            SPCurve *curve = new SPCurve();
            gboolean hascpt = FALSE;

            gchar const *cptr = value;
            bool has_error = false;

            while (TRUE) {
                gdouble x;
                if (!polygon_get_value(&cptr, &x)) {
                    break;
                }

                gdouble y;
                if (!polygon_get_value(&cptr, &y)) {
                    /* fixme: It is an error for an odd number of points to be specified.  We
                     * should display the points up to now (as we currently do, though perhaps
                     * without the closepath: the spec isn't quite clear on whether to do a
                     * closepath or not, though I'd guess it's best not to do a closepath), but
                     * then flag the document as in error, as per
                     * http://www.w3.org/TR/SVG11/implnote.html#ErrorProcessing.
                     *
                     * (Ref: http://www.w3.org/TR/SVG11/shapes.html#PolygonElement.) */
                    has_error = true;
                    break;
                }

                if (hascpt) {
                    curve->lineto(x, y);
                } else {
                    curve->moveto(x, y);
                    hascpt = TRUE;
                }
            }

            if (has_error || *cptr != '\0') {
                /* TODO: Flag the document as in error, as per
                 * http://www.w3.org/TR/SVG11/implnote.html#ErrorProcessing. */
            } else if (hascpt) {
                /* We might have done a moveto but no lineto.  I'm not sure how we're supposed to represent
                 * a single-point polygon in SPCurve. TODO: add a testcase with only one coordinate pair */
                curve->closepath();
            }
            sp_shape_set_curve(SP_SHAPE(polygon), curve, TRUE);
            curve->unref();
            break;
        }
        default:
            if (((SPObjectClass *) parent_class)->set) {
                ((SPObjectClass *) parent_class)->set(object, key, value);
            }
            break;
    }
}