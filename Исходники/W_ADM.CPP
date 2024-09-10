extern "C" LONG ALMCALLBACK WndAdminProc(
  OBJECTID                oiWindow,
  AObjMessage*            theSystem)
  {
  WINDOW*                 wnd;
  LONG                    rVal = A_NOTHANDLED;

  switch(theSystem->message1)
    {
    case AOBJ_AWAKENED:
      #ifdef AW_I_DEBUG
      g_nLayoutUseCount++;
      if (!g_hinstLayout)
        {
        I_ASSERT(g_nLayoutUseCount==1);
        g_hinstLayout = LoadLibrary("ALM_WLAY.DLL");
        ADBG_PRINT_I("Preloading Layout Editor");
        }
      #endif
      rVal = A_OK;
      break;

    case AOBJ_CREATED:
      #ifdef AW_I_DEBUG
      g_nLayoutUseCount++;
      if (!g_hinstLayout)
        {
        I_ASSERT(g_nLayoutUseCount==1);
        g_hinstLayout = LoadLibrary("ALM_WLAY.DLL");
        ADBG_PRINT_I("Preloading Layout Editor");
        }
      #endif

      wnd = new(oiWindow) WINDOW(oiWindow);  //The locks the data
      delete wnd;  //Just unlocks the data -- DOES NOT DELETE THE DATAS!!!
      rVal = A_OK;
      break;

    case AOBJ_DESTROYED:
    case AOBJ_ASLEEP:
      #ifdef AW_I_DEBUG
      g_nLayoutUseCount--;
      if(g_nLayoutUseCount==0)
        {
        FreeLibrary(g_hinstLayout);
        g_hinstLayout = NULL;
        g_lpfnEditWnd = NULL;
        g_lpfnItemFromUID = NULL;
        ADBG_PRINT_I("Unloading Layout Editor");
        }
      #endif
      rVal = A_CONTINUE;
      break;

    case AOBJ_ASSIGNOBJECT:
      //Assignment of a window object is not yet defined
      break;

    case AOBJ_PREWRITE:
      if (theSystem->message4 != /*AOBJ_PROJECTSAVE*/2)
        {
        wnd = LockWindowData(oiWindow);
        I_VERIFY_POINTER(wnd, break);
        if(wnd->PutItemsIntoDatas())
          rVal = A_CONTINUE;
        else
          rVal = A_NOTHANDLED;
        UnlockWindowData(oiWindow);
        }
      else