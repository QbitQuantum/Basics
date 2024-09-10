/*
Constructor.
Loading precalculated data.
*/
CPathEstimator::CPathEstimator(CPathFinder* pf, unsigned int BSIZE, unsigned int mmOpt, string name) :
pathFinder(pf),
BLOCK_SIZE(BSIZE),
BLOCK_PIXEL_SIZE(BSIZE * SQUARE_SIZE),
BLOCKS_TO_UPDATE(SQUARES_TO_UPDATE / (BLOCK_SIZE * BLOCK_SIZE) + 1),
moveMathOptions(mmOpt)
{
	//Gives the changes in (x,z) when moved one step in given direction.
	//(Need to be placed befor pre-calculations)
	directionVector[PATHDIR_LEFT].x = 1;
	directionVector[PATHDIR_LEFT].y = 0;
	directionVector[PATHDIR_LEFT_UP].x = 1;
	directionVector[PATHDIR_LEFT_UP].y = 1;
	directionVector[PATHDIR_UP].x = 0;
	directionVector[PATHDIR_UP].y = 1;
	directionVector[PATHDIR_RIGHT_UP].x = -1;
	directionVector[PATHDIR_RIGHT_UP].y = 1;
	directionVector[PATHDIR_RIGHT].x = -1;
	directionVector[PATHDIR_RIGHT].y = 0;
	directionVector[PATHDIR_RIGHT_DOWN].x = -1;
	directionVector[PATHDIR_RIGHT_DOWN].y = -1;
	directionVector[PATHDIR_DOWN].x = 0;
	directionVector[PATHDIR_DOWN].y = -1;
	directionVector[PATHDIR_LEFT_DOWN].x = 1;
	directionVector[PATHDIR_LEFT_DOWN].y = -1;

	goalSqrOffset.x=BLOCK_SIZE/2;
	goalSqrOffset.y=BLOCK_SIZE/2;

	//Creates the block-map and the vertices-map.
	nbrOfBlocksX = gs->mapx / BLOCK_SIZE;
	nbrOfBlocksZ = gs->mapy / BLOCK_SIZE;
	nbrOfBlocks = nbrOfBlocksX * nbrOfBlocksZ;

	blockState = new BlockInfo[nbrOfBlocks];
	nbrOfVertices = moveinfo->moveData.size() * nbrOfBlocks * PATH_DIRECTION_VERTICES;
	vertex = new float[nbrOfVertices];
	openBlockBufferPointer=openBlockBuffer;

	int i;
	for(i = 0; i < nbrOfVertices; i++)
		vertex[i] = PATHCOST_INFINITY;

	//Initialize blocks.
	int x, z;
	for(z = 0; z < nbrOfBlocksZ; z++){
		for(x = 0; x < nbrOfBlocksX; x++) {
			int blocknr = z * nbrOfBlocksX + x;
			blockState[blocknr].cost = PATHCOST_INFINITY;
			blockState[blocknr].options = 0;
			blockState[blocknr].parentBlock.x = -1;
			blockState[blocknr].parentBlock.y = -1;
			blockState[blocknr].sqrCenter = new int2[moveinfo->moveData.size()];
		}
	}

	//Pre-read/calculate data.
	PrintLoadMsg("Reading estimate path costs");
	if(!ReadFile(name)) {
		//Generate text-message.
		char calcMsg[1000], buffer[10];
		strcpy(calcMsg, "Analyzing map accessability \"");
		SNPRINTF(buffer,10,"%d",BLOCK_SIZE);
		strcat(calcMsg, buffer);
		strcat(calcMsg, "\"");
		PrintLoadMsg(calcMsg);
		//Calculating block-center-offsets.
		for(z = 0; z < nbrOfBlocksZ; z++) {
			for(x = 0; x < nbrOfBlocksX; x++) {
				vector<MoveData*>::iterator mi;
				for(mi = moveinfo->moveData.begin(); mi < moveinfo->moveData.end(); mi++) {
					FindOffset(**mi, x, z);
				}
			}
		}

		//Calculating vectors.
		vector<MoveData*>::iterator mi;
		for(mi = moveinfo->moveData.begin(); mi < moveinfo->moveData.end(); mi++) {
			//Generate text-message.
			char calcMsg[10000];
			sprintf(calcMsg,"Calculating estimate path costs \"%i\" %i/%i",BLOCK_SIZE,(*mi)->pathType,moveinfo->moveData.size());
			PrintLoadMsg(calcMsg);
			if(net) net->Update();	//prevent timeout 
			//Calculate
			for(z = 0; z < nbrOfBlocksZ; z++) {
				for(x = 0; x < nbrOfBlocksX; x++) {
					CalculateVertices(**mi, x, z);
				}
			}
		}
		WriteFile(name);
	}

	//As all vertexes are bidirectional and having equal values
	//in both directions, only one value are needed to be stored.
	//This vector helps getting the right vertex.
	//(Need to be placed after pre-calculations)
	directionVertex[PATHDIR_LEFT] = PATHDIR_LEFT;
	directionVertex[PATHDIR_LEFT_UP] = PATHDIR_LEFT_UP;
	directionVertex[PATHDIR_UP] = PATHDIR_UP;
	directionVertex[PATHDIR_RIGHT_UP] = PATHDIR_RIGHT_UP;
	directionVertex[PATHDIR_RIGHT] = int(PATHDIR_LEFT) - PATH_DIRECTION_VERTICES;
	directionVertex[PATHDIR_RIGHT_DOWN] = int(PATHDIR_LEFT_UP) - (nbrOfBlocksX * PATH_DIRECTION_VERTICES) - PATH_DIRECTION_VERTICES;
	directionVertex[PATHDIR_DOWN] = int(PATHDIR_UP) - (nbrOfBlocksX * PATH_DIRECTION_VERTICES);
	directionVertex[PATHDIR_LEFT_DOWN] = int(PATHDIR_RIGHT_UP) - (nbrOfBlocksX * PATH_DIRECTION_VERTICES) + PATH_DIRECTION_VERTICES;

	pathCache=new CPathCache(nbrOfBlocksX,nbrOfBlocksZ);
}