void Out::scrollOutput()
{
  // shift output lines up one
  for (int i = 0; i < outputLine - 1; i++) {
    for (int j = 0; j < MAX_COLS; j++) outputLines[i][j] = outputLines[i+1][j];
  }
  outputLine--;
  outputY--;

  for (int i = 0; i < outputLine; i++) {
    if (strlen(outputLines[i]) > 0) mvaddstr(i, 0, outputLines[i]);
    for (int j = strlen(outputLines[i]); j < COLS; j++) {
      // blank the rest
      mvaddch(i, j, ' ');
    }
  }
  for (int i = 0; i < COLS; i++) mvaddch(outputLine, i, ' ');
  refresh();
}