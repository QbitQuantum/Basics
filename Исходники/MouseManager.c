void solveMaze()
{		
	//Reset maze to 0
	initializeMaze(&maze);
		
	//We Know at the starting point, there's something behind us
	setN(&maze[0][0], 1);
	mouse.direction.x = 0;
	mouse.direction.y = -1;
	mouse.x = 0;
	mouse.y = 0;

	//Disable the mouse for now
	enableDrive(0);
	turnOnTimers(0, 0);
	
	int areWeSearching = UserInterfaceIntro();
	
	//Does the user want to skip the search phase and load a maze from EEPROM
	if(areWeSearching)
	{
		/* SEARCH MAZE */
		for(int i = 0; i < 10; i++)
		{
			turnOnLeds(7);
			_delay_ms(10);
			turnOnLeds(0);
			_delay_ms(90);
		}
		
		//Init Mouse
		enableDrive(1);
		turnOnTimers(1, 1);
		setDirection(0, 0);
		
		//Update Sensors
		updateSensors();
		updateSensors();	
		updateWalls();
		
		//Go Forward first block
		mouse.IR_LONG_CHECK_LEFT = 2;
		mouse.IR_LONG_CHECK_RIGHT = 2;
		straight(480, 0, mouse.maxVelocity, mouse.maxVelocity, mouse.acceleration, mouse.deceleration);
		mouse.x += mouse.direction.x;
		mouse.y -= mouse.direction.y;	
		
		/* SEARCH */
		InitialSearchRun();
		
			//Search is Complete!
			updateWalls();
			
			/* TURN AROUND */
			mouse.rightMotor.stepCount = mouse.leftMotor.stepCount = 0;	
			StopFromSpeedHalf();
			mouse.rightMotor.stepCount = mouse.leftMotor.stepCount = 0;	
			moveBackwards();			
				
			//Save Maze to EEPROM
			saveCurrentMaze();
			writeMemByte(MOUSE_DIRECTION, firstTurn);
		
			mouse.rightMotor.stepCount = mouse.leftMotor.stepCount = 0;	
			moveForwardHalf();
			
			//Current Mouse Direction
			int dirx = mouse.direction.x;
			int diry = mouse.direction.y;
			
			//Reverse and go back
			mouse.direction.x  = -dirx;
			mouse.direction.y = -diry;
			
			//Set Position to next block
			mouse.x += mouse.direction.x;
			mouse.y -= mouse.direction.y;
		
		/* RETURN SEARCH*/
		ReturnSearchRun();
			
			//Turn Around
			mouse.rightMotor.stepCount = mouse.leftMotor.stepCount = 0;	
			StopFromSpeedHalf();
			mouse.rightMotor.stepCount = mouse.leftMotor.stepCount = 0;	
			moveBackwards();
		
			//Save Maze to EEPROM
			saveCurrentMaze();
			writeMemByte(MOUSE_DIRECTION, firstTurn);
		
		/* PICK UP AND PLACE MOUSE */
		enableDrive(0);
		waitForButtonPressed();
	}
	
	/* FAST RUN */
	FastRun();
	
		//Completed Search run, go back and search some more
		turnAroundInPlace();	
		
		floodFill(maze, firstTurn, mouse.x, mouse.y);
	
	/* RETURN */	
	ReturnSearchRun();
		
		//Turn Around
		mouse.rightMotor.stepCount = mouse.leftMotor.stepCount = 0;	
		StopFromSpeedHalf();
		mouse.rightMotor.stepCount = mouse.leftMotor.stepCount = 0;	
		moveBackwards();	
		
		//Save Maze to EEPROM
		saveCurrentMaze();
		writeMemByte(MOUSE_DIRECTION, firstTurn);
		
	stopMouse();
	
	while(!isButtonPushed(1));
		printMaze(maze);
}