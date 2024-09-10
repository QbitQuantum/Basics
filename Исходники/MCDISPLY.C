void initcursor(void)
/* Initializes the different cursor types */
{
 struct text_info ti;

 gettextinfo(&ti);
 oldcursor = getcursor();
 if (ti.currmode == MONO)
 {
  shortcursor = 0x0A0C;
  tallcursor = 0x090C;
 }
 else
 {
  shortcursor = 0x0607;
  tallcursor = 0x0507;
 }
} /* initcursor */