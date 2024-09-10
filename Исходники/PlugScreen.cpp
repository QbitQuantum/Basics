void PlugScreen::waitForReceiver(NewRemoteCode receivedCode)
{
	//Clear What was there.
	myUTFT.setFont(SmallFont);
	myUTFT.clrScr();
	myUTFT.setColor(255, 0, 0);
	myUTFT.fillRect(0, 0, 220, 13);
	myUTFT.setColor(255, 255, 255);
	myUTFT.setBackColor(255, 0, 0);
	myUTFT.drawLine(0, 14, 320, 14);
	myUTFT.print("ID Set", CENTER, 1);
	myUTFT.setBackColor(0, 0, 0);

	setAddresstoEEPROM(receivedCode.address);
	if(plugDevice.lights)
	{
		EEPROM.write(EEPROM_LEARNED_LIGHTS_UNIT,receivedCode.unit);
		plugDevice.lights = false;
	}
	if(plugDevice.pump)
	{
		EEPROM.write(EEPROM_LEARNED_PUMP_UNIT,receivedCode.unit);
		plugDevice.pump = false;
	}
	if(plugDevice.heater)
	{
		EEPROM.write(EEPROM_LEARNED_HEATER_UNIT,receivedCode.unit);
		plugDevice.heater = false;
	}

	//unsigned long add = getAddress();
	String sAddress(receivedCode.address);
	String slightID(receivedCode.unit);

	myUTFT.print("The unit has been set to unit ", LEFT, 30);
	myUTFT.print(slightID, LEFT, 42);
	myUTFT.print("The Transmitting Address is", LEFT, 54);
	myUTFT.print(sAddress, LEFT, 66);
	myUTFT.print("You can now use the plug", LEFT, 78);
	myUTFT.print("**********************************", LEFT, 90);

	myButtons.deleteAllButtons();
	exitButton = -1;

	exitButton = myButtons.addButton( 10, 170, 145, 53, mainButton);
	myButtons.drawButton(exitButton);
	myUTFT.setBackColor (161,190,237);
	myUTFT.print("Back", 55, 195);
	myUTFT.setFont(BigFont);

}