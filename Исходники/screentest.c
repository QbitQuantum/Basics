int main(int argc, char **argv)
{
    struct myargs args = {NULL};
    struct RDArgs *rda;

    if ((IntuitionBase = (struct IntuitionBase *) OpenLibrary("intuition.library", 0))) 
    {
	if ((GfxBase = (struct GfxBase *)OpenLibrary("graphics.library", 0))) 
        {
	    if ((DOSBase = (struct DosLibrary *) OpenLibrary("dos.library",0)))
	    {
		rda = ReadArgs("LEFT/K/N,TOP/K/N,WIDTH/N,HEIGHT/N,DEPTH/K/N,MODEID/K,OVERSCAN/K/N,SCROLL/K/N,DRAG/K/N,LIKEWB/K/N", (IPTR *)&args, NULL);
		if (rda) {
		    struct Screen *screen;
		    struct Window *w1;
		    ULONG oserr = 0;
		    struct TagItem tags[] = {
			{SA_Width,     640			         },
			{SA_Height,    480			         },
			{SA_Depth,     4			         },
			{TAG_IGNORE,   0			         },
			{TAG_IGNORE,   0			         },
			{TAG_IGNORE,   0			         },
			{TAG_IGNORE,   0			         },
			{TAG_IGNORE,   0			         },
			{TAG_IGNORE,   0			         },
			{TAG_IGNORE,   0			         },
			{SA_Title,     (IPTR)"Screen opening and movement test"},
			{SA_ErrorCode, (IPTR)&oserr			         },
			{TAG_DONE,     0				 }
		    };

		    if (args.width)
		        tags[0].ti_Data = *args.width;
		    if (args.height)
		        tags[1].ti_Data = *args.height;
		    if (args.depth)
		        tags[2].ti_Data = *args.depth;
		    printf("Opening screen, size: %lux%lu, depth: %lu\n", tags[0].ti_Data, tags[1].ti_Data, tags[3].ti_Data);
		    if (args.mode) {
		        tags[3].ti_Tag  = SA_DisplayID;
			tags[3].ti_Data = strtoul(args.mode, NULL, 16);
			printf("ModeID: 0x%08lX\n", tags[3].ti_Data);
		    }
		    if (args.scroll) {
			tags[4].ti_Tag = SA_AutoScroll;
			tags[4].ti_Data = *args.scroll;
			printf("SA_AutoScroll: %ld\n", tags[4].ti_Data);
		    }
		    if (args.drag) {
			tags[5].ti_Tag = SA_Draggable;
			tags[5].ti_Data = *args.drag;
			printf("SA_Draggable: %ld\n", tags[5].ti_Data);
		    }
		    if (args.likewb) {
			tags[6].ti_Tag = SA_LikeWorkbench;
			tags[6].ti_Data = *args.likewb;
			printf("SA_LikeWorkbench: %ld\n", tags[6].ti_Data);
		    }
		    if (args.oscan) {
			tags[7].ti_Tag = SA_Overscan;
			tags[7].ti_Data = *args.oscan;
			printf("SA_Overscan: %ld\n", tags[7].ti_Data);
		    }
		    if (args.left) {
			tags[8].ti_Tag = SA_Left;
			tags[8].ti_Data = *args.left;
			printf("SA_Left: %ld\n", tags[8].ti_Data);
		    }
		    if (args.top) {
			tags[9].ti_Tag = SA_Top;
			tags[9].ti_Data = *args.top;
			printf("SA_Top: %ld\n", tags[9].ti_Data);
		    }

		    screen = OpenScreenTagList(NULL, tags);
                    if (screen) {
			w1 = openwindow(screen, "Screen data",  W1_LEFT, W1_TOP, W1_WIDTH, W1_HEIGHT);
			if (w1) {
			    WORD x = w1->BorderLeft;
		            WORD y = w1->BorderTop;
			    struct BitMap *bitmap = screen->RastPort.BitMap;

			    y = drawtext(w1, x, y, "Requested size: %lux%lu", tags[0].ti_Data, tags[1].ti_Data);
			    y = drawtext(w1, x, y, "Requested depth: %lu", tags[2].ti_Data);
			    if (args.mode)
			        y = drawtext(w1, x, y, "Requested ModeID: 0x%08lX", tags[3].ti_Data);
			    y = drawtext(w1, x, y, "Actual size: %ux%u", screen->Width, screen->Height);
			    y = drawtext(w1, x, y, "Actual ModeID: 0x%08X", screen->ViewPort.ColorMap->VPModeID);
			    y = drawtext(w1, x, y, "Flags: 0x%04lX", screen->Flags);
			    y = drawtext(w1, x, y, "BitMap size: %ux%u", GetBitMapAttr(bitmap, BMA_WIDTH), GetBitMapAttr(bitmap, BMA_HEIGHT));
			    y = drawtext(w1, x, y, "BitMap depth: %u", GetBitMapAttr(bitmap, BMA_DEPTH));
			    handleevents(w1, screen, x, y);
			    CloseWindow(w1);
			}
		        CloseScreen(screen);
		    } else
		        printf("Failed to open screen, error: %d\n", (int)oserr);
		    FreeArgs(rda);
	        } else
		    printf("Error parsing arguments\n");
                CloseLibrary((struct Library *)DOSBase);
	    }
	    CloseLibrary((struct Library *)GfxBase);
	}
	CloseLibrary((struct Library *) IntuitionBase);
    }
    return 0;
} /* main */