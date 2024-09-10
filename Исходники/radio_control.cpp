short processRadioMessages(char *buf, short lenth) {
  short cmdIndex = -1;
  char cmd[lenth];
  char token2[lenth];
  short i = 0;
  short changeLeve = 0;
  short parameter = 0;
  float parameterF = 0.0;
  float rollSpShift = 0;
  float pitchSpShift = 0;
  float yawShiftValue = 0;
  float throttlePercentage = 0;
  static unsigned long  radio_last_tv3 = 0;

#if 0
   unsigned long tv=millis();
  Serial.println(tv-radio_last_tv3);
   radio_last_tv3=tv;
  // Serial.println(buf);
#endif

  resetPacketAccCounter();
  

  memset(cmd, '\0', sizeof(cmd));

  for (i = 1; buf[i] != '#'; i++) {
    cmd[i - 1] = buf[i];
  }
 
  qToken(cmd, token2,lenth, 0);
  cmdIndex = atoi(token2);


  switch (cmdIndex) {
    case ON_OFF_FLY_SYSTEM_MESSAGE:

	  qToken(cmd, token2,lenth,ON_OFF_FLY);
      parameter = atoi(token2);

      if (1 == parameter) {
          enableFlySystem();
      } else {
        disenableFlySystem();
      }

      break;
    case PILOT_CONTROL_MESSAGE:
     // printf("%s\n",buf);

	  qToken(cmd, token2,lenth, THROTTLE_LEVEL);
      parameter = atoi(token2);
	  
      qToken(cmd, token2,lenth, ROLL_SP_SHIFT);
      rollSpShift = atof(token2);

      qToken(cmd, token2,lenth, PITCH_SP_SHIFT);
      pitchSpShift = atof(token2);

       qToken(cmd, token2,lenth, YAW_SP_SHIFT);
      yawShiftValue = atof(token2);
      //printf("factor=%d\n",(int)(((float)(parameter-100)/(float)100)*(float)(MAX_POWER_LEVEL-MIN_POWER_LEVEL)));
      //printf("parameter=%d\n",parameter);
      throttlePercentage = (float)parameter / 100.f;
      parameter = getMinPowerLevel()
                  + (int) (throttlePercentage
                           * (float) (getMaxPowerLeve()
                                      - getMinPowerLevel())); /*(100~200)*10=1000~2000 us*/
      //printf("getMaxPowerLeveRange()- getMinPowerLeveRange()=%f\n",getMaxPowerLeve()- getMinPowerLevel());
      //printf("parameter=%d\n",parameter);

      if (parameter > getMaxPowerLeve()
          || parameter < getMinPowerLevel()) {
         printf( "break\n");
        break;
      }
      if (true == flySystemIsEnable()) {

        setThrottlePowerLevel(parameter);

        if (getMinPowerLevel() == parameter) {
          //printf("STOP\n");
          resetPidRecord(&rollAttitudePidSettings);
          resetPidRecord(&pitchAttitudePidSettings);
          resetPidRecord(&yawAttitudePidSettings);
          resetPidRecord(&rollRatePidSettings);
          resetPidRecord(&pitchRatePidSettings);
          resetPidRecord(&yawRatePidSettings);
          setYawCenterPoint(0);
          setPidSp(&yawAttitudePidSettings, 321.0);

        } else {
          if (getPidSp(&yawAttitudePidSettings) == 321.0) {
             printf( "START Flying\n");
            setYawCenterPoint(getYaw());
            setPidSp(&yawAttitudePidSettings, 0);
          }
          setPidSp(&rollAttitudePidSettings,
                   LIMIT_MIN_MAX_VALUE(rollSpShift, -getAngularLimit(),
                                       getAngularLimit()));
          setPidSp(&pitchAttitudePidSettings,
                   LIMIT_MIN_MAX_VALUE(pitchSpShift, -getAngularLimit(),
                                       getAngularLimit()));
          setYawCenterPoint(getYawCenterPoint() + (yawShiftValue * 1.0));

        }

      }

      //printf("throttle=%d roll=%f pitch=%f\n",parameter,rollSpShift,pitchSpShift);

      break;



    case SYSTEM_SETTING_MESSAGE:
       printf( "%s " , buf);

	  qToken(cmd, token2,lenth, ANAGULAR_VELOVITY_LIMIT);
      parameterF = atof(token2);
      if (parameterF == 0) {
        parameterF = 1;
      }
      setGyroLimit(parameterF);
	  printf( "Angular Velocity Limit: %4.3f\n",getGyroLimit());
      /***/

	  qToken(cmd, token2,lenth, ROLL_CALIBRATION);
      parameterF = atof(token2);
      setPidSpShift(&rollAttitudePidSettings, parameterF);
	  printf( "Roll Angular Calibration: %4.3f\n",getPidSpShift(&rollAttitudePidSettings));

      /***/

	  qToken(cmd, token2,lenth, PITCH_CALIBRATION);
      parameterF = atof(token2);
      setPidSpShift(&pitchAttitudePidSettings, parameterF);
	  printf( "Pitch Angular Calibration: %4.3f\n",getPidSpShift(&pitchAttitudePidSettings));


      break;

    case PID_SETTING_MESSAGE:
	
       printf("%s\n", buf);

    
	  qToken(cmd, token2,lenth, ATTITUDE_ROLL_P);
      parameterF = atof(token2);
      setPGain(&rollAttitudePidSettings, parameterF);
       printf( "Attitude Roll P Gain=%f\n", getPGain(&rollAttitudePidSettings));

      
      qToken(cmd, token2,lenth, ATTITUDE_ROLL_I);
      parameterF = atof(token2);
      setIGain(&rollAttitudePidSettings, parameterF);
      printf("Attitude Roll I Gain=%f\n", getIGain(&rollAttitudePidSettings));

    
       qToken(cmd, token2,lenth,ATTITUDE_ROLL_I_LIMIT );
      parameterF = atof(token2);
      setILimit(&rollAttitudePidSettings, parameterF);
       printf( "Attitude Roll I Output Limit=%f\n",
                getILimit(&rollAttitudePidSettings));

       qToken(cmd, token2,lenth,ATTITUDE_ROLL_D );
      parameterF = atof(token2);
      setDGain(&rollAttitudePidSettings, parameterF);
       printf("Attitude Roll D Gain=%f\n", getDGain(&rollAttitudePidSettings));

       qToken(cmd, token2,lenth,ATTITUDE_PITCH_P );
      parameterF = atof(token2);
      setPGain(&pitchAttitudePidSettings, parameterF);
       printf( "Attitude Pitch P Gain=%f\n", getPGain(&pitchAttitudePidSettings));

       qToken(cmd, token2,lenth, ATTITUDE_PITCH_I);
      parameterF = atof(token2);
      setIGain(&pitchAttitudePidSettings, parameterF);
      printf( "Attitude Pitch I Gain=%f\n", getIGain(&pitchAttitudePidSettings));

       qToken(cmd, token2,lenth, ATTITUDE_PITCH_I_LIMIT);
      parameterF = atof(token2);
      setILimit(&pitchAttitudePidSettings, parameterF);
      printf( "Attitude Pitch I Output Limit=%f\n",
                getILimit(&pitchAttitudePidSettings));

       qToken(cmd, token2,lenth, ATTITUDE_PITCH_D);
      parameterF = atof(token2);
      setDGain(&pitchAttitudePidSettings, parameterF);
       printf( "Attitude Pitch D Gain=%f\n", getDGain(&pitchAttitudePidSettings));


       qToken(cmd, token2,lenth,ATTITUDE_YAW_P );
      parameterF = atof(token2);
      setPGain(&yawAttitudePidSettings, parameterF);
       printf( "Attitude Yaw P Gain=%f\n", getPGain(&yawAttitudePidSettings));

       qToken(cmd, token2,lenth, ATTITUDE_YAW_I);
      parameterF = atof(token2);
      setIGain(&yawAttitudePidSettings, parameterF);
       printf( "Attitude Yaw I Gain=%f\n", getIGain(&yawAttitudePidSettings));

       qToken(cmd, token2,lenth, ATTITUDE_YAW_I_LIMIT);
      parameterF = atof(token2);
      setILimit(&yawAttitudePidSettings, parameterF);
       printf( "Attitude Yaw I Output Limit=%f\n", getILimit(&yawAttitudePidSettings));
	   
       qToken(cmd, token2,lenth, ATTITUDE_YAW_D);
      parameterF = atof(token2);
      setDGain(&yawAttitudePidSettings, parameterF);
       printf( "Attitude Yaw D Gain=%f\n", getDGain(&yawAttitudePidSettings));

       qToken(cmd, token2,lenth, RATE_ROLL_P);
      parameterF = atof(token2);
      setPGain(&rollRatePidSettings, parameterF);
       printf( "Rate Roll P Gain=%f\n", getPGain(&rollRatePidSettings));
    
       qToken(cmd, token2,lenth, RATE_ROLL_I);
      parameterF = atof(token2);
      setIGain(&rollRatePidSettings, parameterF);
       printf( "Rate Roll I Gain=%f\n", getIGain(&rollRatePidSettings));
     
       qToken(cmd, token2,lenth, RATE_ROLL_I_LIMIT);
      parameterF = atof(token2);
      setILimit(&rollRatePidSettings, parameterF);
       printf( "Rate Roll I Output Limit=%f\n",
                getILimit(&rollRatePidSettings));
      
       qToken(cmd, token2,lenth,RATE_ROLL_D);
      parameterF = atof(token2);
      setDGain(&rollRatePidSettings, parameterF);
      printf( "Rate Roll D Gain=%f\n", getDGain(&rollRatePidSettings));                                                                                                                                                                                                                                                     

    
       qToken(cmd, token2,lenth,RATE_PITCH_P );
      parameterF = atof(token2);
      setPGain(&pitchRatePidSettings, parameterF);
      printf( "Rate Pitch P Gain=%f\n", getPGain(&pitchRatePidSettings));
   
       qToken(cmd, token2,lenth,RATE_PITCH_I );
      parameterF = atof(token2);
      setIGain(&pitchRatePidSettings, parameterF);
       printf( "Rate Pitch I Gain=%f\n", getIGain(&pitchRatePidSettings));
     
       qToken(cmd, token2,lenth,RATE_PITCH_I_LIMIT );
      parameterF = atof(token2);
      setILimit(&pitchRatePidSettings, parameterF);
       printf( "Rate Pitch I Output Limit=%f\n",
                getILimit(&pitchRatePidSettings));
  
       qToken(cmd, token2,lenth, RATE_PITCH_D);
      parameterF = atof(token2);
      setDGain(&pitchRatePidSettings, parameterF);
       printf( "Rate Pitch D Gain=%f\n", getDGain(&pitchRatePidSettings));

    
     qToken(cmd, token2,lenth,RATE_YAW_P );
      parameterF = atof(token2);
      setPGain(&yawRatePidSettings, parameterF);
       printf( "Rate Yaw P Gain=%f\n", getPGain(&yawRatePidSettings));
     
       qToken(cmd, token2,lenth, RATE_YAW_I);
      parameterF = atof(token2);
      setIGain(&yawRatePidSettings, parameterF);
      printf( "Rate Yaw I Gain=%f\n", getIGain(&yawRatePidSettings));
    
       qToken(cmd, token2,lenth,RATE_YAW_I_LIMIT );
      parameterF = atof(token2);
      setILimit(&yawRatePidSettings, parameterF);
       printf("Rate Yaw I Output Limit=%f\n",
                getILimit(&yawRatePidSettings));

       qToken(cmd, token2,lenth, RATE_YAW_D);
      parameterF = atof(token2);
      setDGain(&yawRatePidSettings, parameterF);
       printf( "Rate Yaw D Gain=%f\n", getDGain(&yawRatePidSettings));
      break;
	  default:
	  	printf("unknow message\n");
  }

}