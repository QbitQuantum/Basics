// Function compares Boards
char boardEquals(board_p a, board_p b)
{
    if (!a || !b)
        return 0;
    if (a == b)
        return 1;

    if (a->width != b->width)
        return 0;
    if (a->height != b->height)
        return 0;

    if (a->state != b->state)
        return 0;

    if (a->round != b->round)
        return 0;
    if (a->score != b->score)
        return 0;

    if (a->progress != b->progress)
        return 0;
    if (a->goal != b->goal)
        return 0;

    return 0 == MemCmp(a->board, b->board,
                       sizeof(a->board));
};