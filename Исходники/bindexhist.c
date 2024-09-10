/* Get the matches for the contig/pos */
int GetMatchesFromContigPos(RGIndex *index,
		RGBinary *rg,
		uint32_t curContig,
		uint32_t curPos,
		int64_t *numForward,
		int64_t *numReverse)
{
	char *FnName = "GetMatchesFromContigPos";
	int returnLength, returnPosition;
	char *read=NULL;
	RGRanges ranges;
	RGMatch match;
	int readLength = index->width;
	int8_t readInt[SEQUENCE_LENGTH];
	int32_t i;

	/* Initialize */
	RGRangesInitialize(&ranges);
	RGMatchInitialize(&match);

	/* Get the read */
	RGBinaryGetReference(rg,
			curContig,
			curPos,
			FORWARD,
			0,
			&read,
			readLength,
			&returnLength,
			&returnPosition);
	assert(returnLength == readLength);
	assert(returnPosition == curPos);

	ConvertSequenceToIntegers(read, readInt, readLength);

	RGIndexGetRangesBothStrands(index,
			rg,
			readInt,
			readLength,
			0,
			INT_MAX,
			INT_MAX,
			rg->space,
			BothStrands,
			&ranges);

	/* Transfer ranges to matches */
	RGRangesCopyToRGMatch(&ranges,
			index,
			&match,
			rg->space,
			0);

	/* Remove duplicates */
	RGMatchRemoveDuplicates(&match,
			INT_MAX);

	assert(0 < match.numEntries);
	(*numForward) = (*numReverse) = 0;

	for(i=0;i<match.numEntries;i++) {
		switch(match.strands[i]) {
			case FORWARD:
				(*numForward)++;
				break;
			case REVERSE:
				(*numReverse)++;
				break;
			default:
				PrintError(FnName, NULL, "Could not understand strand", Exit, OutOfRange);
				break;
		}
	}

	assert((*numForward) > 0); /* It should at least match itself ! */
	assert((*numReverse) >= 0);

	RGRangesFree(&ranges);
	RGMatchFree(&match);
	free(read);
	read=NULL;

	return 1;
}