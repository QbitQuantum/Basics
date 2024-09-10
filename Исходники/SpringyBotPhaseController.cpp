double Vector::angle(Vector vector) {
	double out = 0;
    if (length() && vector.length())
    {
        double tmp = dot(vector) / ( length() * vector.length() );
        if (tmp > 1)
            out = acos(1);
        else if  (tmp < -1)
        	out = acos(-1);
        else
            out = acos(tmp);
    }
    else
        out = 0.0;

    return out;
}