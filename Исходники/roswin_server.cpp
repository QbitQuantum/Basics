float Float(char unsigned *const p)
{
	float val;

	memcpy(&val,p,sizeof val);

	return val;
}