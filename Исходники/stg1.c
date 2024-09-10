void stg1(){
	while(1){
		BACK_TO_FLAG = 0;
		clear_screen();
		setcursor(8,5,1);
		printg("SNAKE: ADIN EDITION MENU\n\r\0",0,_C_YELLOW);
		set_border();
		draw_game_line(23,25,133,25,_C_YELLOW,1);
		setcursor(8,8,1);
		printg("1.- Start Game",0,_C_YELLOW);
		setcursor(8,9,1);
		printg("2.- Select Difficult",0,_C_YELLOW);
		setcursor(8,10,1);
		printg("3.- Back to screen",0,_C_YELLOW);
		write_diff();
		write_highscore();
		select_menu();
		if(BACK_TO_FLAG == 1) break;
	}
}