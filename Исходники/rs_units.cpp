/**
 * Formats the given length in scientific format (e.g. 2.5E7).
 *
 * @param length The length in the current unit of the drawing.
 * @param prec Precisision of the value (e.g. 0.001 or 1/128 = 0.0078125)
 & @param showUnit Append unit to the value.
 */
RS_String RS_Units::formatScientific(double length, RS2::Unit unit,
                                     int prec, bool showUnit) {

    RS_String ret;

    // unit appended to value (e.g. 'mm'):
    RS_String unitString = "";
    if (showUnit) {
        unitString = unitToSign(unit);
    }

    char format[128];
    sprintf(format, "%%.%dE%%s", prec);
    ret.sprintf(format, length, (const char*)unitString.local8Bit());

    return ret;
}