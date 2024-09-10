void toByteArray_htonf(float value, Byte * barr) {
	float temp = htonf(value);
	memcpy (barr, &temp, sizeof(value));
}