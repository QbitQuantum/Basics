static int _refPoint_option(const copt_t * opt, const char * option, const copt_value_t * value)
{
	char * e;
	long double lat, lon;
	lat = strtold(value->v_str, &e);
	if (*e == ':'){
		lon = strtold(e + 1, &e);
		if (*e == 0){
			if (lat <= 90.0 &&  lat >= -90.0) lat *= 10000000.0; // degree
			_refLat = (int32_t)floorl(lat);
			if (lon <= 180.0 &&  lon >= -180.0) lon *= 10000000.0; // degree
			_refLon = (int32_t)floorl(lon);
			return 0;
		}
	}
	return -1;
}