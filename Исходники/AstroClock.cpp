void AstroClock::convert(uint32_t timestamp, float ra, float dec, float* alt,
		float* az) {
	float lstd = getLSTd(convertJ2000(timestamp));
	float ha = lstd - ra;
	while (ha < 0)
		ha += 360.0;

	float sinAlt = SIN(dec) * SIN(lat) + COS(dec) * COS(lat) * COS(ha);
	*alt = ASIN(sinAlt);

	float cosA = //
			(SIN(dec) - SIN(*alt) * SIN(lat)) //
			/ (COS(*alt) * COS(lat));

	float a = ACOS(cosA);

	if (SIN(ha) < 0)
		*az = a;
	else
		*az = 360.0 - a;
}