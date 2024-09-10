void terminalDriver() {
  char commands[NUM_SAVED_COMMANDS][BUFFERSIZE];
  int lengths[NUM_SAVED_COMMANDS];
  int commandNum = 0, viewingNum = 0;

  char curCommand[BUFFERSIZE];
  int commandLength = 0, totalCommands = 0;

  char c;

  int trainSpeeds[80];
  int i;
  for(i=0; i<80; i++) {
    trainSpeeds[i] = 0;
  }
  int train[80];
  for(i=0; i<80; i++) {
    train[i] = -1;
  }

  Create(2, clockDriver);

  outputEscape("[2J[13;100r");
  refreshScreen();
  initializeTrack();
  moveCursor(13, 1);
  Putc(2, '>');
  while(true) {
    c = (char)Getc(2);
    switch(c) {
      case '\r':
	curCommand[commandLength] = '\0';
	strcpy(commands[commandNum], curCommand);
	lengths[commandNum] = commandLength;
	Putc(2, '\r');
	parseCommand(curCommand, trainSpeeds, train);
	commandNum++;
	commandNum %= NUM_SAVED_COMMANDS;
	viewingNum = commandNum;
	commands[commandNum][0] = '\0';
	commandLength = 0;
	if(totalCommands < NUM_SAVED_COMMANDS-1) totalCommands++;
	Putc(2, '>');
	break;
      case '\t':
	if(commandLength > 0) {
	  curCommand[commandLength] = '\0';
	  commandLength = tabComplete(curCommand);
	  outputEscape("[100D[K");
	  printf(">%s", curCommand);
	}
	break;
      case '\x8':
	if(commandLength > 0) {
	  commandLength--;
	  outputEscape("[1D[K");
	}
	break;
      case '\x1B':	//escape
	c = (char)Getc(2);
	c = (char)Getc(2);
	if(c == 'A') {
	  if(commandNum == viewingNum) {
	    curCommand[commandLength] = '\0';
	    strcpy(commands[commandNum], curCommand);
	    lengths[commandNum] = commandLength;
	  }
	  if(viewingNum != ((commandNum + NUM_SAVED_COMMANDS - totalCommands) 
					% NUM_SAVED_COMMANDS)) {
	    viewingNum += NUM_SAVED_COMMANDS - 1;
	    viewingNum %= NUM_SAVED_COMMANDS;
	    strcpy(curCommand, commands[viewingNum]);
	    commandLength = lengths[viewingNum];
	    outputEscape("[100D[K");
	    printf(">%s", curCommand);
	  }
	}else if(c == 'B') {
	  if(viewingNum != commandNum) {
	    viewingNum += 1;
	    viewingNum %= NUM_SAVED_COMMANDS;
	    strcpy(curCommand, commands[viewingNum]);
	    commandLength = lengths[viewingNum];
	    outputEscape("[100D[K");
	    printf(">%s", curCommand);
	  }
	}
	break;
      default:
	if(commandLength < BUFFERSIZE - 1) {
          curCommand[commandLength++] = c;
          Putc(2, c);
	}
        break;
    }
  }
}