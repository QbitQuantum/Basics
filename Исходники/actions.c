void adjust_speed(FLOAT *speedx, FLOAT *speedy, double adjust)
{
	double angle;

	angle = ATAN2(*speedy, *speedx);
	*speedx += (FLOAT)(adjust * COS(angle));
	*speedy += (FLOAT)(adjust * SIN(angle));
}