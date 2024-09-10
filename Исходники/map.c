/**
 * Print the map in a BMP file
 */
int printMap(s_map* map, float min, float max, char* filename, int filename_len, short generateText)
{
	//set up some variables
	float diff = max - min,
		  flood = 0.5f,//flood level
		  mount = 0.85f;//mountain level

	flood *= diff;
	mount *= diff;

	int i,j,k;
	char bmpfile[filename_len + 4], txtfile[filename_len + 4];
	strcpy(bmpfile, filename);
	strcat(bmpfile, ".bmp");
	strcpy(txtfile, filename);
	strcat(txtfile, ".txt");

	//these can be changed for interesting results
	s_color waterlow, waterhigh, landlow, landhigh, mountlow, mounthigh;

	waterlow = color(0, 0, 55);
	waterhigh = color(0, 53, 106);
	landlow = color(0, 64, 0);
	landhigh = color(133, 182, 116);
	mountlow = color(167, 157, 147);
	mounthigh = color(216, 223, 226);

	//3.0 output to file
	//3.1 Begin the file
	//3.1.1 open output file
	FILE *bmp, *txt;
	bmp = fopen(bmpfile, "wb");

	if (generateText)
		txt = fopen(txtfile, "w");
	if (bmp == NULL || (generateText && txt == NULL)){
		printf("Target file opening error");
		return 1;
	}

	//3.1.2 copy the header
	//3.1.2.1 magic number
	fputc((char)66, bmp);
	fputc((char)77, bmp);

	//~//3.1.2.2 filsize/unused space
	for (i = 0; i < 8; i++) {
		fputc((char)0, bmp);
	}

	//~//3.1.2.3 data offset
	fputc((char)54, bmp);

	//~//3.1.2.4 unused space
	for (i = 0; i < 3; i++) {
		fputc((char)0, bmp);
	}

	//~//3.1.2.5 header size
	fputc((char)40, bmp);

	//~//3.1.2.6 unused space
	for (i = 0; i < 3; i++) {
		fputc((char)0, bmp);
	}

	//~//3.1.2.7 file width (trickier)
	fputc((char)((*map).width % 256), bmp);
	fputc((char)(((*map).width>>8)%256), bmp);
	fputc((char)(((*map).width>>16)%256), bmp);
	fputc((char)(((*map).width>>24)%256), bmp);

	//~//3.1.2.8 file height (trickier)
	fputc((char)((*map).height%256), bmp);
	fputc((char)(((*map).height>>8)%256), bmp);
	fputc((char)(((*map).height>>16)%256), bmp);
	fputc((char)(((*map).height>>24)%256), bmp);

	//~//3.1.2.9 color planes
	fputc((char)1, bmp);
	fputc((char)0, bmp);

	//~//3.1.2.10 bit depth
	fputc((char)24, bmp);

	//~//3.1.2.11 the rest
	for (i = 0; i < 25; i++) {
		fputc((char)0, bmp);
	}

	//3.2 put in the elements of the array
	s_color newcolor = color(0, 0, 0);
	s_cell* current;
	for (j = map->height - 1; j >= 0; j--) {//bitmaps start with the bottom row, and work their way up...
		for (i = 0; i < map->width; i++) {//...but still go left to right
			int directions, currentIndex;

			currentIndex = i + j * map->width;
			current = &(map->grid[currentIndex]);
			current->altitude -= min;
			//if this point is below the floodline...
			if (current->altitude < flood) {
				current->ground_type = GROUND_WATER;
				newcolor = lerp(waterlow, waterhigh, current->altitude / flood);
			}
			//if this is above the mountain line...
			else if (current->altitude > mount) {
				current->ground_type = GROUND_MOUNTAIN;
				newcolor = lerp(mountlow, mounthigh, (current->altitude - mount) / (diff - mount));
			}
			//if this is regular land
			else {
				current->ground_type = GROUND_LAND;
				newcolor = lerp(landlow, landhigh, (current->altitude - flood) / (mount - flood));
			}

			fputc((char)(newcolor.v[2]), bmp);//blue
			fputc((char)(newcolor.v[1]), bmp);//green
			fputc((char)(newcolor.v[0]), bmp);//red

			if (!generateText)
				continue;

			directions = 0;
			// WEST
			if (i > 0 && map->grid[currentIndex - 1].altitude >= flood) {
				directions |= BIT_CELL_WEST;
			}
			// EAST
			if (i < map->width - 1 && map->grid[currentIndex + 1].altitude - min >= flood) {
				directions |= BIT_CELL_EAST;
			}
			// NORTH
			if (j > 0 && map->grid[currentIndex - map->width].altitude - min >= flood) {
				directions |= BIT_CELL_NORTH;
			}
			// SOUTH
			if (j < map->height - 1 && map->grid[currentIndex + map->width].altitude >= flood) {
				directions |= BIT_CELL_SOUTH;
			}
			fprintf(txt, "%d %d %d %d\n", (*current).ground_type, i, j, directions);
		}
		//round off the row
		for (k = 0; k < ((*map).width % 4); k++) {
			fputc((char)0, bmp);
		}
	}

	//3.3 end the file
	fclose(bmp);

	if (generateText)
		fclose(txt);

	return 0;
}