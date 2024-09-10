//readfromfile modifies the given board to make it like board stored in file, and returns a char indicating the player to play
char readfromfile(board *b, char *filename) {
	int i, j;
	FILE *fp = fopen(filename, "r+");
	if (fp == NULL)
		return -1;
	char player;
	fwscanf(fp, L"%d", &player);
	for(i = c_8; i <= c_1; i++)
		for(j = c_a; j <= c_h; j++) 
			fwscanf(fp, L"%lc%d",&b->sq[i][j].piece, &b->sq[i][j].info);
	fclose(fp);
	return player;
}