			//////////////////////////////////////
			// Handles WM_TIMER messages
			//////////////////////////////////////
void Main_Timer(HWND hwnd, UINT id)
{
if(Mstart == TRUE)
	{
	SaveLevels();

	SetCursor(LoadCursor(NULL, IDC_WAIT));
	for(int i = 0; i < MAXLEVEL; i++)
		{
		leveltemp[i] = (LPLEVELARRAY)malloc(sizeof(LEVELARRAY));
		}
	SetCursor(LoadCursor(NULL, IDC_ARROW));

	FILE *fp;
	char S2[MAXARRAY] = GAMEDIR;
	strcat(S2, LEVELSFILE);
	fp = fopen(S2, "r");
for(i = 0; i < CL; i++)
	{
	fread(&(leveltemp[i]->midi),			sizeof(MIDIFILE),			1, fp);
	fread(&(leveltemp[i]->waveNum),		sizeof(UINT),					1, fp);
	fread(&(leveltemp[i]->bitmapNum),	sizeof(UINT),					1, fp);
	fread(&(leveltemp[i]->spriteNum),	sizeof(UINT),					1, fp);
	fread(&(leveltemp[i]->zoneNum),		sizeof(UINT),					1, fp);
	fread(&(leveltemp[i]->lWaveA),		sizeof(UINT),					leveltemp[i]->waveNum, fp);
	fread(&(leveltemp[i]->lBitmapA),	sizeof(BITMAPARRAY),	leveltemp[i]->bitmapNum, fp);
	fread(&(leveltemp[i]->lSpriteA),	sizeof(SPRITEARRAY),	leveltemp[i]->spriteNum, fp);
	fread(&(leveltemp[i]->lZoneA),		sizeof(ZONEARRAY),		leveltemp[i]->zoneNum, fp);
	}
	fclose(fp);

	Mstart = FALSE;
	}

else if(mouseswitch)
	{
	int m = 10;
	int x = 10;
	RECT r;
	char S[MAXARRAY];
	HDC PaintDC = GetDC(hwnd);
	GetWindowRect(hwnd, &r);
	FillRect(PaintDC, &r, (HBRUSH)GetStockObject(BLACK_BRUSH));

	sprintf(S, "LevelNum = %u", n);
		TextOut(PaintDC, x, m, S, strlen(S));
		m += 30;

	sprintf(S, "level.midi.file = %s", leveltemp[n]->midi.file);
		TextOut(PaintDC, x, m, S, strlen(S));
		m += 20;
	sprintf(S, "level.midi.sec = %u", leveltemp[n]->midi.sec);
		TextOut(PaintDC, x, m, S, strlen(S));
		m += 30;

	sprintf(S, "level.waveNum = %u", leveltemp[n]->waveNum);
		TextOut(PaintDC, x, m, S, strlen(S));
		m += 20;
	sprintf(S, "level.bitmapNum = %u", leveltemp[n]->bitmapNum);
		TextOut(PaintDC, x, m, S, strlen(S));
		m += 20;
	sprintf(S, "level.spriteNum = %u", leveltemp[n]->spriteNum);
		TextOut(PaintDC, x, m, S, strlen(S));
		m += 20;
	sprintf(S, "level.zoneNum = %u", leveltemp[n]->zoneNum);
		TextOut(PaintDC, x, m, S, strlen(S));
		m += 30;
//////////////////////////////////////////////////////////////////
	sprintf(S, "WaveNum = %u", w);
		TextOut(PaintDC, x, m, S, strlen(S));
		m += 20;
	sprintf(S, "level.lWaveA = %d", leveltemp[n]->lWaveA[w]);
		TextOut(PaintDC, x, m, S, strlen(S));
		m += 30;
//////////////////////////////////////////////////////////////////
	x = 400;
	m = 10;
	sprintf(S, "BitmapNum = %u", b);
		TextOut(PaintDC, x, m, S, strlen(S));
		m += 20;
	sprintf(S, "level.lBitmapA.zNum = %u", leveltemp[n]->lBitmapA[b].zNum);
		TextOut(PaintDC, x, m, S, strlen(S));
		m += 20;
if(leveltemp[n]->lZoneA[leveltemp[n]->lBitmapA[b].zNum].x1 < 65500)
	{
	sprintf(S, "level.lBitmapA.zoneName = %s", leveltemp[n]->lZoneA[leveltemp[n]->lBitmapA[b].zNum].zoneName);
		TextOut(PaintDC, x, m, S, strlen(S));
		m += 20;
	}
	sprintf(S, "level.lBitmapA.x1 = %u", leveltemp[n]->lZoneA[leveltemp[n]->lBitmapA[b].zNum].x1);
		TextOut(PaintDC, x, m, S, strlen(S));
		m += 20;
	sprintf(S, "level.lBitmapA.y1 = %u", leveltemp[n]->lZoneA[leveltemp[n]->lBitmapA[b].zNum].y1);
		TextOut(PaintDC, x, m, S, strlen(S));
		m += 20;
	sprintf(S, "level.lBitmapA.x2 = %u", leveltemp[n]->lZoneA[leveltemp[n]->lBitmapA[b].zNum].x2);
		TextOut(PaintDC, x, m, S, strlen(S));
		m += 20;
	sprintf(S, "level.lBitmapA.y2 = %u", leveltemp[n]->lZoneA[leveltemp[n]->lBitmapA[b].zNum].y2);
		TextOut(PaintDC, x, m, S, strlen(S));
		m += 20;
	sprintf(S, "level.lBitmapA.w = %u", leveltemp[n]->lZoneA[leveltemp[n]->lBitmapA[b].zNum].w);
		TextOut(PaintDC, x, m, S, strlen(S));
		m += 20;
	sprintf(S, "level.lBitmapA.h = %u", leveltemp[n]->lZoneA[leveltemp[n]->lBitmapA[b].zNum].h);
		TextOut(PaintDC, x, m, S, strlen(S));
		m += 30;
//////////////////////////////////////////////////////////////////
	sprintf(S, "SpriteNum = %u", l);
		TextOut(PaintDC, x, m, S, strlen(S));
		m += 20;
	sprintf(S, "level.lSpriteA.zNum = %u", leveltemp[n]->lSpriteA[l].zNum);
		TextOut(PaintDC, x, m, S, strlen(S));
		m += 20;
if(leveltemp[n]->lZoneA[leveltemp[n]->lSpriteA[l].zNum].x1 < 65500)
	{
	sprintf(S, "level.lSpriteA.zoneName = %s", leveltemp[n]->lZoneA[leveltemp[n]->lSpriteA[l].zNum].zoneName);
		TextOut(PaintDC, x, m, S, strlen(S));
		m += 20;
	}
sprintf(S, "level.lSpriteA.x1 = %u", leveltemp[n]->lZoneA[leveltemp[n]->lSpriteA[l].zNum].x1);
		TextOut(PaintDC, x, m, S, strlen(S));
		m += 20;
	sprintf(S, "level.lSpriteA.y1 = %u", leveltemp[n]->lZoneA[leveltemp[n]->lSpriteA[l].zNum].y1);
		TextOut(PaintDC, x, m, S, strlen(S));
		m += 20;
	sprintf(S, "level.lSpriteA.x2 = %u", leveltemp[n]->lZoneA[leveltemp[n]->lSpriteA[l].zNum].x2);
		TextOut(PaintDC, x, m, S, strlen(S));
		m += 20;
	sprintf(S, "level.lSpriteA.y2 = %u", leveltemp[n]->lZoneA[leveltemp[n]->lSpriteA[l].zNum].y2);
		TextOut(PaintDC, x, m, S, strlen(S));
		m += 20;
	sprintf(S, "level.lSpriteA.w = %u", leveltemp[n]->lZoneA[leveltemp[n]->lSpriteA[l].zNum].w);
		TextOut(PaintDC, x, m, S, strlen(S));
		m += 20;
	sprintf(S, "level.lSpriteA.h = %u", leveltemp[n]->lZoneA[leveltemp[n]->lSpriteA[l].zNum].h);
		TextOut(PaintDC, x, m, S, strlen(S));
		m += 20;
	sprintf(S, "level.lSpriteA.zOrder = %u", leveltemp[n]->lSpriteA[l].zOrder);
		TextOut(PaintDC, x, m, S, strlen(S));
		m += 20;
	sprintf(S, "level.lSpriteA.cel = %u", leveltemp[n]->lSpriteA[l].cel);
		TextOut(PaintDC, x, m, S, strlen(S));
		m += 20;
	sprintf(S, "level.lSpriteA.xDelta = %u", leveltemp[n]->lSpriteA[l].xDelta);
		TextOut(PaintDC, x, m, S, strlen(S));
		m += 20;
	sprintf(S, "level.lSpriteA.yDelta = %u", leveltemp[n]->lSpriteA[l].yDelta);
		TextOut(PaintDC, x, m, S, strlen(S));
		m += 20;
	sprintf(S, "level.lSpriteA.xHotspot = %u", leveltemp[n]->lSpriteA[l].xHotspot);
		TextOut(PaintDC, x, m, S, strlen(S));
		m += 20;
	sprintf(S, "level.lSpriteA.yHotspot = %u", leveltemp[n]->lSpriteA[l].yHotspot);
		TextOut(PaintDC, x, m, S, strlen(S));
		m += 30;
//////////////////////////////////////////////////////////////////
	sprintf(S, "ZoneNum = %u", k);
		TextOut(PaintDC, x, m, S, strlen(S));
		m += 20;
if(leveltemp[n]->lZoneA[k].x1 < 65500)
	{
	sprintf(S, "level.lZoneA.zoneName = %s", leveltemp[n]->lZoneA[k].zoneName);
		TextOut(PaintDC, x, m, S, strlen(S));
		m += 20;
	}
	sprintf(S, "level.lZoneA.x1 = %u", leveltemp[n]->lZoneA[k].x1);
		TextOut(PaintDC, x, m, S, strlen(S));
		m += 20;
	sprintf(S, "level.lZoneA.y1 = %u", leveltemp[n]->lZoneA[k].y1);
		TextOut(PaintDC, x, m, S, strlen(S));
		m += 20;
	sprintf(S, "level.lZoneA.x2 = %u", leveltemp[n]->lZoneA[k].x2);
		TextOut(PaintDC, x, m, S, strlen(S));
		m += 20;
	sprintf(S, "level.lZoneA.y2 = %u", leveltemp[n]->lZoneA[k].y2);
		TextOut(PaintDC, x, m, S, strlen(S));
		m += 20;
	sprintf(S, "level.lZoneA.w = %u", leveltemp[n]->lZoneA[k].w);
		TextOut(PaintDC, x, m, S, strlen(S));
		m += 20;
	sprintf(S, "level.lZoneA.h = %u", leveltemp[n]->lZoneA[k].h);
		TextOut(PaintDC, x, m, S, strlen(S));
		m += 30;

	ReleaseDC(hwnd, PaintDC);
	mouseswitch = FALSE;
	}
SetTimer(hwnd, IDT_MAIN, 10, NULL);
}