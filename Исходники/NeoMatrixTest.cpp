  void timeExpired()
  {
    matrix.fillScreen(0);

    matrix.fillCircle(6, 6, 6, matrix.Color(190, 190, 190));
    matrix.setTextColor(colors[0]);
    matrix.setCursor(0, 1);
    matrix.print(F("158"));

    if (counter % 2 == 0)
    {
      matrix.fillScreen(0);
      matrix.fillCircle(6, 5, 5, matrix.Color(20, 20, 20));

      matrix.setTextColor(colors[2]);
      matrix.setCursor(0, 1);
      matrix.print(String(counter));
    }

    matrix.show();
    counter++;
  }