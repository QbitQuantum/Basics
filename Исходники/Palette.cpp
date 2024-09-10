void PalEvidence(char* tpal,char* pal)
{
    const int SPEED = 4;
    int log = 1,i;
    int t;
    while(log) {
        t = CLOCK();
        while(CLOCK() < t + 1);
        log = 0;
        for(i = 0; i < 256; i++) {
            tpal[3*i + 0] += SPEED;
            tpal[3*i + 1] += SPEED;
            tpal[3*i + 2] += SPEED;
            if(tpal[3*i + 0] >= pal[3*i + 0]) tpal[3*i + 0] = pal[3*i + 0];
            else log = 1;
            if(tpal[3*i + 1] >= pal[3*i + 1]) tpal[3*i + 1] = pal[3*i + 1];
            else log = 1;
            if(tpal[3*i + 2] >= pal[3*i + 2]) tpal[3*i + 2] = pal[3*i + 2];
            else log = 1;
        }
        XGR_SetPal(tpal,0,255);
        XGR_Flush(0,0,XGR_MAXX,XGR_MAXY);
        xtClearMessageQueue();
    }
}