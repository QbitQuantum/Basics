int parse_map(FILE *rules, Ship *ships, Grid *board, 
        unsigned int *numShips)
{
    char line[BUFF_LEN];	/* Line buffers */
    int i;
    int maths;				/* Temporary integer for performing math */

    /* All lines should be a two positive integers followed by a char */
    /* Also, we expect there to be the same number of ships described
     * here as defined by the second line of the rules file and saved
     * to numShips */ 
    /* After parsing for errors, we then check for overlap and out of bounds
     * on a line by line basis */
    /* Note: We can assume only one error possible per line */
    for(i = 0; i < *numShips; i++) {
        /* Check if we reached EOF prematurely */
        if(fgets(line, BUFF_LEN, rules) == NULL) {
            return map_invalid();
        }
        /* Check the length of the line */
        if(!check_length(line)) {
            return map_invalid();
        }
        if(sscanf(line, "%u %u %c", &ships[i].xPos, &ships[i].yPos, 
                    &ships[i].direction) != 3) {
            return map_invalid();
        }

        /* ship.direction must be 'N', 'S', 'E', or 'W' */
        if(ships[i].direction != 'N' && ships[i].direction != 'S' && 
                ships[i].direction != 'E' && ships[i].direction != 'W') {
            return map_invalid();
        }

        /* Out of Bounds check */
        /* First check anchor point */
        if(ships[i].xPos > board->width ||
                ships[i].xPos > board->height) {
            return map_oob(); 
        }
        /* Next, check no section of ship is out of bounds */
        switch(ships[i].direction) {
            case 'N':
                maths = ships[i].yPos - (ships[i].length - 1);
                if(maths < 0) {
                    return map_oob();
                }
                break;
            case 'S':
                maths = ships[i].yPos + (ships[i].length - 1);
                if(maths >=	board->height) {
                    return map_oob();
                }
                break;
            case 'E':
                maths = ships[i].xPos + (ships[i].length - 1);
                if(maths >=	board->width) {
                    return map_oob();
                }
                break;
            case 'W':
                maths = ships[i].xPos - (ships[i].length - 1);
                if(maths < 0) {
                    return map_oob();
                }
                break;
            default:
                return map_invalid();
        }

    }
    return 0;
}