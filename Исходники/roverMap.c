void mapRoverTask( void *param ){
//static portTASK_FUNCTION( mapRoverTask, pvParameters )
	RoverMapStruct *roverMapStruct = (RoverMapStruct *) param;
	
	MapCorner receivedCorner;

	double totalAngle = 0;
	double totalCalcAngle = 90.0;
	double area;
	
	char buf[20];
	double number;
	//int intPart, decimalPart;
	uint8_t cornersCount = 0;

	sprintf(guiMapCoordinates, "");
	polyComp = 0;
	
	for(;;){
		if (xQueueReceive(roverMapStruct->inQ, (void *) &receivedCorner, portMAX_DELAY) != pdTRUE) {
			VT_HANDLE_FATAL_ERROR(0);
		}

		if(strlen(guiMapCoordinates) >= (BUFFER_SIZE - 10)){
			sprintf(guiMapCoordinates, "");
		}
		if(strlen(debugBuf) >= (BUFFER_SIZE - 10)){
			sprintf(debugBuf, "");
		}
		printFloat("QReced:", receivedCorner.distSide, 1);
		// Print the received distance reading
		vtLEDToggle(0x40);
		printFloat("Angle: ", receivedCorner.angleCornerExterior, 0);;
		double ang;
		if(roverMapStruct->taskFlags == REGULAR && roverMapStruct->numberSides != 0){
			receivedCorner.angleCornerExterior = 360.0/roverMapStruct->numberSides;
		}
		else{
			ang = receivedCorner.angleCornerExterior;
			receivedCorner.angleCornerExterior = receivedCorner.angleCornerExterior + receivedCorner.tempBefore/2.0;
			if(receivedCorner.angleCornerExterior>90) receivedCorner.angleCornerExterior = 90;
		}
		//printFloat("Side Dist: ", receivedCorner.distSide, 1);
		receivedCorner.tempPow = mapCorners[cornersCount-1].distFromSide * pow(receivedCorner.angleCornerExterior/90.0, 5);
		
		totalAngle += receivedCorner.angleCornerExterior;
		if(cornersCount != 0){
			//totalAngle += receivedCorner.angleCornerExterior;
			//receivedCorner.distSide += mapCorners[cornersCount-1].distFromSide;
			printFloat("PrevSide:", mapCorners[cornersCount-1].distFromSide, 1);
			printFloat("WithPrevSide:", receivedCorner.distSide, 1);
			
			// Teja experimenting
			receivedCorner.distSide +=  receivedCorner.tempFrontDist + mapCorners[cornersCount-1].distFromSide*sin(mapCorners[cornersCount-1].angleCornerExterior*M_PI/180.0)*sin(mapCorners[cornersCount-1].angleCornerExterior*M_PI/180.0);

			// Yasir's conversion to coordinates
			xPoints[cornersCount] = xPoints[cornersCount - 1] + receivedCorner.distSide*cos(totalCalcAngle*M_PI/180.0);
			yPoints[cornersCount] = yPoints[cornersCount - 1] + receivedCorner.distSide*sin(totalCalcAngle*M_PI/180.0);
			totalCalcAngle -= receivedCorner.angleCornerExterior;

			sprintf(buf, "C=%d Deg=%.2f Dist=%.2f A=%.2f\n", cornersCount+1, receivedCorner.angleCornerExterior, receivedCorner.distSide, calculateArea(cornersCount+1, xPoints, yPoints));
			strcat(debugBuf, buf);

			//sprintf(buf, "Deg=%.1f F=%.1f OA=%.1f SB=%.1f SD=%.1f SDP=%1.f FD=%.1f Dist=%.1f S=%d\n", receivedCorner.angleCornerExterior,receivedCorner.tempFront, ang, receivedCorner.tempBefore, mapCorners[cornersCount-1].distFromSide, receivedCorner.tempPow, receivedCorner.tempFrontDist, receivedCorner.distSide, cornersCount);
			//strcat(debugBuf, buf);

			//sprintf(buf, "A=%f\n", calculateArea(cornersCount+1, xPoints, yPoints));
			//strcat(debugBuf, buf);
			if ((totalAngle) >= TOTAL_ANGLE_THRESHOLD){
				// TODO: calculate area;
				// param for calculateArea (side) is 1 minus the number of sides
				if(polyComp == 0){
					polyComp = -1;
					sprintf(buf, "%d,%d ", (int)(xPoints[cornersCount]*MAP_SCALE_FACTOR + MAP_X_OFFSET), (int)(yPoints[cornersCount]*-MAP_SCALE_FACTOR + MAP_Y_OFFSET));
					strcat(guiMapCoordinates, buf);
				}
				else{
					polyComp = cornersCount;
					sprintf(buf, "%d,%d", MAP_X_OFFSET, MAP_Y_OFFSET);
					strcat(guiMapCoordinates, buf);
				}
				sprintf(buf, "\n** Polygon complete ** Corners=%d A=%f\n\n", cornersCount+1,calculateArea(cornersCount+1, xPoints, yPoints));
				strcat(debugBuf, buf);
			}
			else{
				sprintf(buf, "%d,%d ", (int)(xPoints[cornersCount]*MAP_SCALE_FACTOR + MAP_X_OFFSET), (int)(yPoints[cornersCount]*-MAP_SCALE_FACTOR + MAP_Y_OFFSET));
				strcat(guiMapCoordinates, buf);
			}
		}
		else{
			totalCalcAngle = 90;
			xPoints[0] = 0;
			xPoints[0] = 0;
			sprintf(buf, "%d,%d ", (int)(xPoints[cornersCount]*MAP_SCALE_FACTOR + MAP_X_OFFSET), (int)(yPoints[cornersCount]*-MAP_SCALE_FACTOR + MAP_Y_OFFSET));
			strcat(guiMapCoordinates, buf);
		}

		if(cornersCount < MAXIMUM_CORNERS){
			mapCorners[cornersCount] = receivedCorner;
			++cornersCount;
		}


		
	}
}