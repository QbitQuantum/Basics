SaveTrajectoryFltkMenu::SaveTrajectoryFltkMenu(VMDApp *vmdapp)
: VMDFltkMenu("save", "Save Trajectory", vmdapp) {
  
  size(450, 250);
    { Fl_Choice* o = molchooser = new Fl_Choice(120, 10, 320, 25, "Save data from: ");
      o->box(FL_THIN_UP_BOX);
      o->down_box(FL_BORDER_BOX);
      o->color(VMDMENU_CHOOSER_BG);
      o->selection_color(VMDMENU_CHOOSER_SEL);
      o->callback(molchooser_cb, this);
    }
    { Fl_Input *o = selectinput = new Fl_Input(120, 45, 295, 25, "Selected atoms:");
      o->selection_color(VMDMENU_VALUE_SEL);
    }
    { Fl_Choice* o = repchooser = new Fl_Choice(415, 45, 25, 25);
      o->down_box(FL_BORDER_BOX);
      o->align(FL_ALIGN_TOP_LEFT);
      o->color(VMDMENU_CHOOSER_BG, VMDMENU_CHOOSER_SEL);
      o->callback(repchooser_cb, this);
    }
    { Fl_Choice* o = filetypechooser = new Fl_Choice(20, 90, 115, 25, "File type:");
      o->down_box(FL_BORDER_BOX);
      o->align(FL_ALIGN_TOP_LEFT);
      o->color(VMDMENU_CHOOSER_BG, VMDMENU_CHOOSER_SEL);
    }
    savebutton = new Fl_Return_Button(345, 90, 95, 25, "Save...");
    savebutton->callback(save_cb, this);
    { Fl_Group* o = timestepgroup = new Fl_Group(20, 145, 165, 95, "Frames: ");
      o->box(FL_ENGRAVED_FRAME);
      o->align(FL_ALIGN_TOP_LEFT);
      { Fl_Button* o = saveinbackgroundbutton = new Fl_Round_Button(30, 215, 150, 20, "Save in background");
        o->down_box(FL_ROUND_DOWN_BOX);
        o->type(FL_RADIO_BUTTON);
      }
      { Fl_Button* o = allatoncebutton = new Fl_Round_Button(30, 195, 150, 20, "Save all at once");
        o->down_box(FL_ROUND_DOWN_BOX);
        o->type(FL_RADIO_BUTTON);
      }
      { Fl_Input* o = firstinput = new Fl_Int_Input(25, 170, 45, 20, "First:");
        o->align(FL_ALIGN_TOP);
        o->selection_color(VMDMENU_VALUE_SEL);
      }
      { Fl_Input* o = lastinput = new Fl_Int_Input(80, 170, 45, 20, "Last:");
        o->align(FL_ALIGN_TOP);
        o->selection_color(VMDMENU_VALUE_SEL);
      }
      { Fl_Input* o = strideinput = new Fl_Int_Input(135, 170, 45, 20, "Stride:");
        o->align(FL_ALIGN_TOP);
        o->selection_color(VMDMENU_VALUE_SEL);
      }
      o->end();
      datasetbrowser = new Fl_Multi_Browser(195, 145, 240, 95, "Volumetric Datasets");
      datasetbrowser->align(5);
      datasetbrowser->color(VMDMENU_BROWSER_BG, VMDMENU_BROWSER_SEL);
    } 
    end();

  allatoncebutton->value(1);
  selected_molid = -1;
  datasetbrowser->deactivate();
  
  command_wanted(Command::PLUGIN_UPDATE);
  command_wanted(Command::MOL_NEW);
  command_wanted(Command::MOL_RENAME);
  command_wanted(Command::MOL_DEL);
  command_wanted(Command::MOL_ADDREP);
  command_wanted(Command::MOL_DELREP);
  command_wanted(Command::MOL_MODREP);
  command_wanted(Command::MOL_MODREPITEM);
  command_wanted(Command::ANIM_DELETE);
}