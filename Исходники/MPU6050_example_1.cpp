int main(int argc, char **argv) {
  printf("MPU6050 3-axis acceleromter example program\n");
  I2Cdev::initialize();
  MPU6050 accelgyro ;
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  
  accelgyro.initialize();

  if ( accelgyro.testConnection() ) 
    printf("MPU6050 connection test successful\n") ;
  else {
    fprintf( stderr, "MPU6050 connection test failed! something maybe wrong, continuing anyway though ...\n");
    //return 1;
  }
  // use the code below to change accel/gyro offset values
  /*
  printf("Updating internal sensor offsets...\n");
  // -76	-2359	1688	0	0	0
  printf("%i \t %i \t %i \t %i \t %i \t %i\n", 
	 accelgyro.getXAccelOffset(),
	 accelgyro.getYAccelOffset(),
	 accelgyro.getZAccelOffset(),
	 accelgyro.getXGyroOffset(),
	 accelgyro.getYGyroOffset(),
	 accelgyro.getZGyroOffset());
  accelgyro.setXGyroOffset(220);
  accelgyro.setYGyroOffset(76);
  accelgyro.setZGyroOffset(-85);
  printf("%i \t %i \t %i \t %i \t %i \t %i\n", 
	 accelgyro.getXAccelOffset(),
	 accelgyro.getYAccelOffset(),
	 accelgyro.getZAccelOffset(),
	 accelgyro.getXGyroOffset(),
	 accelgyro.getYGyroOffset(),
	 accelgyro.getZGyroOffset());
  */
  
  printf("\n");
  printf("  ax \t ay \t az \t gx \t gy \t gz:\n");
  while (true) {
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
//    printf("  %d \t %d \t %d \t %d \t %d \t %d\n", ax, ay, az, gx, gy, gz);

//    accelgyro.getAcceleration(&ax, &ay, &az);
//    printf("  %d \t %d \t %d \r", ax, ay, az);
    float axs = ax/16384.0;
    float ays = ay/16384.0;
    float azs = az/16384.0;

    float dxz = sqrt( axs*axs+azs*azs);
    float dyz = sqrt( ays*ays+azs*azs);

    float rotX = atan2(axs,dyz);
    float rotY = atan2(ays,dxz);
    printf("  %f \t %f \r", 180*rotX/3.14159, 180*rotY/3.14159);

    fflush(stdout);
//    fflush(stdout);
    bcm2835_delay(100);
  }
  return 1; 
}