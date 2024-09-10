//--------------------------------------------------------------
// main entry
int WINAPI WinMain( 
  HINSTANCE hInstance,            // Instance
  HINSTANCE hPrevInstance,        // Previous Instance
  LPSTR lpCmdLine,                // Command Line Parameters
  int nCmdShow)                   // Window Show State
{
#ifdef DEBUG_MEMORY
  mgDebugMemoryInit();
#endif

  mgDebugReset();         // reset trace file
  mgOSInitTimer();       // performance timer
  
  // initialize random numbers
  time_t seed;
  time(&seed);
  srand(12123123); // srand(seed & 0xFFFF);

  mgOSFindWD("docs");

  // handle utility error messages
  m_errorTable = new mgUtilErrorTable();

  try
  {
    initWindow();
    createWindow();
    createBitmap();
    createUI();

    // create the terrain
    m_flatWorld = new FlatWorld();
    m_flatWorld->resize(m_windowWidth, m_windowHeight);
    m_ui->setValue(m_flatWorld->m_playerX, m_flatWorld->m_playerY);

    // check for screen update every 25 ms
    SetTimer(m_window, 123, 25, NULL);

    while (true)
    {
      MSG msg;      

      // if there is no input pending
      if (!PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) 
      {
        // update any movement keys still down
        updateMovement();

        // if the ui needs an update
        if (m_surface != NULL && m_surface->isDamaged())
        {
          // redraw ui at damaged area
          mgRectangle bounds;
          m_surface->getDamage(bounds);
          m_ui->m_top->surfacePaint(bounds);

          // copy bits from surface into bitmap
          m_surface->repair(bounds);

          // tell windows to redraw the updated area
          RECT rect;
          rect.left = bounds.m_x;
          rect.right = rect.left + bounds.m_width;
          rect.top = bounds.m_y;
          rect.bottom = rect.top + bounds.m_height;
          InvalidateRect(m_window, &rect, false);
        }
      }

      GetMessage(&msg, NULL, 0, 0);     

      // end on quit
      if (msg.message == WM_QUIT)       
        break;

      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }

    // shutdown
    destroyUI();
    destroyBitmap();
    destroyWindow();
    termWindow();
  }
  catch (mgErrorMsg* e)
  {
    mgString msg;
    m_errorTable->msgText(msg, e);
    mgDebug("%s", (const char*) msg);

    MessageBox(m_window, msg, "Error", MB_OK | MB_ICONINFORMATION);
    return 0;
  }
  catch (mgException* e)
  {
    mgDebug("%s", (const char*) e->m_message);

    MessageBox(m_window, e->m_message, "Error", MB_OK | MB_ICONINFORMATION);
    return 0;
  }

  delete m_errorTable;
  m_errorTable = NULL;

#ifdef DEBUG_MEMORY
  // display all memory leaks
  mgDebugMemory();
#endif

  return 0;
}