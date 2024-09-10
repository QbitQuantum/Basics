void MatrixCbsTest(void)
{
  Ihandle *dlg, *bt;

  IupMatrixExOpen();
 
  IupSetFunction("removeline", (Icallback)removeline);
  IupSetFunction("addline", (Icallback)addline);
  IupSetFunction("removecol", (Icallback)removecol);
  IupSetFunction("addcol", (Icallback)addcol);
  IupSetFunction("redraw", (Icallback)redraw);

  createmenu();

  bt = IupButton("Button", NULL);
  IupSetCallback(bt, "ACTION", bt_cb);
  IupSetAttribute(bt, "CANFOCUS", "NO");

  dlg = IupDialog(
//          IupZbox(
          IupTabs(
            IupSetAttributes(
              IupVbox((create_mat(1)), bt, IupText(""), IupLabel("Label Text"), IupFrame(IupVal("HORIZONTAL")), 
                NULL), "MARGIN=10x10, GAP=10, TABTITLE=Test1"),
            IupSetAttributes(
              IupVbox(IupFrame(create_mat(2)), IupText(""), IupLabel("Label Text"), IupVal("HORIZONTAL"), 
//                NULL), "BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=10, TABTITLE=Test2,FONT=HELVETICA_ITALIC_14"), 
//                NULL), "FONT=HELVETICA_NORMAL_12, BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=10, TABTITLE=Test2"), 
                NULL), "BGCOLOR=\"0 255 255\", MARGIN=10x10, GAP=10, TABTITLE=Test2"), 
            NULL)); 
  IupSetAttribute(dlg,"TITLE", "IupMatrix");
  IupSetAttribute(dlg,"MENU", "mymenu");
  IupSetAttributeHandle(dlg,"DEFAULTENTER", bt);
//  IupSetAttribute(dlg,"BGCOLOR", "255 0 255");

  //IupSetAttribute(dlg,"COMPOSITED", "YES");
  //IupSetAttribute(dlg,"OPACITY", "192");

  IupShowXY(dlg,IUP_CENTER,IUP_CENTER);
}