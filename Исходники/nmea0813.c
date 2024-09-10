int32_t processGPGGA (int8_t count, int8_t *f[],
                       struct gps_device_t * session)
{
	double d, m;
	double lat;
	double lon;
	int8_t *p;

	session->nmea.type = TYPE_GPGGA;
	session->nmea.nmea_u.gpgga.time.hour = DD(f[0]);
	session->nmea.nmea_u.gpgga.time.min = DD(&f[0][2]);
	session->nmea.nmea_u.gpgga.time.sec = DD(&f[0][4]);

	/*double d, m;
	double lat;*/
	lat = atof(f[1]);
    m = 100.0 * modf(lat / 100.0, &d);
    lat = d + m / 60.0;
    if (f[2][0] == 'S')
        lat = -lat;
	session->nmea.nmea_u.gpgga.lat = lat;

	//double lon;
	lon = atof(f[3]);
    m = 100.0 * modf(lon / 100.0, &d);
    lon = d + m / 60.0;
    if (f[4][0] == 'S')
        lon = -lon;
	session->nmea.nmea_u.gpgga.lon = lon;

	switch(f[5][0]){
		case '0':
		session->nmea.nmea_u.gpgga.gps_quality = FIX_NOT_AVAIL;	
		break;

		case '1':
		session->nmea.nmea_u.gpgga.gps_quality = FIX;
		break;

		case '2':
		session->nmea.nmea_u.gpgga.gps_quality = DIFF_FIX;
		break;

		default:
		session->nmea.nmea_u.gpgga.gps_quality = FIX_UNDEF;	/* unknow */
		break;
	}

	session->nmea.nmea_u.gpgga.nsv = atoi(f[6]);
	session->nmea.nmea_u.gpgga.hdp = atof(f[7]);
	session->nmea.nmea_u.gpgga.antenna = atof(f[8]);
	session->nmea.nmea_u.gpgga.geoidal = atof(f[10]);
	session->nmea.nmea_u.gpgga.age = atof(f[12]);

	//int8_t *p;
	p = f[13];
	while(*p != '*')
		p++;
	*p = '\0';
	session->nmea.nmea_u.gpgga.stationID = atof(f[13]);

	return true;
}