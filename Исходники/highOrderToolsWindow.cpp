highOrderToolsWindow::highOrderToolsWindow(int deltaFontSize)
{
  getMeshInfoForHighOrder(GModel::current(), meshOrder, complete, CAD);
  FL_NORMAL_SIZE -= deltaFontSize;

  int width = 3 * IW + 4 * WB;
  int height = 24 * BH;

  win = new paletteWindow
    (width, height, CTX::instance()->nonModalWindows ? true : false, "High order tools");
  win->box(GMSH_WINDOW_BOX);

  int y = WB;
  int x = 2 * WB;

  box[0] = new Fl_Box(x, y, width - 4 * WB, BH);
  box[0]->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);

  y += BH;

  butt[1] = new Fl_Check_Button
    (x, y, width - 4 * WB, BH, "Only apply high order tools to visible entities");
  butt[1]->type(FL_TOGGLE_BUTTON);
  butt[1]->value(1);

  y += BH;

  butt[3] = new Fl_Check_Button
    (x, y, width - 4 * WB, BH, "Show detailed log messages");
  butt[3]->type(FL_TOGGLE_BUTTON);
  butt[3]->value(1);

  {
    y += BH / 2;
    Fl_Box* b = new Fl_Box(x, y + BH - WB, width - 4 * WB, 2);
    b->box(FL_ENGRAVED_FRAME);
    b->labeltype(FL_NO_LABEL);
  }

  {
    y += BH;
    Fl_Box *b = new Fl_Box
      (x - WB, y, width, BH, "1. Generation of high order vertices");
    b->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
  }

  y += BH;

  value[0] = new Fl_Value_Input
    (x, y, IW, BH, "Polynomial order");
  value[0]->minimum(1);
  value[0]->maximum(10);
  value[0]->step(1);
  value[0]->align(FL_ALIGN_RIGHT);
  value[0]->value(meshOrder);

  y += BH;

  butt[0] = new Fl_Check_Button
    (x, y, width - 4 * WB, BH, "Use incomplete elements");
  butt[0]->type(FL_TOGGLE_BUTTON);
  butt[0]->value(!complete);
  butt[0]->callback(change_completeness_cb);

  y += BH;

  butt[2] = new Fl_Check_Button
    (x, y, width - 4 * WB, BH, "Use CAD model to curve mesh");
  butt[2]->type(FL_TOGGLE_BUTTON);
  butt[2]->value(1);

  y += BH;

  push[0] = new Fl_Button
    (width - BB - 2 * WB, y, BB, BH, "Generate");
  push[0]->callback(highordertools_runp_cb);

  {
    y += BH / 2;
    Fl_Box* b = new Fl_Box(x, y + BH - WB, width - 4 * WB, 2);
    b->box(FL_ENGRAVED_FRAME);
    b->labeltype(FL_NO_LABEL);
  }

  {
    y += BH;
    Fl_Box *b = new Fl_Box
      (x - WB, y, width, BH, "2. Regularization of high order elements");
    b->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
  }

  y += BH;
  static Fl_Menu_Item menu_method[] = {
    {"Optimization", 0, 0, 0},
    {"Elastic Analogy", 0, 0, 0},
    {"Fast Curving", 0, 0, 0},
    {0}
  };
  choice[2] = new Fl_Choice
    (x, y, IW, BH, "Algorithm");
  choice[2]->align(FL_ALIGN_RIGHT);
  choice[2]->menu(menu_method);
  choice[2]->callback(chooseopti_cb);

  y += BH;
  value[1] = new Fl_Value_Input
    (x, y, IW/2.0, BH);
  value[1]->minimum(0);
  value[1]->maximum(1);
  value[1]->step(.01);
  value[1]->align(FL_ALIGN_RIGHT);
  value[1]->value(CTX::instance()->mesh.hoThresholdMin);

  value[8] = new Fl_Value_Input
    (x+IW/2.0,y, IW/2.0, BH, "Target Jacobian range");
  value[8]->minimum(1);
  value[8]->maximum(10);
  value[8]->step(.01);
  value[8]->align(FL_ALIGN_RIGHT);
  value[8]->value(CTX::instance()->mesh.hoThresholdMax);

  y += BH;
  value[2] = new Fl_Value_Input
    (x, y, IW, BH, "Number of layers");
  value[2]->minimum(1);
  value[2]->maximum(20);
  value[2]->step(1);
  value[2]->align(FL_ALIGN_RIGHT);
  value[2]->value(CTX::instance()->mesh.hoNLayers);

  y += BH;
  value[7] = new Fl_Value_Input
    (x, y, IW, BH, "Distance factor");
  value[7]->minimum(1);
  value[7]->maximum(20000);
  value[7]->step(1);
  value[7]->align(FL_ALIGN_RIGHT);
  value[7]->value(12);

  y += BH;
  static Fl_Menu_Item menu_objf[] = {
    {"Fixed", 0, 0, 0},
    {"Free", 0, 0, 0},
    {0}
  };
  choice[0] = new Fl_Choice
    (x, y, IW, BH, "Boundary vertices");
  choice[0]->menu(menu_objf);
  choice[0]->align(FL_ALIGN_RIGHT);

  y += BH;
  value[5] = new Fl_Value_Input
    (x, y, IW/2, BH);
  value[5]->align(FL_ALIGN_RIGHT);
  value[5]->value(1000.);
  value[6] = new Fl_Value_Input
    (x+IW/2,y, IW/2, BH, "W fixed / W free");
  value[6]->align(FL_ALIGN_RIGHT);
  value[6]->value(1.);

  y += BH;
  value[3] = new Fl_Value_Input
    (x, y, IW, BH, "Maximum number of iterations");
  value[3]->minimum(1);
  value[3]->maximum(10000);
  value[3]->step(10);
  value[3]->align(FL_ALIGN_RIGHT);
  value[3]->value(300);

  y += BH;
  value[4] = new Fl_Value_Input
    (x, y, IW, BH, "Max. number of optimization passes");
  value[4]->minimum(1);
  value[4]->maximum(100);
  value[4]->step(1);
  value[4]->align(FL_ALIGN_RIGHT);
  value[4]->value(50);

  static Fl_Menu_Item menu_strategy[] = {
    {"Connected blobs", 0, 0, 0},
    {"Adaptive one-by-one", 0, 0, 0},
    {0}
  };

  y += BH;
  choice[3] = new Fl_Choice
    (x, y, IW, BH, "Strategy");
  choice[3]->menu(menu_strategy);
  choice[3]->align(FL_ALIGN_RIGHT);
  choice[3]->callback(chooseopti_strategy);

  y += BH;
  value[9] = new Fl_Value_Input
    (x, y, IW, BH, "Max. number of blob adaptation iter.");
  value[9]->minimum(1);
  value[9]->maximum(100);
  value[9]->step(1);
  value[9]->align(FL_ALIGN_RIGHT);
  value[9]->value(2);
  value[9]->deactivate();

  y += BH;
  value[10] = new Fl_Value_Input
    (x, y, IW, BH, "Num. layer adaptation factor");
  value[10]->align(FL_ALIGN_RIGHT);
  value[10]->minimum(1);
  value[10]->maximum(100);
  value[10]->step(1);
  value[10]->value(2);
  value[10]->deactivate();

  y += BH;
  value[11] = new Fl_Value_Input
    (x, y, IW, BH, "Distance adaptation factor");
  value[11]->align(FL_ALIGN_RIGHT);
  value[11]->minimum(1.);
  value[11]->maximum(100.);
  value[11]->value(2.);
  value[11]->deactivate();

  y += 1.5*BH;
  push[1] = new Fl_Button
    (width - BB - 2 * WB, y, BB, BH, "Regularize");
  push[1]->callback(highordertools_runopti_cb);

  // win->resizable(o);
  win->position(CTX::instance()->hotPosition[0], CTX::instance()->hotPosition[1]);
  win->end();
  FL_NORMAL_SIZE += deltaFontSize;
}