int main(int argc, char **argv)
{
	SeqPool seqpool;
	bool cs;

	if( argc < 2 ) {	PrintUsage();	return 1;	}	

	cs = true;

	seqpool.Add(argv[1]);

	for( SamOutput theSam; theSam.Get(); )
	{
		char str[81];
		char seq[4096];
		char csseq[4096];	
		int qLen, rLen;
		int numErr, numLErr, numRErr;	
		int leftLen, rightLen;
		int i;
		int Pos;
		int identity;
		
		qLen = strlen(theSam.Qual);
		identity = IdentityCut;

		if( theSam.AS < ScoreCut )
			continue;
	
		if( strncmp( theSam.CIGAR, ItoA(qLen, str, 10), strlen(ItoA(qLen, str, 10)) ) != 0 )
			continue;

		if(cs)
		{
			if( theSam.IsPlusStrand() )
				strcpy(seq, seqpool.GiveMe(theSam.rName)->c_str());
			else
				ToComplement(seq, seqpool.GiveMe(theSam.rName)->c_str());
		}
		else
			strcpy(seq, seqpool.GiveMe(theSam.rName)->c_str());

		numErr=0;
		numLErr = 0;
		numRErr = 0;
		leftLen = 0;
		rightLen = 0;
		rLen = strlen(seq);

		if(cs)
		{
			ToColorSpace(csseq, seq);

			if( theSam.IsPlusStrand() == 0)
				Pos = theSam.Pos-2;
			else
				Pos = rLen-qLen-theSam.Pos;

			for(i=1; i<qLen; i++)
			{
				if( (i+Pos) < 0 )
					continue;
				if( csseq[i+Pos] != theSam.CS[i+1] )
				{
					numErr++;
					if( (i+Pos) <= (rLen-41) )
						numLErr++;
					if( (i+Pos) >= 39 )
						numRErr++;
				}

				if( (i+Pos) <= (rLen-41) )
					leftLen++;
				if( (i+Pos) >= 39 )
					rightLen++;
			}
		}
		else
		{
//			puts(seq);
//			puts(theSam.Seq);

			Pos = theSam.Pos-1;

			for(i=0; i<qLen; i++)
			{
				if( (i+Pos) < 0 )
					continue;
				if( seq[i+Pos] != theSam.Seq[i] )
				{
					numErr++;
					if( (i+Pos) < (rLen-40) )
						numLErr++;
					if( (i+Pos) >= 40 )
						numRErr++;
				}

				if( (i+Pos) < (rLen-40) )
					leftLen++;
				if( (i+Pos) >= 40 )
					rightLen++;
			}
			
//			printf("%d\t%d\t%d\t%d\n", theSam.Pos, numErr, numLErr, numRErr);
		}

		if( numErr > ( qLen*(100-identity)/75 + 1 ) )
		{
			ErrMsg("numErr.\n");
			continue;
		}
		if( leftLen < LenCut )
			continue;
		if( rightLen < LenCut )
			continue;

		if( numErr > 2 )
			continue;

		if( leftLen < 20 )	
			if( numLErr > 1 )
				continue;
			
		if( rightLen < 20 )
			if( numRErr > 1 )
				continue;

		theSam.Print();
	}

	return 0;
}