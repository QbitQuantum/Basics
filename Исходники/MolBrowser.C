MolBrowser::MolBrowser(VMDApp *vmdapp, MainFltkMenu *mm,
                       int x, int y, int xw, int yw)
: Fl_Multi_Browser(x, y, xw, yw), app(vmdapp) {
  mainmenu = mm;
  dragpending = 0;  
  align(FL_ALIGN_TOP_LEFT);
  column_widths(widths);
  color(VMDMENU_BROWSER_BG);
  selection_color(VMDMENU_BROWSER_SEL);

  VMDFLTKTOOLTIP(this, "Select molecule, toggle top/active/drawn/fixed, \nload/save coordinates or trajectory frames, \ndouble-click to rename molecule")

  new Fl_Box(x,   y-20,30,20,"ID");
  new Fl_Box(x+32,y-20,18,20,"T");
  new Fl_Box(x+50,y-20,18,20,"A");
  new Fl_Box(x+68,y-20,18,20,"D");
  new Fl_Box(x+86,y-20,18,20,"F");
  Fl_Box *b = new Fl_Box(x+102,y-20,220,20,"Molecule");
  b->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
  b = new Fl_Box(x+262,y-20,80,20,"Atoms");
  b->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
  b = new Fl_Box(x+342,y-20,60,20,"Frames");
  b->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
  b = new Fl_Box(x+412,y-20,30,20,"Vol");
  b->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
  end();
}