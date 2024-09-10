void drawMainMenu(int pos)
{

	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = false;
	cursor.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
   int current=pos; // store the value of the currently highlighted selection

   gotoxy(25,4); // position on screen
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
   cprintf("        BU MicroSight        "); // name of menu item
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

   if (current == 1)
   {

	 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
    // turn text color to black
      // turn the text background color grey

     gotoxy(25,7); // position on screen
     cprintf("-> Alter System Variables    "); // name of menu item

	 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    // textcolor(7);  // turn the text colour back to normal
    // textbackground(0);  // turn the text BG to black
   }
   else
   {
     gotoxy(25, 7);
     cprintf("   Alter System Variables    ");
   }

   if(current == 2)
   {
     //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
    // textbackground(7);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);

     gotoxy(25, 9);
     cprintf("-> Edit Trial Details        ");

	 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
     //textcolor(7);
     //textbackground(0);

   }
   else
   {
     gotoxy(25, 9);
     cprintf("   Edit Trial Details        ");
   }

   if(current == 3)
   {

	 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
  
     gotoxy(25, 11);
     cprintf("   Set Segmentation Method   ");

	 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		
   }
   else
   {

     gotoxy(25, 11);
     cprintf("   Set Segmentation Method   ");

   }

   if (current == 4)
   {
      
	 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);

     gotoxy(25, 13);
     cprintf("   Begin Trial Now           ");

	 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

   }
   else
   {

     gotoxy(25, 13);
     cprintf("   Begin Trial Now           ");

   }


   if(current == 5)
   {
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);

     gotoxy(25, 19);
     cprintf("   Exit                      ");

      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

   }
   else
   {

     gotoxy(25, 19);
     cprintf("   Exit                      ");

   }

}