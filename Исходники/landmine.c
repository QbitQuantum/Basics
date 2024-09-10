/*
 * Initialize the board for playing
 */
static void
newgame(void)
{
    GR_COORD	row;
    GR_COORD	col;
    GR_COUNT	count;
    CELL		cell;
    POS		pos;

    for (row = 0; row < FULLSIZE; row++) {
        for (col = 0; col < FULLSIZE; col++) {
            cell = F_EMPTY;
            if (badsquare(row) || badsquare(col))
                cell |= F_EDGE;
            board[boardpos(row, col)] = cell;
        }
    }

    playing = GR_TRUE;
    count = 0;
    legs = 2;
    steps = 0;
    drawstatus();
    setcursor();

    while (count < mines) {
        do {
            row = (rand() / 16) % (size * size + 1);
        } while (row == (size * size));

        col = (row % size) + 1;
        row = (row / size) + 1;
        pos = boardpos(row, col);

        if ((pos == boardpos(1,1)) || (pos == boardpos(1,2)) ||
                (pos == boardpos(2,1)) || (pos == boardpos(2,2)) ||
                (pos == boardpos(size,size)))
            continue;

        if (!ismine(board[pos]) && checkpath(pos))
            count++;
    }

    board[boardpos(1,1)] = (F_OLD | '0');

    GrClearWindow(boardwid, GR_TRUE);
}