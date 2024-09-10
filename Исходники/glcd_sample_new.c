void loop(){ // run over and over again
int i;
  startMillis = millis();
  while( millis() - startMillis < 1000){ // loop for one second
    DrawRect(0, 0, 64, 61, BLACK); // rectangle in left side of screen
    DrawRoundRect(68, 0, 58, 61, 5, BLACK);  // rounded rectangle around text area   
    for(i=0; i < 62; i += 4)
      DrawLine(1,1,63,i, BLACK);  // draw lines from upper left down right side of rectangle  
    DrawCircle(32,31,30,BLACK);   // draw circle centered in the left side of screen  
    FillRect(92,40,16,16, WHITE); // clear previous spinner position  
    CursorTo(5,5);               // locate curser for printing text
    PrintNumber(++iter);         // print current iteration at the current cursor position 
  } 
//
  ClearScreenX();               // clear the screen  
  CursorTo(13,2);              // positon cursor  
  Puts("FPS= ");               // print a text string  
  PrintNumber(iter);           // print a number 
  iter=0;
 }