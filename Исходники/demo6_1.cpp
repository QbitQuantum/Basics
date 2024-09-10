int Game_Init(void *parms = NULL, int num_parms = 0)
{
// this is called once after the initial window is created and
// before the main event loop is entered, do all your initialization
// here

// create IDirectDraw interface 7.0 object and test for error
if (FAILED(DirectDrawCreateEx(NULL, (void **)&lpdd, IID_IDirectDraw7, NULL)))
   return(0);

// set cooperation to normal since this will be a windowed app
lpdd->SetCooperativeLevel(main_window_handle, DDSCL_NORMAL);

// return success or failure or your own return code here
return(1);

} // end Game_Init