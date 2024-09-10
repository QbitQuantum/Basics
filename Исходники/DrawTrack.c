void	DrawTrack(FILE *fp, TRACK *t, char *Label, int PointsPerPixel, int OriginX, int OriginY, INFO I, int DrawEvents, int frame, FILEINFO FileInfo)
{
	RGBCOLOR	rgb[N_COLORS];

	int			i,j, FirstGoodPosition = 1, NewEvent;
	float		x, y;
	float		CenterX, CenterY, ArenaRadiusPix;
	float		MinShockAng, MaxShockAng, MinShockRad, MaxShockRad;
	double		asin(), acos(), atan2();
	double 		Y, X, ang, rad;
	unsigned char	**ReinforcedMap;

	SetRGBColors(rgb);
	
	// ArenaRadiusPix = (float)(I.Arena.Radius * I.PixelsPerCM);
	ArenaRadiusPix = (float)DEFAULT_ARENA_RADIUS;	// iTrack sets the radius to be 127

	(void) fprintf(fp, "gsave\n");

	// Set coordinate system to arena center
	CenterX = (float)(I.Arena.CenterX * PointsPerPixel + OriginX);
	CenterY = (float)(OriginY - I.Arena.CenterY * PointsPerPixel - 20);
	(void) fprintf(fp, "%0.2f %0.2f translate\n", CenterX, CenterY);

	// label the picture
	(void) fprintf(fp, "/Times-Roman findfont\n");
	(void) fprintf(fp, "0.5 cm scalefont\n");
	(void) fprintf(fp, "setfont\n");

	(void) fprintf(fp, "%0.2f pix %0.2f pix mt\n", (0.0 - ArenaRadiusPix), (ArenaRadiusPix + 10.0));
	// (void) fprintf(fp, "%0.2f pix %0.2f pix mt\n", (0.0 - ArenaRadiusPix - ROOM_FRAME_INCREASE), (ArenaRadiusPix + 10.0));
	(void) fprintf(fp, "( Paradigm: %s ) show\n", I.Paradigm);

	(void) fprintf(fp, "%d pix %d pix mt\n", 0 - strlen(Label) / 2, 0 - (int)(ArenaRadiusPix + 20));
	(void) fprintf(fp, "( %s ) center show\nnewpath\n", Label);

	// draw the arena in a thin line
	(void) fprintf(fp, "%0.2f %0.2f %0.2f setrgbcolor\n1.0 setlinewidth\n", rgb[BLACK].r, rgb[BLACK].g, rgb[BLACK].b);

	switch(I.Arena.Type){
		case ARENA_TYPE_CIRCLE:
			/* draw a circle for the arena */
			(void) fprintf(fp, "%0.2f pix %0.2f pix %0.2f pix 0 360 arc\n", 0.0, 0.0, ArenaRadiusPix);
			(void) fprintf(fp, "closepath\nstroke\n");

		break;

		default:
		break;
	}

	for(i = 0; i < I.NumberOfCoordFrames; i++){
		// draw the Coordinate frame in a thick line
		(void) fprintf(fp, "%0.2f %0.2f %0.2f setrgbcolor\n3.0 setlinewidth\n", rgb[BLACK].r, rgb[BLACK].g, rgb[BLACK].b);
		switch(I.Target[i].CoordFrame){
			case ROOM_FRAME:
				/* draw a square for the room */
				(void) fprintf(fp, "%0.2f pix %0.2f pix mt\n", 0.0 - (ArenaRadiusPix + ROOM_FRAME_INCREASE) , 0.0 - (ArenaRadiusPix + ROOM_FRAME_INCREASE));
				(void) fprintf(fp, "%0.2f pix %0.2f pix lt\n", (ArenaRadiusPix + ROOM_FRAME_INCREASE), 0.0 - (ArenaRadiusPix + ROOM_FRAME_INCREASE));
				(void) fprintf(fp, "%0.2f pix %0.2f pix lt\n", (ArenaRadiusPix + ROOM_FRAME_INCREASE) , (ArenaRadiusPix + ROOM_FRAME_INCREASE));
				(void) fprintf(fp, "%0.2f pix %0.2f pix lt\n", 0.0 - (ArenaRadiusPix + ROOM_FRAME_INCREASE) , (ArenaRadiusPix + ROOM_FRAME_INCREASE));
				(void) fprintf(fp, "closepath\nstroke\n");	
			break;

			case ARENA_FRAME:
				switch(I.Arena.Type){
					case ARENA_TYPE_CIRCLE:
						/* draw a circle for the arena */	
						(void) fprintf(fp, "%0.2f pix %0.2f pix %0.2f pix 0 360 arc\n", 0.0, 0.0, ArenaRadiusPix);
						(void) fprintf(fp, "closepath\nstroke\n");
					break;
					
					default:
					break;
				}
			break;

			case ROOM_AND_ARENA_FRAME:
				/* draw a square for the room */
				(void) fprintf(fp, "%0.2f pix %0.2f pix mt\n", 0.0 - (ArenaRadiusPix + ROOM_FRAME_INCREASE) , 0.0 - (ArenaRadiusPix + ROOM_FRAME_INCREASE));
				(void) fprintf(fp, "%0.2f pix %0.2f pix lt\n", (ArenaRadiusPix + ROOM_FRAME_INCREASE), 0.0 - (ArenaRadiusPix + ROOM_FRAME_INCREASE));
				(void) fprintf(fp, "%0.2f pix %0.2f pix lt\n", (ArenaRadiusPix + ROOM_FRAME_INCREASE) , (ArenaRadiusPix + ROOM_FRAME_INCREASE));
				(void) fprintf(fp, "%0.2f pix %0.2f pix lt\n", 0.0 - (ArenaRadiusPix + ROOM_FRAME_INCREASE) , (ArenaRadiusPix + ROOM_FRAME_INCREASE));
				(void) fprintf(fp, "closepath\nstroke\n");
			
				switch(I.Arena.Type){
					case ARENA_TYPE_CIRCLE:
						/* draw a circle for the arena */	
						(void) fprintf(fp, "%0.2f pix %0.2f pix %0.2f pix 0 360 arc\n", 0.0, 0.0, ArenaRadiusPix);
						(void) fprintf(fp, "closepath\nstroke\n");
					break;

					default:
					break;
				}
			
			break;

			default:
			break;
		}
		
		/* draw the reinforced area */
		if(I.Target[i].Show && (i == frame)){

			switch(I.Target[i].Type){
				case REINFORCED_CIRCLE:
					(void) fprintf(fp, "%0.2f %0.2f %0.2f setrgbcolor\n1.0 setlinewidth\n", rgb[RED].r, rgb[RED].g, rgb[RED].b);
				
					// draw the same regardless of the defining frame
					// original target
					X = I.Target[i].Circle.X - I.Arena.CenterX, 
					Y = I.Arena.CenterY - I.Target[i].Circle.Y;
					(void) fprintf(fp, "%0.2f pix %0.2f pix %0.2f pix 0 360 arc\n", X, Y, I.Target[i].Circle.Rad);
					(void) fprintf(fp, "closepath\nstroke\n");
					rad = hypot(Y, X);
					ang = atan2(Y, X);

					// draw corresponding targets in the other quadrants
					(void) fprintf(fp, "%0.2f %0.2f %0.2f setrgbcolor\n1.0 setlinewidth\n", rgb[BLACK].r, rgb[BLACK].g, rgb[BLACK].b);
					
					for(j = 1; j < 4; j++){
						X = cos(ang + j * (M_PI / 2.0)) * rad; 
						Y = sin(ang + j * (M_PI / 2.0)) * rad; 
						(void) fprintf(fp, "%0.2f pix %0.2f pix %0.2f pix 0 360 arc\n", X, Y, I.Target[i].Circle.Rad);
						(void) fprintf(fp, "closepath\nstroke\n");
					}
				break;

				case REINFORCED_SECTOR:
					(void) fprintf(fp, "%0.2f %0.2f %0.2f setrgbcolor\n3.0 setlinewidth\n", rgb[RED].r, rgb[RED].g, rgb[RED].b);
				
					MinShockAng = (float)(I.Target[i].Sector.Ang - (I.Target[i].Sector.Width / (float)2.0)) / (float)DEG_PER_RAD;
					MaxShockAng = (float)(I.Target[i].Sector.Ang + (I.Target[i].Sector.Width / (float)2.0)) / (float)DEG_PER_RAD;
					MinShockRad = (float)(I.Target[i].Sector.InRad);
					MaxShockRad = (float)(I.Target[i].Sector.OutRad);

					// draw according to the defining frame
					if((I.Target[i].CoordFrame == ROOM_FRAME) || (I.Target[i].CoordFrame == ROOM_AND_ARENA_FRAME)){
						double RoomRadius, WallRadius;

						RoomRadius = ArenaRadiusPix + ROOM_FRAME_INCREASE;
						// max ang: line in to out
						x = (float)(cos(MaxShockAng) * MinShockRad);
						y = (float)(sin(MaxShockAng) * MinShockRad);
						(void) fprintf(fp, "%0.2f pix %0.2f pix mt\n", x,y);

						if(((MaxShockAng > (45.0 / DEG_PER_RAD)) && (MaxShockAng < (135.0 / DEG_PER_RAD))) ||
							((MaxShockAng > (225.0 / DEG_PER_RAD)) && (MaxShockAng < (315.0 / DEG_PER_RAD))))
							WallRadius = sqrt((double)(RoomRadius * RoomRadius) / (1.0 - cos(MaxShockAng) * cos(MaxShockAng)));
						else
							WallRadius = sqrt((double)(RoomRadius * RoomRadius) / (1.0 - sin(MaxShockAng) * sin(MaxShockAng)));
					
						x = (float)(cos(MaxShockAng) * WallRadius);
						y = (float)(sin(MaxShockAng) * WallRadius);
						(void) fprintf(fp, "%0.2f pix %0.2f pix lt\n", x,y);
				
						// max ang outer to min ang outer
						if(((MinShockAng > (45.0 / DEG_PER_RAD)) && (MinShockAng < (135.0 / DEG_PER_RAD))) ||
							((MinShockAng > (225.0 / DEG_PER_RAD)) && (MinShockAng < (315.0 / DEG_PER_RAD))))
							WallRadius = sqrt((double)(RoomRadius * RoomRadius) / (1.0 - cos(MinShockAng) * cos(MinShockAng)));
						else
							WallRadius = sqrt((double)(RoomRadius * RoomRadius) / (1.0 - sin(MinShockAng) * sin(MinShockAng)));

						x = (float)(cos(MinShockAng) * WallRadius);
						y = (float)(sin(MinShockAng) * WallRadius);
						(void) fprintf(fp, "%0.2f pix %0.2f pix mt\n", x,y);

						// min ang: outer to inner
						x = (float)(cos(MinShockAng) * MinShockRad);
						y = (float)(sin(MinShockAng) * MinShockRad);
						(void) fprintf(fp, "%0.2f pix %0.2f pix lt\n", x,y);
		
						// inner arc
						x = (float)(cos(MinShockAng) * MinShockRad);
						y = (float)(sin(MinShockAng) * MinShockRad);
						(void) fprintf(fp, "%0.2f pix %0.2f pix mt\n", x,y);
						x = 0.0;
						y = 0.0;
						(void) fprintf(fp, "%0.2f pix %0.2f pix %0.2f pix %0.2f %0.2f arc\n", x, y, MinShockRad, MinShockAng * DEG_PER_RAD, MaxShockAng * DEG_PER_RAD);
						x = (float)(cos(MaxShockAng) * MinShockRad);
						y = (float)(sin(MaxShockAng) * MinShockRad);
						(void) fprintf(fp, "%0.2f pix %0.2f pix mt\n", x,y);

						(void) fprintf(fp, "closepath\nstroke\n");
					}
					if((I.Target[i].CoordFrame == ARENA_FRAME) || (I.Target[i].CoordFrame == ROOM_AND_ARENA_FRAME)){

						// max ang: line in to out
						x = (float)(cos(MaxShockAng) * MinShockRad);
						y = (float)(sin(MaxShockAng) * MinShockRad);
						(void) fprintf(fp, "%0.2f pix %0.2f pix mt\n", x,y);
						x = (float)(cos(MaxShockAng) * MaxShockRad);
						y = (float)(sin(MaxShockAng) * MaxShockRad);
						(void) fprintf(fp, "%0.2f pix %0.2f pix lt\n", x,y);

						// outer arc
						x = (float)(cos(MinShockAng) * MaxShockRad);
						y = (float)(sin(MinShockAng) * MaxShockRad);
						(void) fprintf(fp, "%0.2f pix %0.2f pix mt\n", x,y);
						x = 0.0;
						y = 0.0;
						(void) fprintf(fp, "%0.2f pix %0.2f pix %0.2f pix %0.2f %0.2f arc\n", x, y, MaxShockRad, MinShockAng * DEG_PER_RAD, MaxShockAng * DEG_PER_RAD);
						
						// min ang: line out to in
						x = (float)(cos(MinShockAng) * MaxShockRad);
						y = (float)(sin(MinShockAng) * MaxShockRad);
						(void) fprintf(fp, "%0.2f pix %0.2f pix mt\n", x,y);
						x = (float)(cos(MinShockAng) * MinShockRad);
						y = (float)(sin(MinShockAng) * MinShockRad);
						(void) fprintf(fp, "%0.2f pix %0.2f pix lt\n", x,y);

						// inner arc
						x = (float)(cos(MinShockAng) * MinShockRad);
						y = (float)(sin(MinShockAng) * MinShockRad);
						(void) fprintf(fp, "%0.2f pix %0.2f pix mt\n", x,y);
						x = 0.0;
						y = 0.0;
						(void) fprintf(fp, "%0.2f pix %0.2f pix %0.2f pix %0.2f %0.2f arc\n", x, y, MinShockRad, MinShockAng * DEG_PER_RAD, MaxShockAng * DEG_PER_RAD);
						x = (float)(cos(MaxShockAng) * MinShockRad);
						y = (float)(sin(MaxShockAng) * MinShockRad);
						(void) fprintf(fp, "%0.2f pix %0.2f pix mt\n", x,y);

						(void) fprintf(fp, "closepath\nstroke\n");
					}
				break;

				default:
				break;

			}	
		}
	}

	//  draw quadrant lines
	if(I.ParadigmType == OPEN_FIELD || I.ParadigmType == TRACKER){
		double RoomRadius, QuadAng;

		RoomRadius = ArenaRadiusPix + ROOM_FRAME_INCREASE;

		(void) fprintf(fp, "%0.2f %0.2f %0.2f setrgbcolor\n0.5 setlinewidth\n", rgb[BLACK].r, rgb[BLACK].g, rgb[BLACK].b);

		QuadAng = 135.0 / (double)DEG_PER_RAD; // NW point
		x = (float)(cos(QuadAng) * RoomRadius);
		y = (float)(sin(QuadAng) * RoomRadius);
		(void) fprintf(fp, "newpath\n%0.2f pix %0.2f pix mt\n", x,y);

		QuadAng = 315.0 / (double)DEG_PER_RAD; // SE point
		x = (float)(cos(QuadAng) * RoomRadius);
		y = (float)(sin(QuadAng) * RoomRadius);
		(void) fprintf(fp, "%0.2f pix %0.2f pix lt\nclosepath\nstroke\n", x,y);

		QuadAng = 45.0 / (double)DEG_PER_RAD; // NE point
		x = (float)(cos(QuadAng) * RoomRadius);
		y = (float)(sin(QuadAng) * RoomRadius);
		(void) fprintf(fp, "newpath\n%0.2f pix %0.2f pix mt\n", x,y);

		QuadAng = 225.0 / (double)DEG_PER_RAD; // SW point
		x = (float)(cos(QuadAng) * RoomRadius);
		y = (float)(sin(QuadAng) * RoomRadius);
		(void) fprintf(fp, "%0.2f pix %0.2f pix lt\nclosepath\nstroke\n", x,y);

	}

	//  draw grid lines
	if(I.ParadigmType == OPEN_FIELD){
		double RoomRadius;
		int	OFPixelSize;
		float  point;

		RoomRadius = ArenaRadiusPix + ROOM_FRAME_INCREASE;
		OFPixelSize = (int)(TRACKER_XY_RESOLUTION / I.Options.OpenFieldDimension);

		(void) fprintf(fp, "%0.2f %0.2f %0.2f setrgbcolor\n0.5 setlinewidth\n", rgb[BLACK].r, rgb[BLACK].g, rgb[BLACK].b);

		for(i = 0; i <= TRACKER_XY_RESOLUTION; i += OFPixelSize){
			point = (float)(i - (TRACKER_XY_RESOLUTION / 2));
			// vertical lines
			(void) fprintf(fp, "%0.2f pix %0.2f pix mt\n", point, RoomRadius);
			(void) fprintf(fp, "%0.2f pix %0.2f pix lt\nstroke\n", point, -1.0 * RoomRadius);
			// horizontal lines
			(void) fprintf(fp, "%0.2f pix %0.2f pix mt\n", -1.0 * RoomRadius, point);
			(void) fprintf(fp, "%0.2f pix %0.2f pix lt\nstroke\n", RoomRadius, point);
		}
	}

	// draw track

	// define the Reinforced sector for avoidance since this was not set in Tracker
	if(I.ParadigmType == PLACE_AVOIDANCE){
		if(I.Target[frame].Type == REINFORCED_SECTOR){
                	MakeAvoidSectorMap(&ReinforcedMap, I, I.Target[frame].Sector);
                }else if(I.Target[frame].Type == REINFORCED_CIRCLE){
                	MakeAvoidCircleMap(&ReinforcedMap, I, I.Target[frame].Circle, 1);
		}
	}

	(void) fprintf(fp, "%0.2f %0.2f %0.2f setrgbcolor\n0.5 setlinewidth\n", rgb[GRAY].r, rgb[GRAY].g, rgb[GRAY].b);
	FirstGoodPosition = 1;
	NewEvent = 1;
	for(i = 0; i < I.NumberOfSamps; i ++){
		// Was the object detected?
		if((!t[i].x) || (!t[i].y)){
			if(!FirstGoodPosition)
				(void) fprintf(fp, "stroke\n");
			FirstGoodPosition = 1;
			continue;
		}

		// Transform from tracker to Cartesian coordinates
		x = (float)(t[i].x - I.Arena.CenterX);
		y = (float)(I.Arena.CenterY - t[i].y);
		if(FirstGoodPosition){
			(void) fprintf(fp, "%0.2f pix %0.2f pix mt\n", x,y);
			if(t[i].event){
				switch(DrawEvents){
					case 0: break;		/* don't draw anything */

					case 1: 		/* draw one mark per event */
						if((I.FileFormat == TRACKER_FORMAT) || (I.FileFormat == ITRACK_FORMAT) || (I.FileFormat == FGX_FORMAT)){ // Event is coded as a state
							if(t[i].event == SHOCK_STATE){
								if(NewEvent){
									(void) fprintf(fp, "stroke\n");
									if(I.Target[frame].Show){
										if(ReinforcedMap[t[i].y][t[i].x] == TARGET){	// make frame specific events
											DrawAnEvent(fp, x, y, rgb, PointsPerPixel, RED);
										}else{
											DrawAnEvent(fp, x, y, rgb, PointsPerPixel, BLUE);
										}
									}else{
										DrawAnEvent(fp, x, y, rgb, PointsPerPixel, BLUE);
									}
									(void) fprintf(fp, "%0.2f pix %0.2f pix mt\n", x,y);
									NewEvent = 0;
								}
							}else{
								if(t[i].event != BAD_SPOT_STATE){	// Use the BadSpot flag introduced by Tracker
									NewEvent = 1;
								}
							}
						}else{
							(void) fprintf(fp, "stroke\n");
							if(I.Target[frame].Show){
								DrawAnEvent(fp, x, y, rgb, PointsPerPixel, RED);
							}else{
								DrawAnEvent(fp, x, y, rgb, PointsPerPixel, BLUE);
							}
							(void) fprintf(fp, "%0.2f pix %0.2f pix mt\n", x,y);
						}
						break;

					case 2:
						(void) fprintf(fp, "stroke\n");
						if(I.Target[frame].Show){
							for(j = 0; j < t[i].event; j++){
								DrawAnEvent(fp, (float)(x + (j * 0.1)), (float)(y + (j * 0.1)), rgb, PointsPerPixel, RED);
							}
						}else{
							for(j = 0; j < t[i].event; j++){
								DrawAnEvent(fp, (float)(x + (j * 0.1)), (float)(y + (j * 0.1)), rgb, PointsPerPixel, BLUE);
							}
						}
						(void) fprintf(fp, "%0.2f pix %0.2f pix mt\n", x,y);
						break;
					default:	
						break;
				}
			}else{
				if(t[i].event != BAD_SPOT_STATE){	// Use the BadSpot flag introduced by Tracker
					NewEvent = 1;
				}
			}	
			FirstGoodPosition = 0;
			continue;
		}
		(void) fprintf(fp, "%0.2f pix %0.2f pix lt\n", x,y);
		if(t[i].event){
			switch(DrawEvents){
				case 0: break;		/* don't draw anything */

				case 1: 		/* draw one mark per event */
					if((I.FileFormat == TRACKER_FORMAT) || (I.FileFormat == ITRACK_FORMAT) || (I.FileFormat == FGX_FORMAT)){ // Event is coded as a state
						if(t[i].event == SHOCK_STATE){
							if(NewEvent){
								(void) fprintf(fp, "stroke\n");
								if(I.Target[frame].Show){
									if(ReinforcedMap[t[i].y][t[i].x] == TARGET){	// make frame specific events
										// DEBUG(-1 * i)
										DrawAnEvent(fp, x, y, rgb, PointsPerPixel, RED);
									}else{
										DrawAnEvent(fp, x, y, rgb, PointsPerPixel, BLUE);
									}
								}else{
									DrawAnEvent(fp, x, y, rgb, PointsPerPixel, BLUE);
								}
								(void) fprintf(fp, "%0.2f pix %0.2f pix mt\n", x,y);
								NewEvent = 0;
							}
						}else{
							if(t[i].event != BAD_SPOT_STATE){       // Use the BadSpot flag introduced by Tracker	
								NewEvent = 1;
							}
						}
					}else{
						(void) fprintf(fp, "stroke\n");
						if(I.Target[frame].Show){
							DrawAnEvent(fp, x, y, rgb, PointsPerPixel, RED);
						}else{
							DrawAnEvent(fp, x, y, rgb, PointsPerPixel, BLUE);
						}
						(void) fprintf(fp, "%0.2f pix %0.2f pix mt\n", x,y);
					}
					break;

				case 2:
					(void) fprintf(fp, "stroke\n");
					if(I.Target[frame].Show){
						for(j = 0; j < t[i].event; j++){
							DrawAnEvent(fp, (float)(x + (j * 0.1)), (float)(y + (j * 0.1)), rgb, PointsPerPixel, RED);
						}
					}else{
						for(j = 0; j < t[i].event; j++){
							DrawAnEvent(fp, (float)(x + (j * 0.1)), (float)(y + (j * 0.1)), rgb, PointsPerPixel, BLUE);
						}
					}
					(void) fprintf(fp, "%0.2f pix %0.2f pix mt\n", x,y);
					break;

				default:	
					break;
			}
		}else{
			NewEvent = 1;
		}
	}
	if(!FirstGoodPosition)
		(void) fprintf(fp, "stroke\n");

	// reset coordinate system upon return
	(void) fprintf(fp, "grestore\n");

	return;
	
}