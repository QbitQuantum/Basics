int DD_Init(int width, int height, int bpp)
{
// this function initializes directdraw
int index; // looping variable

// create object and test for error
if (DirectDrawCreateEx(NULL, (void **)&lpdd, IID_IDirectDraw7, NULL)!=DD_OK)
   return(0);

// set cooperation level to windowed mode normal
if (lpdd->SetCooperativeLevel(main_window_handle,
           DDSCL_ALLOWMODEX | DDSCL_FULLSCREEN | 
           DDSCL_EXCLUSIVE | DDSCL_ALLOWREBOOT)!=DD_OK)
    return(0);

// set the display mode
if (lpdd->SetDisplayMode(width,height,bpp,0,0)!=DD_OK)
   return(0);

// set globals
screen_height = height;
screen_width  = width;
screen_bpp    = bpp;

// Create the primary surface
memset(&ddsd,0,sizeof(ddsd));
ddsd.dwSize = sizeof(ddsd);
ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;

// we need to let dd know that we want a complex 
// flippable surface structure, set flags for that
ddsd.ddsCaps.dwCaps = 
  DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;

// set the backbuffer count to 1
ddsd.dwBackBufferCount = 1;

// create the primary surface
lpdd->CreateSurface(&ddsd,&lpddsprimary,NULL);

// query for the backbuffer i.e the secondary surface
ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
lpddsprimary->GetAttachedSurface(&ddscaps,&lpddsback);

// create and attach palette

// create palette data
// clear all entries defensive programming
memset(palette,0,256*sizeof(PALETTEENTRY));

// create a R,G,B,GR gradient palette
for (index=0; index < 256; index++)
    {
    // set each entry
    if (index < 64) 
        palette[index].peRed = index*4; 
    else           // shades of green
    if (index >= 64 && index < 128) 
        palette[index].peGreen = (index-64)*4;
    else           // shades of blue
    if (index >= 128 && index < 192) 
       palette[index].peBlue = (index-128)*4;
    else           // shades of grey
    if (index >= 192 && index < 256) 
        palette[index].peRed = palette[index].peGreen = 
        palette[index].peBlue = (index-192)*4;
    
    // set flags
    palette[index].peFlags = PC_NOCOLLAPSE;
    } // end for index

// now create the palette object
if (lpdd->CreatePalette(DDPCAPS_8BIT | DDPCAPS_INITIALIZE | DDPCAPS_ALLOW256,
                         palette,&lpddpal,NULL)!=DD_OK)
   return(0);

// attach the palette to the primary
if (lpddsprimary->SetPalette(lpddpal)!=DD_OK)
   return(0);

// clear out both primary and secondary surfaces
DD_Fill_Surface(lpddsprimary,0);
DD_Fill_Surface(lpddsback,0);

// attach a clipper to the screen
RECT screen_rect = {0,0,screen_width,screen_height};
lpddclipper = DD_Attach_Clipper(lpddsback,1,&screen_rect);

// return success
return(1);
} // end DD_Init