    layer_colorbase[2] = 0x80;
    layer_colorbase[3] = 0xc0;
}

/* useful function to sort the three tile layers by priority order */
static void sortlayers(int *layer,int *pri)
{
#define SWAP(a,b) \
	if (pri[a] < pri[b]) \
	{ \
		int t; \
		t = pri[a]; pri[a] = pri[b]; pri[b] = t; \
		t = layer[a]; layer[a] = layer[b]; layer[b] = t; \
	}

    SWAP(0,1)
    SWAP(0,2)
    SWAP(0,3)
    SWAP(1,2)
    SWAP(1,3)
    SWAP(2,3)
}

VIDEO_UPDATE(bishi)
{
    int layers[4], i;/*, old;*/
    /*  int bg_colorbase, new_colorbase, plane, dirty; */
    static const int pris[4] = { K55_PRIINP_0, K55_PRIINP_3, K55_PRIINP_6, K55_PRIINP_7 };
    static const int enables[4] = { K55_INP_VRAM_A, K55_INP_VRAM_B, K55_INP_VRAM_C, K55_INP_VRAM_D };

    K054338_update_all_shadows(screen->machine);