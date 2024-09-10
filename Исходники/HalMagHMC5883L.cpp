/** @brief Execute the driver */
bool HalMagHMC5883L::sample(
		math::Vector3i& compassMeas_U)
{
	bool result = false;

	/* Read data */
	if (0<=readRaw(compassMeas_U))
	{
		/* Command a new read */
		if (0==commandSample())
		{
			result = true;
		}
	}
	return result;
}