int main() {
	srand(0); //seed generator with 0 for debugging
	dungeon *game = generate_dungeon(10, 20);

	tutorial(game);

	for(;;) {
		set_stage(game);
		get_desc(game);

		switch(input("", I_CHAR)) {
			case 'q': goto END_GAME;
			case 'n': move(game, D_NORTH); break;
			case 's': move(game, D_SOUTH); break;
			case 'e': move(game, D_EAST); break;
			case 'w': move(game, D_WEST); break;
			case 'i': action(game, A_INVENTORY); break;
			case 'd': action(game, A_DROP); break;
			case 'l': action(game, A_LOOT); break;
			case 'p': action(game, A_PUTON); break;
			case 'a': action(game, A_ARM); break;
			case 'c': action(game, A_CONSUME); break;
			case 'f': fight(game); break;
			case 'h': help(); break;
			case 'r': reflect(&(game->player)); break;
			case 'z': dump_dungeon(game); break;
			default: printf("Invalid Command!\n");
		}
	}
	END_GAME:
	return 0;
}