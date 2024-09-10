void board_menu_draw(board_t* b)
{
  setTextColor(0, 0xff);
  setIntFont(&Font_7x8);

  const int lineh = getFontHeight();

  lcdSetCrsr(0, 0);
  lcdPrintln("0xb number game");
  lcdPrintln("Push < > ^ v");
  lcdPrintln("Add same blocks");
  lcdPrint("Try to reach '");
  setTextColor(colors[N_COLORS-1].bg, colors[N_COLORS-1].fg);
  lcdPrint("b");
  setTextColor(0, 0xff);
  lcdPrintln("'!");
  lcdNl();

  for (uint i = 0; i < menu_N; i ++) {
    if (i == b->menu_item)
      lcdPrint(">> ");
    else
      lcdPrint("   ");
    lcdPrint(menu_str[i]);

    switch (i) {
      case 3:
        // width
        lcdPrint(" = ");
        lcdPrint(IntToStr(b->w, 2, 0));
        break;
      case 4:
        // height
        lcdPrint(" = ");
        lcdPrint(IntToStr(b->h, 2, 0));
      default:
        break;
    }
    lcdNl();
  }

  if (b->menu_item == 2) {
    lcdPrintln(font_list[b->font]);
    if (b->font == FONT_NONE) {
      uint w = RESX / N_COLORS;
      for (uint8_t i = 0; i < N_COLORS; i++) {
        const color_t* col = colors + i;
        setTextColor(col->bg, col->fg);
        DoRect(i*w, 120, w, 10);
      }
    }
    else {
      setExtFont(font_list[b->font]);
      lcdPrint("789ab");
    }
  }
}