uint8_t initializeMPU(int16_t *accelOffsetX, int16_t *accelOffsetY,int16_t *accelOffsetZ, int16_t *currAccelX,int16_t *currAccelY,int16_t *currAccelZ){

/*MUST DECIDE WHETHER TO USE*/
/*ERROR CODES:
1: no connection of MPU in hardware
2: no DMP initialization
*/
uint8_t initErrorCode=0;

// ================================================================
// ===                      INITIAL SETUP                       ===
// ================================================================

  // CONNECT DEVICE TO I2C BUS

// join I2C bus (I2Cdev library doesn't do this automatically)
  Wire.begin();

//  Serial.begin(38400);
//  while (!Serial);
//
//  // initialize device
//  Serial.println(F("Initializing I2C devices..."));
  mpu.initialize();


  // TEST MPU CONNECTION

//  // verify connection
  if( !(mpu.testConnection()) ){ /*Added MPU connection check*/
    initErrorCode=1;
    return initErrorCode;
  }
//  Serial.println(F("Testing device connections..."));
//  Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

  // wait for ready
//  Serial.println(F("\nSend any character to begin DMP programming and demo: "));
//  while (Serial.available() && Serial.read()); // empty buffer
//  while (!Serial.available());                 // wait for data
//  while (Serial.available() && Serial.read()); // empty buffer again


  // CONFIGURE MPU SETTINGS

  //Low pass filtering
  //mpu.setDLPFMode(1);

  //Set tap detection on XYZ axes
  /* dmp_set_tap_thresh(1,500);
  dmp_set_tap_thresh(2,500);
  dmp_set_tap_thresh(4,500); */

  
  
  // LOAD AND CONFIGURE THE DMP
  uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
//  Serial.println(F("Initializing DMP..."));
    devStatus=mpu.dmpInitialize();

  // make sure it worked (returns 0 if so)
  if (devStatus == 0) {
    // turn on the DMP, now that it's ready
//    Serial.println(F("Enabling DMP..."));
    mpu.setDMPEnabled(true);

    // enable Arduino interrupt detection
//    Serial.println(F("Enabling interrupt detection (Arduino external interrupt 2)..."));
    attachInterrupt(0, dmpDataReady, RISING);
    

  //mpuIntStatus = mpu.getIntStatus();
//    Serial.println("MPU int status:");
//    Serial.println(mpuIntStatus);

    // set our DMP Ready flag so function knows it's okay to use it
//    Serial.println(F("DMP ready!"));
    dmpReady = true;

    // get expected DMP packet size for later comparison
    packetSize = mpu.dmpGetFIFOPacketSize();
    
  } else {
    /*Failed to intialize dmp*/
    // 1 = initial memory load failed
    // 2 = DMP configuration updates failed
    // (if it's going to break, usually the code will be 1)
//    Serial.print(F("DMP Initialization failed (code "));
//    Serial.print(devStatus);
//    Serial.println(F(")"));
    initErrorCode=2;
    return initErrorCode; 

  }



  // RUN CALIBRATION

  // According to manual, user should place the cube on table for 10 seconds to allow for accelerometer to calibrate
  // Accelerometer calibration: apply offsets

  int16_t tempOffsetX=0;  /*CHANGED TO INT16*/
  int16_t tempOffsetY=0;
  int16_t tempOffsetZ=0;


  //Get offset as average over 10 seconds
  uint8_t count=0;

  *accelOffsetX=0;
  *accelOffsetY=0;
  *accelOffsetZ=0;
  unsigned long startTime=millis();
  while ((millis()-startTime)<10000){
    mpuMonitor(currAccelX,currAccelY,currAccelZ); /*Class call added*/
    tempOffsetX=(tempOffsetX+*(currAccelX)/2048);
    tempOffsetY=(tempOffsetY+*(currAccelY)/2048);
    tempOffsetZ=(tempOffsetZ+*(currAccelZ)/2048);
    count++;
  }

  tempOffsetX=2048*tempOffsetX/count;
  tempOffsetY=2048*tempOffsetY/count;
  tempOffsetZ=2048*tempOffsetZ/count;

  *accelOffsetX=tempOffsetX;
  *accelOffsetY=tempOffsetY;
  *accelOffsetZ=tempOffsetZ;

  //pinMode(LED_PIN,output); /*No more LEDs for failure checks*/

  return initErrorCode;
}