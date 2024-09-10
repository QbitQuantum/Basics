void draw_grid_line_matlab(FILE * ff, const grid_line * line, const d_grid * grd, const char * color, short thick) 
{
#ifndef DEBUG
	return;
#endif

	if (line == NULL)
		return;
	if (grd == NULL)
		return;

	size_t fl_size = line->size();
	size_t i;
	size_t J1, J2;
	size_t pos_i, pos_j;
	size_t NN = grd->getCountX();
	size_t MM = grd->getCountY();
	for (i = 0; i < fl_size; i++) {
		J1 = line->get_first_cell(i);
		J2 = line->get_second_cell(i);
		
		one2two(J1, pos_i, pos_j, NN+2, MM+2);
		pos_i--;
		pos_j--;
		
		REAL x, y;
		
		REAL stepX2 = grd->stepX/REAL(2);
		REAL stepY2 = grd->stepY/REAL(2);
		grd->getCoordNode(pos_i,pos_j,x,y);
		
		int diff = (J2-J1);
		
		// right line
		if (diff == 1) {
			fprintf(ff,"plot([%lf  %lf],[%lf %lf],'color','%s','LineWidth',%d);\n", 
				x+stepX2, x+stepX2, y-stepY2, y+stepY2, color, thick);
		}
		
		// left line
		if (diff == -1) {
			fprintf(ff,"plot([%lf  %lf],[%lf %lf],'color','%s','LineWidth',%d);\n", 
				x-stepX2, x-stepX2, y-stepY2, y+stepY2, color, thick);
		}
		
		// up line 
		if (diff == NN+2) {
			fprintf(ff,"plot([%lf  %lf],[%lf %lf],'color','%s','LineWidth',%d);\n", 
				x-stepX2, x+stepX2, y+stepY2, y+stepY2, color, thick);
		}
		
		// down line
		if (-diff == NN+2) { // diff == -NN-2
			fprintf(ff,"plot([%lf  %lf],[%lf %lf],'color','%s','LineWidth',%d);\n", 
				x-stepX2, x+stepX2, y-stepY2, y-stepY2, color, thick);
		}
		
	}
	
	fflush(ff);
};