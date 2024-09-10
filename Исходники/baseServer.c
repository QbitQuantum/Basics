void dispatchFixedMessage(int operation, unsigned long param)
{
  if (VERBOSE) {
    fprintf(stderr,"Calling base operation %d\n",operation);
  }

  confirmCommandToClient(operation, param); /* sends a message back to all
					     * baseClients, confirming the
					     * command, sebastian 7-97 */

  switch(operation) {
    
    /**** GENERAL ****/ 
  case BASE_baseKill:		baseKill(); break;	
  case BASE_loadHeading:	loadHeading(param); break;	
  case BASE_loadPosition:	loadPosition(param); break;	
  case BASE_statusReportData:	statusReportData(param);break;
  case BASE_statusReportPeriod:	statusReportPeriod(param);break;
  case BASE_batteryVoltage:	batteryVoltage();break;
  case BASE_batteryCurrent:	batteryCurrent();break;

  case BASE_watchdogTimer:	watchdogTimer(param);break;
  case BASE_assumeWatchdog:	assumeWatchdog();break;


    /**** ROTATION ****/ 
  case BASE_rotateLimp:		rotateLimp(); break;
  case BASE_rotateHalt:		rotateHalt(); break;
  case BASE_rotateVelocityPos:	rotateVelocityPos(); break;	
  case BASE_rotateVelocityNeg:  rotateVelocityNeg(); break;	
  case BASE_rotateRelativePos:  rotateRelativePos(param); break;	
  case BASE_rotateRelativeNeg: 	rotateRelativeNeg(param); break;	
  case BASE_rotateTorquePos:	rotateTorquePos(param); break;	
  case BASE_rotateTorqueNeg: 	rotateTorqueNeg(param); break;	
  case BASE_rotatePowerPos:	rotatePowerPos(param); break;	
  case BASE_rotatePowerNeg: 	rotatePowerNeg(param); break;	
  case BASE_rotateToPosition: 	rotateToPosition(param); break;	
  case BASE_findRotIndex:
    if (bRobot.base_hasIndex) {
      findRotIndex();
    }
    else {
      sendClientFixed(BASE_indexReport, 0xFFFFFF);
    }
    break;

  case BASE_setRotateVelocity:	setRotateVelocity(param); break;	
  case BASE_setRotateAcceleration: setRotateAcceleration(param); break;	
  case BASE_setRotateFriction: 	setRotateFriction(param); break;	
  case BASE_setRotateSlope: 	setRotateSlope(param); break;	
  case BASE_setRotateTorque: 	setRotateTorque(param); break;	
  case BASE_setRotateZero: 	setRotateZero(param); break;	

  case BASE_rotateCurrent:	rotateCurrent(); break;	
  case BASE_rotateWhere:	rotateWhere(); break;	


    /**** TRANSLATION ****/ 
  case BASE_translateLimp:		translateLimp(); break;
  case BASE_translateHalt:		translateHalt(); break;
  case BASE_translateVelocityPos:  	translateVelocityPos(); break;	
  case BASE_translateVelocityNeg:  	translateVelocityNeg(); break;	
  case BASE_translateRelativePos:  	translateRelativePos(param); break;
  case BASE_translateRelativeNeg:  	translateRelativeNeg(param); break;
  case BASE_translateTorquePos:		translateTorquePos(param); break;
  case BASE_translateTorqueNeg: 	translateTorqueNeg(param); break;
  case BASE_translatePowerPos:		translatePowerPos(param); break;
  case BASE_translatePowerNeg: 		translatePowerNeg(param); break;
  case BASE_translateToPosition: 	translateToPosition(param); break;
  case BASE_setTranslateVelocity:	setTranslateVelocity(param); break;
  case BASE_setTranslateAcceleration: 	setTranslateAcceleration(param); break;
  case BASE_setTranslateSlope: 		setTranslateSlope(param); break;
  case BASE_setTranslateTorque: 	setTranslateTorque(param); break;
  case BASE_setTranslateZero: 		setTranslateZero(param); break;

  case BASE_translateCurrent:		translateCurrent(); break;	
  case BASE_translateWhere:		translateWhere(); break;	

  /**** SONARS ****/
  case BASE_sonarStart:                 SIM_sonarStart(); break;
  case BASE_sonarStop:                  SIM_sonarStop(); break;

  /**** Odometry stuff ****/
  case BASE_odometryChangeX:
    ntohf(param, bOriginX);
    sendClientFixed(BASE_odometryChangeX, param);
    break;
  case BASE_odometryChangeY:
    ntohf(param, bOriginY);
    sendClientFixed(BASE_odometryChangeY, param);
    break;
  case BASE_odometryChangeH:
    ntohf(param, bOriginHeading);
    sendClientFixed(BASE_odometryChangeH, param);
    break;

  /**** Odometry lock requests ****/
  case BASE_requestOdometryLock:
    requestOdometryLock((unsigned short)param);
    break;
  case BASE_releaseOdometryLock:
    releaseOdometryLock();
    break;

  default: 
    fprintf(stderr, "BaseServer: Operation %d not yet implemented.\n",
            operation); 	
  }
  
  if (VERBOSE) {
    fprintf(stderr,"Operation %d complete\n",operation);
  }
}