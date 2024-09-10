/**
 * Converts a double into a string which is as short as possible
 *
 * @param value The double value
 * @param prec Precision e.g. a precision of 1 would mean that a 
 *     value of 2.12030 will be converted to "2.1". 2.000 is always just "2").
 */
RS_String RS_Math::doubleToString(double value, double prec) {
	if (prec<1.0e-12) {
		std::cerr << "RS_Math::doubleToString: invalid precision\n";
		return "";
	}

    RS_String ret;
    RS_String exaStr;
    int dotPos;
    int num = RS_Math::round(value / prec);

    exaStr = RS_Math::doubleToString(prec, 10);
    dotPos = exaStr.find('.');

    if (dotPos==-1) {
        ret.sprintf("%d", RS_Math::round(num*prec));
    } else {
        int digits = exaStr.length() - dotPos - 1;
        ret = RS_Math::doubleToString(num*prec, digits);
    }

    return ret;
}