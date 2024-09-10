/*
During “Functional Test Mode” only “Raw sensor” and “VOC_short” data are available. “VOC_short” is
an image of sensor reactivity and can then be used for functional test.
Out of this initial period, the device will have the I2C data CO2 equivalent [ppm] and tVOC equivalent
referred to the isobutylene sensitivity unit [ppb].

D1:Data_byte_1: CO2_equ: [13…242] -> CO2_equ [ppm] = (D1 -13) * (1600/229) + 400
D2: Data_byte_2: VOC_short [13…242]
D3: Data_byte_3: tVOC: [13…242] -> tVOC [ppb] = (D3 -13) * (1000/229)
D4: Data_byte_4: Raw sensor first byte (LSB)
D5: Data_byte_5: Raw sensor second byte
D6: Data_byte_6: Raw sensor third byte (MSB) -> Resistor value [W] = 10*(D4 + (256*D5) + (65536*D6))

return CO2 equivalent [ppm] and tVOC equivalent referred to the isobutylene sensitivity unit [ppb].
 *
 */
bool VZ89::read(float *co2, uint8_t *reactivity, float *tvoc) {
	uint8_t data[6];
	readRaw(data);
	if (data[0] < 13 || data[1] < 13 || data[2] < 13) return false;
	// convert data to meaningful values
	*co2 = (data[0] - 13) * (1600.0 / 229) + 400; // ppm: 400 .. 2000
	*reactivity = data[1];
	*tvoc = (data[2] - 13) * (1000.0/229); // ppb: 0 .. 1000

	//uint32_t resistor = 10 * (data[3] +256 * data[4] + 65536 * data[5]);
	return true;
}