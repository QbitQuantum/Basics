Fl_Window* make_about_panel(const char *copyright) {
  Fl_Window* w;
   {Fl_Window* o = about_panel = new Fl_Window(330, 276, _("About eFluid"));
    w = o;
    o->type(240);
    o->selection_color((Fl_Color)47);
    o->shortcut(0xff1b);
     {Fl_Group* o = display_group = new Fl_Group(0, 0, 330, 240);
       {Fl_Group* o = new Fl_Group(5, 5, 320, 55, _("eFluid"));
        o->box(FL_ENGRAVED_BOX);
        o->label_font(fl_fonts+1);
        o->label_type(FL_EMBOSSED_LABEL);
        o->color((Fl_Color)0xb3b3be00);
        o->label_color((Fl_Color)32);
        o->selection_color((Fl_Color)47);
        o->label_size(40);
        o->align(FL_ALIGN_INSIDE);
        o->end();
      }
       {Fl_Button* o = new Fl_Button(5, 165, 320, 70, _("\302\251""2002-2003\nClick here for more information"));
        o->box(FL_ENGRAVED_BOX);
        o->label_font(fl_fonts+1);
        o->color((Fl_Color)0xb3b3be00);
        o->label_color((Fl_Color)32);
        o->highlight_color((Fl_Color)0x9d9da700);
        o->highlight_label_color((Fl_Color)55);
        o->label_size(14);
        o->callback((Fl_Callback*)cb_2002);
        o->align(FL_ALIGN_WRAP);
      }
       {Fl_Box* o = new Fl_Box(5, 60, 320, 105, _("EFLTK User Interface Designer\nVersion 2.0.3"));
        o->box(FL_ENGRAVED_BOX);
        o->label_font(fl_fonts+1);
        o->label_type(FL_EMBOSSED_LABEL);
        o->color((Fl_Color)0xb3b3be00);
        o->label_color((Fl_Color)32);
        o->selection_color((Fl_Color)47);
        o->label_size(18);
      }
      o->end();
    }
     {Fl_Box* o = copyright_box = new Fl_Box(0, 0, 330, 240);
      o->label_size(10);
      o->align(FL_ALIGN_TOP|FL_ALIGN_LEFT|FL_ALIGN_INSIDE|FL_ALIGN_CLIP|FL_ALIGN_WRAP);
      o->hide();
      o->label(copyright);
    }
     {Fl_Return_Button* o = new Fl_Return_Button(5, 245, 320, 25, _("OK"));
      o->label_size(10);
      o->shortcut(0xff0d);
      o->callback((Fl_Callback*)cb_OK);
    }
    o->end();
  }
  return  w;
}