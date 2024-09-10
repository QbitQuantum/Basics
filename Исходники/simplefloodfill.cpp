/*****************************************************************************
* Function: FindNextPathSegment
*
* Description:	Compute the fastest route throught the maze. Simulate maze
*				solutions and ouput the next heading and the number of cells
*				to travel forward to get to that turn.
*****************************************************************************/
void SimpleFloodFill::FindNextPathSegment
	(
		uint32_t		robot_current_row,      // the current row of the robot
		uint32_t		robot_current_col,      // the current col of the robot
		heading_t		robot_current_heading,  // the current heading of the robot
		heading_t*		next_heading,           // out param of the next heading to travel
		uint32_t*		cells_to_travel         // out param of the number of cells to travel in the given direction
	)
{
    Cell* current_cell          = m->get_cell(robot_current_row, robot_current_col);
    uint32_t depth		        = FloodFill();
    uint32_t current_cell_depth = *((int32_t*)current_cell->get_data());
    *cells_to_travel            = 0;

    if (depth == MAX_FLOOD_DEPTH) return;
    
    
    
    Cell* adjacent_cell = current_cell->get_adjacent_cell(robot_current_heading);
    
    //Decide how many cells to travel forward (0->N cells) 
    while(adjacent_cell != _NULL &&                                             //Make sure no wall is in front of us
          *((int32_t*)adjacent_cell->get_data()) == current_cell_depth - 1 &&   //Check to see if the cell in front of us is the next best decision
          ( adjacent_cell->get_visited() || *cells_to_travel == 0 ) )           //If we are traveling more than one cell verify that we have visited it before
    {
        *cells_to_travel += 1;
        current_cell_depth--;
        current_cell = adjacent_cell;
        adjacent_cell = adjacent_cell->get_adjacent_cell(robot_current_heading);
    }
    
    //decide which direction to turn after moving forward
    for (heading_t h = north; h < num_cardinal_directions; h++)
    {
        if(h == robot_current_heading  || (h == GetReverseHeading(robot_current_heading) && cells_to_travel > 0)) continue;
        
        Cell* adjacent_cell = current_cell->get_adjacent_cell(h);

        if (adjacent_cell != _NULL && *((int32_t*)adjacent_cell->get_data()) == current_cell_depth - 1)
        {
            *next_heading = h;
            return;
        }   
        

    }

} // FindNextPathSegment()