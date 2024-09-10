void handleDiceInput() 
{
	int input = -1;
	do {
		_flushall();
		scanf(" %d", &input);
		if (validateNumber(&input) == 0) {
			if (validateUINTMAX(input) == 1 && validateMin(input) == 1) {
				castDice(input);
				setState(GS_MAINMENU);
#undef FLAGG
				manage(); //Go back to main menu.
			} else {
				printf("\nValue not in range!\n");
				drawDiceMenu();
				handleDiceInput();
			}
		} else {
			printf("\nInput value shall be a number!\n");
			drawDiceMenu();
			handleDiceInput();
		}
	} while (1);
}