// Write year to screen
void ClockMaster::writeYear(DateTime time_now) {
  tft.stroke(255, 255, 255);
  tft.setTextSize(yearSize);
  tft.setCursor(yearYPos, yearXPos);
  tft.print(time_now.year());
}