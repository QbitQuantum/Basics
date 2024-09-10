/*********************************************************************
** Function: cleanFloor
** Description: Random AI to clean the floor
** Parameters: Floor &floor
** Pre-Conditions: None
** Post-Conditions: None
*********************************************************************/ 
void randomAI::cleanFloor(Floor &floor) {
	srand(time(NULL));

	while (battery > 0) {
		floor.clean();
		int x = rand() % 4 + 1;
		if (x == 1) {
			floor.up();
		}
		else if (x == 2) {
			floor.down();
		}
		else if (x == 3) {
			floor.right();
		}
		else if (x == 4) {
			floor.left();
		}
		update(floor);
	}
}