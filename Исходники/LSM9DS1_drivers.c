void readAccel1v1(accel *a)
{
	uint8_t temp[6]; // We'll read six bytes from the accelerometer into temp
	int index = 0;

	xgReadBytes(OUT_X_L_XL, temp, 6); // Read 6 bytes, beginning at OUT_X_L_XL

	ax = (temp[1] << 8) | temp[0]; // Store x-axis values into ax
	ay = (temp[3] << 8) | temp[2]; // Store y-axis values into ay
	az = (temp[5] << 8) | temp[4]; // Store z-axis values into az

	if (_autoCalc)
	{
		ax -= aBiasRaw[X_AXIS];
		ay -= aBiasRaw[Y_AXIS];
		az -= aBiasRaw[Z_AXIS];
	}

	ax = calcAccel(ax);
	ay = calcAccel(ay);
	az = calcAccel(az);


	if((accelMeasurementsNum > 99) && (measurementsLSMRead == 0))
	{
		measurementsLSMRead = 1;
		/*a[accelMeasurementsNum].ax = ax;
		a[accelMeasurementsNum].ay = ay;
		a[accelMeasurementsNum].az = az;*/

		return;
	}

	a[accelMeasurementsNum].ax = ax;
	a[accelMeasurementsNum].ay = ay;
	a[accelMeasurementsNum].az = az;

	accelMeasurementsNum++;
	/*a[accelMeasurementsNum].ax = ax;
	a[accelMeasurementsNum].ay = ay;
	a[accelMeasurementsNum].az = az;

	accelMeasurementsNum++;*/

	toAscii(ax, &index);
	toAscii(ay, &index);
	toAscii(az, &index);

	/*lk[0] = '0' + ax;
	lk[1] = '0' + ay;
	lk[2] = '0' + az;*/
	for(int k = 0; k < 6; k++)
	{
		accelerationXYZ[k] = 0;
	}
}