void ECCalibrateScreen::lowCalibration()
{
	myUTFT.clrScr();
	myUTFT.setColor(255, 0, 0);
	myUTFT.fillRect(0, 0, 220, 13);
	myUTFT.setColor(255, 255, 255);
	myUTFT.setBackColor(255, 0, 0);
	myUTFT.drawLine(0, 14, 320, 14);
	myUTFT.print("EC Calibration", CENTER, 1);
	myUTFT.setBackColor(0, 0, 0);

	myUTFT.print("Calibrate now with the low side liquid", LEFT, 30);
	myUTFT.print("Place the sensor in the 220Us", LEFT, 42);
	myUTFT.print("calibration liquid.  This process", LEFT, 54);
	myUTFT.print("will take 5 mins to complete", LEFT, 66);
	myUTFT.print("Wait for process to finish before ", LEFT, 78);
	myUTFT.print("removing the sensor from the liquid", LEFT, 90);
	myUTFT.print("", LEFT, 102);
	myUTFT.print("************************************", LEFT, 114);
	myUTFT.print("Touch screen to continue", CENTER, 162);

	SwaitForTouch();
	myUTFT.clrScr();

	inputstring = "C\r";  //set in continious mode

	String thisSt = String(12);
	myUTFT.print("Calibration in Progress", CENTER, 30);
	myUTFT.print("Seconds left until ready " + thisSt, CENTER, 42);
	simpleTimer.setTimer(3000, updateLowWaitScreen, /*100*/ 4); //Update screen every 3 seconds for 5 minues.


	//delay(2000);  //Wait 2 seconds -- make 5mins
	//Serial3.print(inputstring); //send command to sensor.
	//inputstring = "Z2\r";  //set the sensor at this value.
	//Serial3.print(inputstring); //need to send twice??


}