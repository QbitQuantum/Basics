void TCOD_map_compute_fov_restrictive_shadowcasting_quadrant (map_t *m, int player_x, int player_y, int max_radius, bool light_walls, int maxObstacles, int dx, int dy) {
    static double *startAngle=NULL, *endAngle=NULL;
    static int angleArraySize=0;

    if ( angleArraySize > 0 && angleArraySize < maxObstacles ) {
        free(startAngle);
        startAngle=NULL;
    }
    if ( startAngle == NULL ) {
        angleArraySize = maxObstacles;
        startAngle = (double *)malloc(sizeof(double) * 2 * maxObstacles);
        endAngle = &startAngle[maxObstacles];
    }
    //octant: vertical edge
    {
        int iteration = 1; //iteration of the algo for this octant
        bool done = false;
        int totalObstacles = 0;
        int obstaclesInLastLine = 0;
		double minAngle = 0.0f;
		int x,y;

        //do while there are unblocked slopes left and the algo is within the map's boundaries
        //scan progressive lines/columns from the PC outwards
        y = player_y+dy; //the outer slope's coordinates (first processed line)
        if (y < 0 || y >= m->height) done = true;
		while(!done) {
            //process cells in the line
			double slopesPerCell = 1.0f/(double)(iteration+1);
			double halfSlopes = slopesPerCell*0.5f;
			int processedCell = (int)(minAngle / slopesPerCell);
            int minx = MAX(0,player_x-iteration), maxx = MIN(m->width-1,player_x+iteration);
            done = true;
            for (x = player_x + (processedCell * dx); x >= minx && x <= maxx; x+=dx) {
                int c = x + (y * m->width);
                //calculate slopes per cell
                bool visible = true;
                double startSlope = (double)processedCell*slopesPerCell;
                double centreSlope = startSlope+halfSlopes;
                double endSlope = startSlope+slopesPerCell;
                if (obstaclesInLastLine > 0 && m->cells[c].fov == 0) {
                    int idx = 0;
                    while(visible && idx < obstaclesInLastLine) {
                        if (m->cells[c].transparent == true) {
                            if (centreSlope > startAngle[idx] && centreSlope < endAngle[idx])
                                visible = false;
                            }
                        else {
                            if (startSlope >= startAngle[idx] && endSlope <= endAngle[idx])
                                visible = false;
                        }
                        if (visible && (m->cells[c-(m->width*dy)].fov == 0 || !m->cells[c-(m->width*dy)].transparent) && (x-dx >= 0 && x-dx < m->width && (m->cells[c-(m->width*dy)-dx].fov == 0 || !m->cells[c-(m->width*dy)-dx].transparent))) visible = false;
                        idx++;
                    }
                }
                if (visible) {
                    m->cells[c].fov = 1;
                    done = false;
                    //if the cell is opaque, block the adjacent slopes
                    if (!m->cells[c].transparent) {
                        if (minAngle >= startSlope) minAngle = endSlope;
                        else {
                        	startAngle[totalObstacles] = startSlope;
                        	endAngle[totalObstacles++] = endSlope;
                        }
                        if (!light_walls) m->cells[c].fov = 0;
                    }
                }
                processedCell++;
            }
            if (iteration == max_radius) done = true;
            iteration++;
            obstaclesInLastLine = totalObstacles;
            y += dy;
            if (y < 0 || y >= m->height) done = true;
			if ( minAngle == 1.0f ) done=true;
        }
    }
    //octant: horizontal edge
    {
        int iteration = 1; //iteration of the algo for this octant
        bool done = false;
        int totalObstacles = 0;
        int obstaclesInLastLine = 0;
		double minAngle = 0.0f;
		int x,y;

        //do while there are unblocked slopes left and the algo is within the map's boundaries
        //scan progressive lines/columns from the PC outwards
        x = player_x+dx; //the outer slope's coordinates (first processed line)
        if (x < 0 || x >= m->width) done = true;
		while(!done) {
            //process cells in the line
			double slopesPerCell = 1.0f/(double)(iteration+1);
			double halfSlopes = slopesPerCell*0.5f;
			int processedCell = (int)(minAngle / slopesPerCell);
            int miny = MAX(0,player_y-iteration), maxy = MIN(m->height-1,player_y+iteration);
            done = true;
            for (y = player_y + (processedCell * dy); y >= miny && y <= maxy; y+=dy) {
                int c = x + (y * m->width);
                //calculate slopes per cell
                bool visible = true;
                double startSlope = (double)processedCell*slopesPerCell;
                double centreSlope = startSlope+halfSlopes;
                double endSlope = startSlope+slopesPerCell;
                if (obstaclesInLastLine > 0 && m->cells[c].fov == 0) {
                    int idx = 0;
                    while(visible && idx < obstaclesInLastLine) {
                        if (m->cells[c].transparent == true) {
                            if (centreSlope > startAngle[idx] && centreSlope < endAngle[idx])
                                visible = false;
                            }
                        else {
                            if (startSlope >= startAngle[idx] && endSlope <= endAngle[idx])
                                visible = false;
                        }
                        if (visible && (m->cells[c-dx].fov == 0 || !m->cells[c-dx].transparent) && (y-dy >= 0 && y-dy < m->height && (m->cells[c-(m->width*dy)-dx].fov == 0 || !m->cells[c-(m->width*dy)-dx].transparent))) visible = false;
                        idx++;
                    }
                }
                if (visible) {
                    m->cells[c].fov = 1;
                    done = false;
                    //if the cell is opaque, block the adjacent slopes
                    if (!m->cells[c].transparent) {
                        if (minAngle >= startSlope) minAngle = endSlope;
                        else {
                        	startAngle[totalObstacles] = startSlope;
                        	endAngle[totalObstacles++] = endSlope;
                        }
                        if (!light_walls) m->cells[c].fov = 0;
                    }
                }
                processedCell++;
            }
            if (iteration == max_radius) done = true;
            iteration++;
            obstaclesInLastLine = totalObstacles;
            x += dx;
            if (x < 0 || x >= m->width) done = true;
			if ( minAngle == 1.0f ) done=true;
        }
    }
}