void ez430_lcd_img_draw(struct ez430_lcd_img_t *img, uint8_t mem[15], uint8_t bmem[15])
{
  int i, j, k;
  int pixel;

  pixel = (img->x + img->y * machine.ui.width) * machine.ui.bpp;
  for (i = 0; i < img->h; i++) {
    int pii = pixel;
    for (j = 0; j < img->w; j++) {
      setpixel(pii, 0x00, 0x00, 0x00); // bkg
      for (k = 0; k < 12; k++) {
        if ((mem[k] & img->img[j][i][k]) != 0) {
          if ((bmem[k] & img->img[j][i][k]) != 0) {
            setpixel(pii, 0x00, 0xee, 0x00); // blink
            break;
          } else {
            setpixel(pii, 0xee, 0x00, 0x00); // on
            break;
          }
        } else if (img->img[j][i][k] > 0) {
          setpixel(pii, 0x30, 0x30, 0x30); // off
        }
      }
      pii += 3;
    }
    pixel += machine.ui.width * machine.ui.bpp;
  }
}