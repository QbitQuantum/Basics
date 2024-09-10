void tidySolutions(int attack, int knightNumber, int coverage, int counter)
{
	FILE* inFile = mkSolDir(attack, coverage, knightNumber, maximisedFile, true, false, counter);
	FILE* duplicatesOutFile = NULL;
	FILE* tidiedOutFile = NULL;
	solution sol;
	solutionTree = (solutionLeaf *)malloc(sizeof(solutionLeaf) * MAX_SOLUTIONS);
	solutionLeaf* slot = solutionTree;
	unsigned long long count = 0;
	bool error = false;
	initialiseXYs();

	int pos = knightsYX[attack][1] > knightsYX[attack][0] ? knightsYX[attack][1] : knightsYX[attack][0];
	if (pos + HASH_BORDER >= MAX_GRID)
	{
		printf("Cannot hash more than %d rows", (MAX_GRID - HASH_BORDER));
		return;
	}

	long long currentPosition = _ftelli64(inFile);
	size_t loop = readSolution(&sol, inFile);
	unsigned long long mask = _rotr64(MASK, pos);
	while (loop)
	{
		int offset = 0;
		int multiplierIndex = 0;
		unsigned long long rowHash = 0;
		unsigned long long hash = 0;
		for (int row = 0; row < pos; row++)
		{
			unsigned long long part = (sol.coverage[row] & mask);
			if (offset < pos)
			{
				part = _rotl64(part, pos - offset);
			}
			else if (offset > pos)
			{
				part = _rotr64(part, offset - pos);
			}

			rowHash |= part;

			offset += HASH_BORDER;
			if (offset > MAX_GRID)
			{
				offset -= MAX_GRID;
				if (multiplierIndex == 0)
				{
					hash |= rowHash;
				}
				else
				{
					hash |= (rowHash + 1) * multiplier[multiplierIndex];
					multiplierIndex++;
				}
			}
		}

		for (int row = pos; row < pos + HASH_BORDER; row++)
		{
			hash |= (_rotr64(sol.coverage[row], MAX_GRID - HASH_BORDER - pos) + 1) * multiplier[multiplierIndex];
			multiplierIndex++;
		}

		slot->hash = hash;
		slot->bigger = NULL;
		slot->equal = NULL;
		slot->lesser = NULL;
		slot->solutionOffset = currentPosition;

		if (count > 0)
		{
			solutionLeaf* root = solutionTree;
			while (true)
			{
				if (hash == root->hash)
				{
					if (root->equal == NULL)
					{
						root->equal = slot;
						break;
					}
					else
					{
						root = root->equal;
					}
				}
				else if (hash > root->hash)
				{
					if (root->bigger == NULL)
					{
						root->bigger = slot;
						break;
					}
					else
					{
						root = root->bigger;
					}
				}
				else if (hash < root->hash)
				{
					if (root->lesser == NULL)
					{
						root->lesser = slot;
						break;
					}
					else
					{
						root = root->lesser;
					}

				}
			}
		}

		slot++;
		count++;
		currentPosition = _ftelli64(inFile);
		loop = readSolution(&sol, inFile);
		if ((count == MAX_SOLUTIONS) && loop)
		{
			printf("Too many solutions to manage.");
			error = true;
			break;
		}
	}
	fclose(inFile);

	if (error)
	{
		return;
	}

	inFile = mkSolDir(attack, coverage, knightNumber, maximisedFile, true, false, counter);
	tidiedOutFile = mkSolDir(attack, coverage, knightNumber, tidiedFile, false, false, 0);
	slot = solutionTree;
	readSolution(&sol, inFile);
	solution compare;
	while (count)
	{
		if (slot->equal == NULL)
		{
			//Could be in a maximised file less than counter!
			writeSolution(&sol, tidiedOutFile);
			slot++;
		}
		else
		{
			solutionLeaf* test = slot->equal;
			int state = STATE_KEEP;
			while (test != NULL)
			{
				_fseeki64(inFile, test->solutionOffset, SEEK_SET);
				readSolution(&compare, inFile);
				int cmp = memcmp(sol.coverage, compare.coverage, sizeof(unsigned long long) * MAX_GRID);
				if (cmp == 0)
				{
					cmp = memcmp(sol.knights, compare.knights, sizeof(unsigned long long) * MAX_GRID);
					if (cmp == 0)
					{
						state = STATE_SCRAP;
						break;
					}
					else
					{
						state = STATE_DUPLICATE;
					}
				}
				test = test->equal;
			}

			if (state == STATE_KEEP)
			{
				writeSolution(&sol, tidiedOutFile);
			}
			else if (state == STATE_DUPLICATE)
			{
				if (duplicatesOutFile == NULL)
				{
					duplicatesOutFile = mkSolDir(attack, coverage, knightNumber, duplicatesFile, false, false, 0);
				}
				writeSolution(&sol, duplicatesOutFile);
			}

			slot++;
			_fseeki64(inFile, slot->solutionOffset, SEEK_SET);
		}
		readSolution(&sol, inFile);
		count--;
	}
	fclose(inFile);
	fclose(tidiedOutFile);
	if (duplicatesOutFile != NULL)
	{
		fclose(duplicatesOutFile);
	}

}