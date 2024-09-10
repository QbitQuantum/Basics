/*
 * Writes out at most 20 restaurants on the screen,
 * starting at the index passed in
 */
void writeOutRestaurants(uint16_t startingIndex, RestDist *distances, uint16_t length) {
  tft.fillScreen(0);
  tft.setCursor(0, 0);
  tft.setTextColor(0xFFFF);
  tft.setTextWrap(false);
  
  for (int i = startingIndex; i < 20 + startingIndex; i++) {
    if(i >= length) {
      break;
    }
    Restaurant r;
    getRestaurant(distances[i].index, &r, &card);
    tft.print(i + 1);
    tft.print(". ");
    tft.print(r.name);
    tft.print("\n");
  }
  tft.print("\n");
}