Fl_Window* make_codingstyle_window() {
  Fl_Window* w;
   {Fl_Window* o = new Fl_Window(310, 255);
    w = o;
    o->shortcut(0xff1b);
     {Fl_Tabs* o = new Fl_Tabs(0, 0, 303, 220);
      o->color((Fl_Color)0xfffffffe);
       {Fl_Group* o = new Fl_Group(1, 24, 301, 195, _("Brace Style"));
         {Fl_Group* o = new Fl_Group(14, 22, 282, 122, _("Brace Style"));
          o->box(FL_ENGRAVED_BOX);
          o->align(FL_ALIGN_TOP|FL_ALIGN_LEFT);
           {Fl_Box* o = new Fl_Box(20, 6, 47, 20, _("if ( x ) {"));
            o->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
          }
           {Fl_Box* o = new Fl_Box(20, 25, 45, 20, _("++y;"));
            o->align(FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
          }
           {Fl_Box* o = new Fl_Box(20, 41, 36, 20, _("}"));
            o->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
          }
           {Fl_Box* o = new Fl_Box(114, 6, 47, 20, _("if ( x )"));
            o->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
          }
           {Fl_Box* o = new Fl_Box(114, 25, 36, 20, _("{"));
            o->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
          }
           {Fl_Box* o = new Fl_Box(115, 42, 46, 20, _("++y;"));
            o->align(FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
          }
           {Fl_Box* o = new Fl_Box(114, 59, 36, 20, _("}"));
            o->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
          }
           {Fl_Round_Button* o = pStyle1 = new Fl_Round_Button(16, 84, 66, 25, _("Style 1"));
            o->type(Fl_Round_Button::RADIO);
            o->value(1);
            o->callback((Fl_Callback*)cb_pStyle1);
          }
           {Fl_Box* o = new Fl_Box(201, 6, 47, 20, _("if ( x )"));
            o->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
          }
           {Fl_Box* o = new Fl_Box(201, 25, 36, 20, _("{"));
            o->align(FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
          }
           {Fl_Box* o = new Fl_Box(227, 42, 34, 22, _("++y;"));
            o->align(FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
          }
           {Fl_Box* o = new Fl_Box(201, 59, 36, 20, _("}"));
            o->align(FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
          }
           {Fl_Round_Button* o = pStyle2 = new Fl_Round_Button(109, 84, 66, 25, _("Style 2"));
            o->type(Fl_Round_Button::RADIO);
            o->callback((Fl_Callback*)cb_pStyle2);
          }
           {Fl_Round_Button* o = pStyle3 = new Fl_Round_Button(200, 84, 66, 25, _("Style 3"));
            o->type(Fl_Round_Button::RADIO);
            o->callback((Fl_Callback*)cb_pStyle3);
          }
          o->end();
        }
         {Fl_Check_Button* o = pNoSpaceParens = new Fl_Check_Button(15, 147, 195, 22, _("No space before parentheses"));
          o->callback((Fl_Callback*)cb_pNoSpaceParens);
        }
         {Fl_Check_Button* o = pBraceFuncs = new Fl_Check_Button(15, 170, 174, 22, _("Apply to function braces"));
          o->value(1);
          o->callback((Fl_Callback*)cb_pBraceFuncs);
        }
        o->end();
      }
       {Fl_Group* o = new Fl_Group(1, 24, 301, 195, _("Other"));
        o->hide();
         {Fl_Group* o = new Fl_Group(11, 22, 284, 90, _("Indentation"));
          o->box(FL_ENGRAVED_BOX);
          o->align(FL_ALIGN_TOP|FL_ALIGN_LEFT);
           {Fl_Value_Input* o = pTabSize = new Fl_Value_Input(129, 33, 60, 22, _("Tab size for indents"));
            o->maximum(12);
            o->value(2);
            o->callback((Fl_Callback*)cb_pTabSize);
          }
           {Fl_Check_Button* o = pIndentTabs = new Fl_Check_Button(13, 7, 114, 22, _("Indent with tabs"));
            o->callback((Fl_Callback*)cb_pIndentTabs);
          }
           {Fl_Check_Button* o = pIndentCode = new Fl_Check_Button(14, 58, 151, 22, _("Indent code blocks"));
            o->callback((Fl_Callback*)cb_pIndentCode);
          }
          o->end();
        }
         {Fl_Check_Button* o = pReturnParens = new Fl_Check_Button(10, 120, 220, 22, _("Always use parentheses on return"));
          o->callback((Fl_Callback*)cb_pReturnParens);
        }
        o->end();
      }
      o->end();
    }
     {Fl_Button* o = new Fl_Button(115, 227, 59, 23, _("Cancel"));
      o->callback((Fl_Callback*)cb_Cancel);
    }
     {Fl_Button* o = new Fl_Button(180, 227, 59, 23, _("Save"));
      o->callback((Fl_Callback*)cb_Save);
    }
     {Fl_Button* o = new Fl_Button(245, 227, 59, 23, _("Use"));
      o->callback((Fl_Callback*)cb_Use);
    }
    o->end();
    o->resizable(o);
  }
  return  w;
}