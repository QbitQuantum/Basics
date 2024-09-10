bool MEModel::loadTrainingExamples( const char *trainFile )
{
	FILE *fin = fopen(trainFile,"r");
	if ( fin == NULL )
	{
		fprintf( stderr, "open train file %s failed!\n", trainFile );
		return false;
	}
	int lineNum = 0;
	int fieldNum = 0;
	int ch;
	bool endOfFile = false;
	int curFieldCnt = 0;
	while( !endOfFile )
	{
		ch = fgetc(fin);
		curFieldCnt = 0;
		while( true )
		{
			while( !isLineEnd(ch) && isSpace(ch) )
				ch = fgetc(fin);
			if( isLineEnd(ch) )
				break;
			while( !isLineEnd(ch) && !isSpace(ch) )
				ch = fgetc(fin);
			curFieldCnt ++;
		}
		if ( curFieldCnt > 0 )
		{
			lineNum ++;
			fieldNum += curFieldCnt;
		}
		if( ch == EOF )
			endOfFile = true;
	}
	rewind(fin);
	M = lineNum;
	VarStr word;
	endOfFile = false;
	xspace = new SpElem[fieldNum];
	x = new SpElem*[M];
	y = new int[M];
	lineNum = 0;
	int xIndex = 0;
	while( !endOfFile )
	{
		ch = fgetc(fin);
		curFieldCnt = 0;
		int curY = 0, curX = 0;
		char *ystr = NULL;
		while( true )
		{
			while( !isLineEnd(ch) && isSpace(ch) )
				ch = fgetc(fin);
			if( isLineEnd(ch) )
				break;
			word.clear();
			while( !isLineEnd(ch) && !isSpace(ch) )
			{
				word.add(ch);
				ch = fgetc(fin);
			}
			curFieldCnt ++;
			if( curFieldCnt == 1 )
			{
				ystr = new char[word.length()+1];
				strcpy(ystr,word.c_str());
			}
			else
			{
				curX = feaIdMap.add(word.c_str());
				xspace[xIndex].index = curX;
				xspace[xIndex].value = 1;
				if ( curFieldCnt == 2 )
					x[lineNum] = &xspace[xIndex];
				xIndex ++;
			}
		}
		if ( curFieldCnt > 1 )
		{
			xspace[xIndex].index = -1; xspace[xIndex].value = 0;
			xIndex ++;
			curY = classNameIdMap.add(ystr);
			y[lineNum] = curY;
			lineNum ++;
		}
		if( ystr != NULL )
			delete []ystr;
		if ( ch == EOF )
			endOfFile = true;
	}
	
	fclose(fin);
	M = lineNum;
	classNumber = (int)classNameIdMap.size();

	needDestroyTrain = true;
	return true;
}