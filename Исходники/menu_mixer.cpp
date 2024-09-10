 void _lcd_draw_mix(const uint8_t y) {
   char tmp[21];
   sprintf_P(tmp, PSTR(MSG_MIX ":    %3d%% %3d%%"), int(mixer.mix[0]), int(mixer.mix[1]));
   SETCURSOR(2, y);
   LCDPRINT(tmp);
 }