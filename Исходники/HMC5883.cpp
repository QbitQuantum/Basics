/**
*@param[in] x X magnetometer value.
*@param[in] y Y magnetometer value.
*/
float HMC5883::getHeadingRadians(int x, int y)
{	
	return (atan2(y, x) + M_PI);
}