/* The terrain revealing ray callback */
static void doWaveTerrain(const BASE_OBJECT *psObj, TILEPOS *recordTilePos, int *lastRecordTilePos)
{
	const int sx = psObj->pos.x;
	const int sy = psObj->pos.y;
	const int sz = psObj->pos.z + MAX(MIN_VIS_HEIGHT, psObj->sDisplay.imd->max.y);
	const unsigned radius = objSensorRange(psObj);
	const int rayPlayer = psObj->player;
	size_t i;
	size_t size;
	const WavecastTile *tiles = getWavecastTable(radius, &size);
	int tileHeight, perspectiveHeight, perspectiveHeightLeeway;
#define MAX_WAVECAST_LIST_SIZE 1360  // Trivial upper bound to what a fully upgraded WSS can use (its number of angles). Should probably be some factor times the maximum possible radius. Is probably a lot more than needed. Tested to need at least 180.
	int heights[2][MAX_WAVECAST_LIST_SIZE];
	int angles[2][MAX_WAVECAST_LIST_SIZE + 1];
	int readListSize = 0, readListPos = 0, writeListPos = 0;  // readListSize, readListPos dummy initialisations.
	int readList = 0;  // Reading from this list, writing to the other. Could also initialise to rand()%2.
	int lastHeight = 0;  // lastHeight dummy initialisation.
	int lastAngle = 0x7FFFFFFF;

	// Start with full vision of all angles. (If someday wanting to make droids that can only look in one direction, change here, after getting the original angle values saved in the wavecast table.)
	heights[!readList][writeListPos] = -0x7FFFFFFF-1;  // Smallest integer.
	angles[!readList][writeListPos] = 0;               // Smallest angle.
	++writeListPos;

	for (i = 0; i < size; ++i)
	{
		const int mapX = map_coord(sx) + tiles[i].dx;
		const int mapY = map_coord(sy) + tiles[i].dy;
		MAPTILE *psTile;
		bool seen = false;

		if (mapX < 0 || mapX >= mapWidth || mapY < 0 || mapY >= mapHeight)
		{
			continue;
		}
		psTile = mapTile(mapX, mapY);
		tileHeight = psTile->height;
		perspectiveHeight = (tileHeight - sz) * tiles[i].invRadius;
		perspectiveHeightLeeway = (tileHeight - sz + MIN_VIS_HEIGHT) * tiles[i].invRadius;

		if (tiles[i].angBegin < lastAngle)
		{
			// Gone around the circle. (Or just started scan.)
			angles[!readList][writeListPos] = lastAngle;

			// Flip the lists.
			readList = !readList;
			readListPos = 0;
			readListSize = writeListPos;
			writeListPos = 0;
			lastHeight = 1;  // Impossible value since tiles[i].invRadius > 1 for all i, so triggers writing first entry in list.
		}
		lastAngle = tiles[i].angEnd;

		while (angles[readList][readListPos + 1] <= tiles[i].angBegin && readListPos < readListSize)
		{
			++readListPos;  // Skip, not relevant.
		}

		while (angles[readList][readListPos] < tiles[i].angEnd && readListPos < readListSize)
		{
			int oldHeight = heights[readList][readListPos];
			int newHeight = MAX(oldHeight, perspectiveHeight);
			seen = seen || perspectiveHeightLeeway >= oldHeight; // consider point slightly above ground in case there is something on the tile
			if (newHeight != lastHeight)
			{
				heights[!readList][writeListPos] = newHeight;
				angles[!readList][writeListPos] = MAX(angles[readList][readListPos], tiles[i].angBegin);
				lastHeight = newHeight;
				++writeListPos;
				ASSERT_OR_RETURN( , writeListPos <= MAX_WAVECAST_LIST_SIZE, "Visibility too complicated! Need to increase MAX_WAVECAST_LIST_SIZE.");
			}
			++readListPos;
		}
		--readListPos;

		if (seen)
		{
			// Can see this tile.
			psTile->tileExploredBits |= alliancebits[rayPlayer];                            // Share exploration with allies too
			visMarkTile(psObj, mapX, mapY, psTile, recordTilePos, lastRecordTilePos);   // Mark this tile as seen by our sensor
		}
	}