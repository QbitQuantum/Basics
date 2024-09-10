void ToucheEngine::op_setFlag() {
	debugC(9, kDebugOpcodes, "ToucheEngine::op_setFlag()");
	uint16 flag = _script.readNextWord();
	int16 val = *_script.stackDataPtr;
	_flagsTable[flag] = val;
	switch (flag) {
	case 104:
		_currentKeyCharNum = val;
		break;
	case 611:
		if (val != 0)
			quitGame();
		break;
	case 612:
		_flagsTable[613] = getRandomNumber(val);
		break;
	case 614:
	case 615:
		_fullRedrawCounter = 1;
		break;
	case 618:
		showCursor(val == 0);
		break;
	case 619:
		debug(0, "Unknown music flag %d", val);
		break;
	}
}