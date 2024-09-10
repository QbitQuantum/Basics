void testfillrects(uint16_t color1, uint16_t color2) {
    tft.fillScreen(ST7735_BLACK);
    for (int16_t x=tft.width()-1; x > 6; x-=6) {
        tft.fillRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color1);
        tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color2);
    }
}