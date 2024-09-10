/**********************************************************
 * GetTemperature
 *  Gets the current temperature from the sensor.
 *
 * @return float - The local temperature in degrees C
 **********************************************************/
float LibTempTMP421::GetTemperature(void) {
    uint8_t in[2];
    float frac = 0.0;
    uint8_t bit;

    setPtrLoc(0x00);                //high-byte
    in[0] = getRegisterValue();

    setPtrLoc(0x10);                //low-byte
    in[1] = getRegisterValue();
    in[1] >>=4;                     //shift-off the unused bits

    /* Assemble the fraction */
    bit = in[1] & 0x01;
    frac += (bit * 0.5) * (bit * 0.5) * (bit * 0.5) * (bit * 0.5);

    in[1] >>= 1;
    bit = in[1] & 0x01;
    frac += (bit * 0.5) * (bit * 0.5) * (bit * 0.5);

    in[1] >>= 1;
    bit = in[1] & 0x01;
    frac += (bit * 0.5) * (bit * 0.5);

    in[1] >>= 1;
    bit = in[1] & 0x01;
    frac += (bit * 0.5);

    /* Add the MSB to the fraction */
    frac += in[0];

	/* frac is unsigned, make it signed to allow for negative temps */
	if (frac > 128.0)
		frac -= 256;
    return frac;
}