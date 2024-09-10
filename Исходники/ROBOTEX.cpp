void listenToCommands() {
	initCOMPort();
	initUSBRadio();
	lastSpeedSentTimer.start();
	HANDLE waitHandles[3] = { startSignal, osStatusDongle.hEvent };

	stateGoal = goalOnRight;
	stateBallSeen = ballOnRight;
	while (true) {
		float floorX, floorY;
		int currentx, currenty;
		findNearestFloorBall(floorX, floorY, currentx, currenty);
		float angle = atanf(floorY / floorX) * 180.0 / PI;

		swprintf_s(buffer, L"NX %.2f \n NY %.2f\n ang %.2f", floorX, floorY, angle);
		SetWindowText(infoGUI, buffer);

		swprintf_s(buffer, L"greencount %d", fieldGreenPixelCountShare);
		SetWindowText(infoGUI3, buffer);

		if (hCOMDongle != INVALID_HANDLE_VALUE) {
			if (lastSpeedSentTimer.time() > 0.5) { //if we send the speeds too often we get communication timeouts
				setSpeedBoth(currentDrivingState);
				lastSpeedSentTimer.start();
			}
		}
		switch (WaitForMultipleObjects(2, waitHandles, FALSE, 50)) {
		//case WAIT_OBJECT_0:
		//	prints(L"radio event %X\n", dwCommEvent);
		//	//receiveCommand();
		//	//WaitCommEvent(hCOMRadio, &dwCommEvent, &osStatus);
		//	break;
		case WAIT_OBJECT_0:
			prints(L"Start signal arrived.\n");
			SetWindowText(stateStatusGUI, L"started");
			dribblerON();
			play();
			dribblerOFF();
			//discharge();
			break;
		case WAIT_OBJECT_0 + 1: //info from the main board controller
			//prints(L"main board COM event %X\n", dwCommEventDongle);
			handleMainBoardCommunication();
			WaitCommEvent(hCOMDongle, &dwCommEventDongle, &osStatusDongle); //listen to new events, ie beginning character
			break;
		}
		receiveCommand();
	}
}