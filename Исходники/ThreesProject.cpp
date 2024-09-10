void displayGameOver() {
    tft.fillScreen(0x0000);    // clear the screen with black
    tft.setCursor(0,0);        // set the cursor, indicates where to display
    tft.setTextWrap(false);    // no wrap
    tft.setTextSize(3);
    tft.print("\n GAME     \n\n");
    tft.print(" OVER\n\n");
    tft.setTextSize(1);
    tft.print("     SCORE: ");
    tft.print(score);
    //~ tft.print("\n TOP 5 OF THE SCORE LIST ");
    // TO_DO: print out the score list, which needs to be saved in SD cardc
   
}