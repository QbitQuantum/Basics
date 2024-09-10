/**
 * Interactively adjust the backlight on a device
 * 
 * @param  cols    The number of columns on the terminal
 * @param  device  The device on which to adjust backlight
 */
static void adjust(int cols, const char* device)
{
  int min, max, cur, step, init, i, d;
  size_t lendir;
  char* dir = alloca(PATH_MAX * sizeof(char));
  char* buf = alloca(256 * sizeof(char));
  
  *dir = 0;
  dir = strcat(dir, BACKLIGHT_DIR "/");
  dir = strcat(dir, device);
  dir = strcat(dir, "/");
  lendir = strlen(dir);
  
  /* Get brightness parameters */
  min = 0;
  if (readfile(buf, strcat(dir, "max_brightness")))
    return;
  max = atoi(unnl(buf));
  *(dir + lendir) = 0;
  if (readfile(buf, strcat(dir, "brightness")))
    return;
  cur = atoi(unnl(buf));
  
  if (max <= min)
    return; /* what the buck */
  
  step = (max - min) / 200 ?: 1;
  init = cur;
  
  P("\n\n\n\n\n");
  bars(min, max, init, cur, cols);
  
  while ((d = getchar()) != -1)
    switch (d)
      {
      case 'q':
      case '\n':
      case 4:
	P("");
	return;
	
      case 'A':
      case 'C':
	cur += step << 1;
	/* fall through */
      case 'B':
      case 'D':
	cur -= step;
	if (cur < min)  cur = min;
	if (cur > max)  cur = max;
	if (writefile(buf, cur, dir))
	  return;
	bars(min, max, init, cur, cols);
      }
}