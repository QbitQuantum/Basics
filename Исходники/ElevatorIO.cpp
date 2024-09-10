UINT __stdcall IOToElevator1(void *args)			
{
	CDataPool	dp1("Ele1", sizeof(struct myDpData)) ;
	struct		myDpData *Ele1DP = (struct myDpData *)(dp1.LinkDataPool());

	while(flag) {	
		if (ps1.Read()>0) {
			ps1.Wait();
			m1->Wait();

			Ele1Status = *Ele1DP;
			
			m1->Signal();
			cs1.Signal();
		}

		//FLOOR 9
		m1->Wait();
		MOVE_CURSOR(0,1);
		printf("          |");
		if (Ele1Status.floor == 9) 
			printf("._.");
		else
			printf("   ");
		printf("|   ");
		MOVE_CURSOR(0,2);
		printf("Floor 9   |");
		if (Ele1Status.floor == 9) {
			printf("|");
			if (Ele1Status.door == OPEN) 
				printf("O");
			else
				printf("-");
			printf("|");
		}
		else
			printf("   ");
		printf("|   ");
		MOVE_CURSOR(0,3);
		printf("          |");
		if (Ele1Status.floor == 9) 
			printf("^-^");
		else
			printf("   ");
		printf("|   ");

		//FLOOR 8
		MOVE_CURSOR(0,5);
		printf("          |");
		if (Ele1Status.floor == 8) 
			printf("._.");
		else
			printf("   ");
		printf("|   ");
		MOVE_CURSOR(0,6);
		printf("Floor 8   |");
		if (Ele1Status.floor == 8) {
			printf("|");
			if (Ele1Status.door == OPEN) 
				printf("O");
			else
				printf("-");
			printf("|");
		}
		else
			printf("   ");
		printf("|   ");
		MOVE_CURSOR(0,7);
		printf("          |");
		if (Ele1Status.floor == 8) 
			printf("^-^");
		else
			printf("   ");
		printf("|   ");

		//FLOOR 7
		MOVE_CURSOR(0,9);
		printf("          |");
		if (Ele1Status.floor == 7) 
			printf("._.");
		else
			printf("   ");
		printf("|   ");
		MOVE_CURSOR(0,10);
		printf("Floor 7   |");
		if (Ele1Status.floor == 7) {
			printf("|");
			if (Ele1Status.door == OPEN) 
				printf("O");
			else
				printf("-");
			printf("|");
		}
		else
			printf("   ");
		printf("|   ");
		MOVE_CURSOR(0,11);
		printf("          |");
		if (Ele1Status.floor == 7) 
			printf("^-^");
		else
			printf("   ");
		printf("|   ");

		//FLOOR 6
		MOVE_CURSOR(0,13);
		printf("          |");
		if (Ele1Status.floor == 6) 
			printf("._.");
		else
			printf("   ");
		printf("|   ");
		MOVE_CURSOR(0,14);
		printf("Floor 6   |");
		if (Ele1Status.floor == 6) {
			printf("|");
			if (Ele1Status.door == OPEN) 
				printf("O");
			else
				printf("-");
			printf("|");
		}
		else
			printf("   ");
		printf("|   ");
		MOVE_CURSOR(0,15);
		printf("          |");
		if (Ele1Status.floor == 6) 
			printf("^-^");
		else
			printf("   ");
		printf("|   ");

		//FLOOR 5
		MOVE_CURSOR(0,17);
		printf("          |");
		if (Ele1Status.floor == 5) 
			printf("._.");
		else
			printf("   ");
		printf("|   ");
		MOVE_CURSOR(0,18);
		printf("Floor 5   |");
		if (Ele1Status.floor == 5) {
			printf("|");
			if (Ele1Status.door == OPEN) 
				printf("O");
			else
				printf("-");
			printf("|");
		}
		else
			printf("   ");
		printf("|   ");
		MOVE_CURSOR(0,19);
		printf("          |");
		if (Ele1Status.floor == 5) 
			printf("^-^");
		else
			printf("   ");
		printf("|   ");

		//FLOOR 4
		MOVE_CURSOR(0,21);
		printf("          |");
		if (Ele1Status.floor == 4) 
			printf("._.");
		else
			printf("   ");
		printf("|   ");
		MOVE_CURSOR(0,22);
		printf("Floor 4   |");
		if (Ele1Status.floor == 4) {
			printf("|");
			if (Ele1Status.door == OPEN) 
				printf("O");
			else
				printf("-");
			printf("|");
		}
		else
			printf("   ");
		printf("|   ");
		MOVE_CURSOR(0,23);
		printf("          |");
		if (Ele1Status.floor == 4) 
			printf("^-^");
		else
			printf("   ");
		printf("|   ");

		//FLOOR 3
		MOVE_CURSOR(0,25);
		printf("          |");
		if (Ele1Status.floor == 3) 
			printf("._.");
		else
			printf("   ");
		printf("|   ");
		MOVE_CURSOR(0,26);
		printf("Floor 3   |");
		if (Ele1Status.floor == 3) {
			printf("|");
			if (Ele1Status.door == OPEN) 
				printf("O");
			else
				printf("-");
			printf("|");
		}
		else
			printf("   ");
		printf("|   ");
		MOVE_CURSOR(0,27);
		printf("          |");
		if (Ele1Status.floor == 3) 
			printf("^-^");
		else
			printf("   ");
		printf("|   ");

		//FLOOR 2
		MOVE_CURSOR(0,29);
		printf("          |");
		if (Ele1Status.floor == 2) 
			printf("._.");
		else
			printf("   ");
		printf("|   ");
		MOVE_CURSOR(0,30);
		printf("Floor 2   |");
		if (Ele1Status.floor == 2) {
			printf("|");
			if (Ele1Status.door == OPEN) 
				printf("O");
			else
				printf("-");
			printf("|");
		}
		else
			printf("   ");
		printf("|   ");
		MOVE_CURSOR(0,31);
		printf("          |");
		if (Ele1Status.floor == 2) 
			printf("^-^");
		else
			printf("   ");
		printf("|   ");

		//FLOOR 1
		MOVE_CURSOR(0,33);
		printf("          |");
		if (Ele1Status.floor == 1) 
			printf("._.");
		else
			printf("   ");
		printf("|   ");

		MOVE_CURSOR(0,34);
		printf("Floor 1   |");
		if (Ele1Status.floor == 1) {
			printf("|");
			if (Ele1Status.door == OPEN) 
				printf("O");
			else
				printf("-");
			printf("|");
		}
		else
			printf("   ");
		printf("|   ");

		MOVE_CURSOR(0,35);
		printf("          |");
		if (Ele1Status.floor == 1) 
			printf("^-^");
		else
			printf("   ");
		printf("|   ");

		//FLOOR 0
		MOVE_CURSOR(0,37);
		printf("          |");
		if (Ele1Status.floor == 0) 
			printf("._.");
		else
			printf("   ");
		printf("|   ");
		MOVE_CURSOR(0,38);
		printf("Floor 0   |");
		if (Ele1Status.floor == 0) {
			printf("|");
			if (Ele1Status.door == OPEN) 
				printf("O");
			else
				printf("-");
			printf("|");
		}
		else
			printf("   ");
		printf("|   ");
		MOVE_CURSOR(0,39);
		printf("          |");
		if (Ele1Status.floor == 0) 
			printf("^-^");
		else
			printf("   ");
		printf("|   ");


		MOVE_CURSOR(0,41);
		printf("Buttons in Ele1");
		MOVE_CURSOR(7,42);
		for (int i = 7; i < 10; i++) {
			if (Ele1Status.lights[i] == 1) {
				TEXT_COLOUR(14);
			}
			printf("[%d] ", i);
			TEXT_COLOUR(7);
		}
		MOVE_CURSOR(7,43);
		for (int i = 4; i < 7; i++) {
			if (Ele1Status.lights[i] == 1) {
				TEXT_COLOUR(14);
			}
			printf("[%d] ", i);
			TEXT_COLOUR(7);
		}
		MOVE_CURSOR(7,44);
		for (int i = 1; i < 4; i++) {
			if (Ele1Status.lights[i] == 1) {
				TEXT_COLOUR(14);
			}
			printf("[%d] ", i);
			TEXT_COLOUR(7);
		}
		MOVE_CURSOR(11,45);
		if (Ele1Status.lights[0] == 1) {
			TEXT_COLOUR(14);
		}
		printf("[0]");
		TEXT_COLOUR(7);
		//printf("Ele1 Read value for Floor = %d                                \n", Ele1Status.floor) ;
		//printf("Ele1 Read value for Usage = %d                                \n", Ele1Status.usage);
		//printf("Ele1 Read value for Door = %d                                 \n", Ele1Status.direction) ; 
		//printf("Ele1 Read value for Direction = %d                            \n", Ele1Status.direction) ; 
		//printf("Ele1 Read values for floor array = ") ;
		//for(int i=0; i < 10; i ++) {
		//	printf("%d ", Ele1Status.floors[i]) ;
		//}
		fflush(stdout);
		MOVE_CURSOR(0,50);
		fflush(stdout);
		m1->Signal();

		SLEEP(10);
	}
	return 0 ;									
}