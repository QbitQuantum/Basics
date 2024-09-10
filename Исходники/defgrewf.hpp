/** Verify the I2C connection.
 * Make sure the device is connected and responds as expected.
 * @return True if connection is valid, FALSE otherwise
 */
bool clMPU6050::TestConnection(){
	if(GetDeviceID() == 0x34) //0b110100; 8-bit representation in hex = 0x34
		return true;
	else
		return false;
}