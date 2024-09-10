int readDWI(std::vector<struct ARROW> *chart, std::vector<struct FREEZE> *holds, int songID, int chartType)
{
	char filename[] = "DATA/dwis/101.dwi";
	FILE* fp = NULL;
	std::vector<struct BEAT_NOTE> beats;

	// hopefully open the target DWI file
	filename[10] = (songID/100 % 10) + '0';
	filename[11] = (songID/10 % 10) + '0';
	filename[12] = (songID % 10) + '0';

	if ( fopen_s(&fp, filename, "rt") != 0 )
	{
		// as a fall back, open a memory dump of a chart (legacy chart data)
		return readDMXSQ(chart, holds, songID, chartType);
	}

	// fix any potential bugs regarding data from one chart accidentally merging into the next chart
	chart->clear();
	holds->clear();
	int gap = 0;
	float timePerBeat = 400.0; // 150 BPM

	// start reading tags
	readNextTag(fp);
	while ( tagName[0] != 0 )
	{
		if ( _strcmpi("SINGLE", tagName) == 0 )
		{
			if ( _strcmpi("BASIC", tagValue) == 0 && chartType == SINGLE_MILD )
			{
				processChartString(&beats, tagLeftSide, 0);
			}
			else if ( _strcmpi("ANOTHER", tagValue) == 0 && chartType == SINGLE_WILD )
			{
				processChartString(&beats, tagLeftSide, 0);
			}
			else if ( _strcmpi("MANIAC", tagValue) == 0 && chartType == SINGLE_ANOTHER )
			{
				processChartString(&beats, tagLeftSide, 0);
			}
		}
		if ( _strcmpi("DOUBLE", tagName) == 0 )
		{
			if ( _strcmpi("BASIC", tagValue) == 0 && chartType == DOUBLE_MILD )
			{
				processChartString(&beats, tagLeftSide, 0);
				processChartString(&beats, tagRightSide, 1);
			}
			else if ( _strcmpi("ANOTHER", tagValue) == 0 && chartType == DOUBLE_WILD )
			{
				processChartString(&beats, tagLeftSide, 0);
				processChartString(&beats, tagRightSide, 1);
			}
			else if ( _strcmpi("MANIAC", tagValue) == 0 && chartType == DOUBLE_ANOTHER )
			{
				processChartString(&beats, tagLeftSide, 0);
				processChartString(&beats, tagRightSide, 1);
			}
		}
		if ( _strcmpi("BPM", tagName) == 0 )
		{
			float bpm = atof(tagValue);
			timePerBeat = BPM_TO_MSEC(bpm);

			// set the initial scroll rate // WHY DOES THIS MAKE SONG NOT END? affects end of song marker somehow?
			struct ARROW a;
			a.timing = 0;
			a.color = bpm;
			a.type = BPM_CHANGE;
			a.judgement = UNSET;
			chart->push_back(a);
		}
		if ( _strcmpi("GAP", tagName) == 0 )
		{
			gap = atoi(tagValue);
			al_trace("gap = %d\r\n", gap);
		}
		if ( _strcmpi("CHANGEBPM", tagName) == 0 ) // #CHANGEBPM:992.000=95.000,1016.000=190.000;
		{
			char* token, *next;
			token = strtok_s(tagValue, ",;", &next);

			while ( token != NULL )
			{
				char leftSide[32], rightSide[32];
				char* equalsPos = strchr(token, '=');
				if ( equalsPos == NULL )
				{
					continue;
				}
				strncpy_s(leftSide, token, equalsPos - token);
				strcpy_s(rightSide, equalsPos+1);

				struct BEAT_NOTE b;
				b.beat = atof(leftSide)/4.0;
				b.param = atof(rightSide);
				b.type = BPM_CHANGE;
				beats.push_back(b);

				token = strtok_s(NULL, ",;", &next);
			}
		}
		if ( _strcmpi("FREEZE", tagName) == 0 ) // #FREEZE:668.000=327.000,1292.000=967.000;
		{
			char* token, *next;
			token = strtok_s(tagValue, ",;", &next);

			while ( token != NULL )
			{
				char leftSide[32], rightSide[32];
				char* equalsPos = strchr(token, '=');
				if ( equalsPos == NULL )
				{
					continue;
				}
				strncpy_s(leftSide, token, equalsPos - token);
				strcpy_s(rightSide, equalsPos+1);

				struct BEAT_NOTE b;
				b.beat = atof(leftSide)/4.0;
				b.param = atof(rightSide);
				b.type = SCROLL_STOP;
				beats.push_back(b);
				
				token = strtok_s(NULL, ",;", &next);
			}
		}

		// next loop
		readNextTag(fp);
	}

	sort(beats.begin(), beats.end(), sortNoteFunction);

	// for each item in the beats vector, create a struct ARROW (real chart object) and translate 'DWI beats' to milliseconds
	int numNotes = beats.size();
	float currentTime = gap;
	float lastBeatProcessed = 0.0;

	for ( int i = 0; i < numNotes; i++ )
	{
		struct ARROW a;
		struct FREEZE f;
		float beatsDifference = beats[i].beat - lastBeatProcessed;
		lastBeatProcessed = beats[i].beat;

		currentTime += timePerBeat*beatsDifference;

		if (currentTime < 0)
		{
			continue; // uh-oh;
		}
		al_trace("%f\r\n", currentTime);

		switch ( beats[i].type )
		{
		case TAP:
			a.timing = currentTime;
			a.color = calculateArrowColor(a.timing, timePerBeat);
			a.type = TAP;
			a.columns[0] = beats[i].column;
			a.judgement = UNSET;
			chart->push_back(a);
			break;
		case HOLD_START:
			f.startTime = currentTime;
			f.columns[0] = beats[i].column;
			f.endTime1 = getMillisecondsAtBeat(beats[i].param, &beats, i, currentTime, timePerBeat); //it ends at beat beats[i].param
			holds->push_back(f); 
			break;
		case BPM_CHANGE:
			a.timing = currentTime;
			a.color = beats[i].param;
			a.type = BPM_CHANGE;
			a.judgement = UNSET;
			chart->push_back(a);

			timePerBeat = BPM_TO_MSEC(beats[i].param); // new tempo! the length of a beat has henceforth and immediately changed
			break;
		case SCROLL_STOP:
			a.timing = currentTime;
			a.color = beats[i].param;
			a.type = SCROLL_STOP;
			chart->push_back(a);

			currentTime += beats[i].param; // advance the time
			break;
		case END_SONG:
			a.timing = currentTime + 1000; // TODO: something better than this, maybe check the mp3?
			a.type = END_SONG;
			chart->push_back(a);
			break;
		default:
			al_trace("IMPOSSIBLE NOTE TYPE IN readDWI() %d\r\n", beats[i].type);
		}
	}

	fclose(fp);

	// count the maximum score that this chart is worth. it is needed while the chart is being played
	int maxScore = 0;
	for ( size_t i = 0; i < chart->size(); i++ )
	{
		if ( chart->at(i).type == TAP || chart->at(i).type == JUMP )
		{
			maxScore += 2;
		}
	}
	maxScore += holds->size()*2;
	return maxScore;
}