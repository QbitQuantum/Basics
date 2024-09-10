int main()
{
	sdcard_Init();
	initVGA();
	initAnonProfile();
	brickmap = malloc(sizeof(BrickMap));
	currentLevel->paddle = malloc(sizeof(Paddle));
	currentLevel->buff=malloc(sizeof(Buff));
	int i,j;
	for(i=0;i<maxBalls;i++)
		currentLevel->ball[i] = malloc(sizeof(Ball));

	for(i=0;i<maxRows;i++)
		for(j=0;j<bricksPerRow;j++)
			currentLevel->bricks[i][j]=malloc(sizeof(Brick));


	level=1;


	//pre load the root menu
	getMenu(&currentMenu,rootMenu, 1);

	//allocate memory for level farm


	//set the game to playing
	prevState=currentState=Playing;


	//look up the level from level farm and load it into currentLevel
	levelLookUp(brickmap,level);
	initLevel(*brickmap);
	drawStart(currentLevel);   //this is optional here
	swapBuffers();
	drawStart(currentLevel);

	runCountDown();              //count down from three
	initInterrupt();            //start the game (we dont need to right off the bat (probably shouldnt)

	int counter=0;   //so were not doing direct IO reads on EVERY iteration (we could timer this buttttt no)
	while(1)
	{
		//input to state machine
		counter++;
		if(counter>22000)
		{
			counter=0;
			if(getMenuPB())
			{
				while(getMenuPB() != 0);
				if(currentState == Playing)
					changeState(MenuShow);
			}
		}
		//flicker changes
		if(prevState != currentState)
		{
			if(currentState == Playing)
			{
				clearScreen();
				drawStart(currentLevel);   //this is optional here
				swapBuffers();
				drawStart(currentLevel);
				runCountDown();
				initInterrupt();
			}else
			{
				stopInterrupt();
				getMenu(&currentMenu,rootMenu, 1);
				clearScreen();
				drawStart(currentLevel);   //this is optional here
				swapBuffers();
				drawStart(currentLevel);
				drawMenu(currentMenu);
			}
			prevState = currentState;
		}
		//state machine
		if(currentState == MenuShow)
		{
			menuLoop();
		}else //while were playing we will have to check for other things (all balls gone etc.)
		{
			if(currentLevel->brickCount<=0)
			{
				printf("starting new level \n");
				stopInterrupt();
				level++;
				levelLookUp(brickmap,level);
				initLevel(*brickmap);
				prevState= currentState - 1;
				currentState = Playing;
				printf("finished starting new level \n");
			}
		}
	}
	return 0;
}