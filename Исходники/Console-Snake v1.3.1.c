int main (int argc, char *argv[]) 
{
 //Get a console handle
 HWND ConsoleWindow = GetConsoleWindow();
 
 //Get a STD handle
 HWND StdHandle = GetStdHandle (STD_OUTPUT_HANDLE);

 //Set cursor invisible
 CONSOLE_CURSOR_INFO CURSOR;
 CURSOR.dwSize = 1;
 CURSOR.bVisible = FALSE;
 SetConsoleCursorInfo (StdHandle, &CURSOR);
 
 //Get Current Font
 for (;;)
 {
  CONSOLE_FONT_INFO GETFONT;
  GetCurrentConsoleFont (StdHandle, FALSE, &GETFONT);
  COORD Fontsize = GetConsoleFontSize (StdHandle, GETFONT.nFont);
  SHORT Font_X = Fontsize.X;
  SHORT Font_Y = Fontsize.Y;
  if (Font_X != 8 || Font_Y != 12)
  {
   system ("chcp 437 > NUL");
   MessageBox (ConsoleWindow, "Please change Console Font to Raster Font  ( 8 x 12 ).", "Notice", MB_TOPMOST | MB_OK | MB_ICONINFORMATION);
   Envir_Error ();
   printf ("\rPress any key to continue...");
   system ("pause>nul");
  }
  else
   break;
 }
 
 //Change Settings
 //SetWindowLong (ConsoleWindow, GWL_STYLE, WS_THICKFRAME);
 //SetWindowLong (ConsoleWindow, GWL_STYLE, WS_CAPTION);
 //SetWindowPos  (ConsoleWindow, HWND_TOPMOST, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_SHOWWINDOW);
 SetWindowPos  (ConsoleWindow, HWND_TOP, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_SHOWWINDOW);

 //Get a handle to device context
 HDC DeviceContext = GetDC (ConsoleWindow);
 
 //Color
 COLORREF Color_White = RGB (255,255,255);
 COLORREF Color_Black = RGB ( 0 , 0 , 0 );
 
 //Title and Resize
 system ("mode con cols=75 lines=50");
 system ("title Console Snake     [ Developer: KVD 2013 ]");
 system ("color 0A");
 
 //Multi-Thread
 pthread_t Key_Stroke_Func;
 pthread_create (&Key_Stroke_Func, NULL, (void*)Get_Key_Stroke, NULL);
 
 //Initialization
 Initialize:;
 Initialization (DeviceContext, argv[1]);
 
 //Main
 for (;;)
 {
  //Terminate / PlayAgain
  if (Flag_Terminate == True)
  {
   return 0;
  }
  else if (Flag_PlayAgain == True)
  {
   Flag_PlayAgain = False;
   Clear_Screen (DeviceContext);
   goto Initialize;
  }
  //Draw
  if (Move.Condition == UnRead)
  {
   Move.Condition = Read;
   Change_Str (DeviceContext, ConsoleWindow);
   Draw_Square (Draw.X, Draw.Y, Draw.Direction, Color_White, Erase.X, Erase.Y, Erase.Direction, Color_Black, User_Def_Delay, DeviceContext);
  }
  else
  {
   Predict_Func (Draw.Direction);
   Change_Str (DeviceContext, ConsoleWindow);
   Draw_Square (Draw.X, Draw.Y, Draw.Direction, Color_White, Erase.X, Erase.Y, Erase.Direction, Color_Black, User_Def_Delay, DeviceContext);
  }
  //End
  if (Is_Snake (Draw.X, Draw.Y) == True || Is_Block (Draw.X, Draw.Y) == True)
  {
   MessageBox (ConsoleWindow, "GAME OVER", "Notice", MB_TOPMOST | MB_OK | MB_ICONSTOP);
   Clear_String ();
   Clear_Screen (DeviceContext);
   goto Initialize;
  }
 }
 
 //End
 system ("pause>nul");
 return 0;
}