// add parameter string to tree
Fl_Widget *onelabGroup::_addParameterWidget(onelab::string &p, int ww, int hh,
                                            Fl_Tree_Item *n, bool highlight, Fl_Color c)
{
  char *path = strdup(getPath(n).c_str());
  _treeStrings.push_back(path);

  // macro button
  if(p.getAttribute("Macro") == "Gmsh"){
    Fl_Button *but = new Fl_Button(1, 1, ww / _widgetLabelRatio, hh);
    but->box(FL_FLAT_BOX);
    but->color(_tree->color());
    but->selection_color(_tree->color());
    but->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE | FL_ALIGN_CLIP);
    //TODO but->callback(onelab_string_button_cb, (void*)path);
    if(highlight) but->color(c);
    return but;
  }

  // non-editable value
  if(p.getReadOnly()){
    Fl_Output *but = new Fl_Output(1, 1, ww, hh);
    but->value(p.getValue().c_str());
    but->align(FL_ALIGN_RIGHT);
    if(highlight) but->color(c);
    return but;
  }

  // simple string (no menu)
  if(p.getChoices().empty() && p.getKind() != "file"){
    Fl_Input *but = new Fl_Input(1, 1, ww, hh);
    but->value(p.getValue().c_str());
    //TODO but->callback(onelab_string_input_cb, (void*)path);
    but->when(FL_WHEN_ENTER_KEY);
    but->align(FL_ALIGN_RIGHT);
    if(highlight) but->color(c);
    return but;
  }

  // general string input
  Fl_Input_Choice *but = new Fl_Input_Choice(1, 1, ww, hh);
  std::string multipleSelection = p.getAttribute("MultipleSelection");
  if(multipleSelection.size())
    ;//but->menubutton()->callback(multiple_selection_menu_cb, but);
  std::vector<Fl_Menu_Item> menu;
  for(unsigned int j = 0; j < p.getChoices().size(); j++){
    char *str = strdup(p.getChoices()[j].c_str());
    _treeStrings.push_back(str);
    bool divider = (p.getKind() == "file" &&
                    j == p.getChoices().size() - 1);
    int choice = multipleSelection.size() ? FL_MENU_TOGGLE : 0;
    if(multipleSelection.size() > j && multipleSelection[j] == '1')
      choice |= FL_MENU_VALUE;
    Fl_Menu_Item it = {str, 0, 0, 0, divider ? FL_MENU_DIVIDER : choice};
    menu.push_back(it);
  }
  //if(p.getKind() == "file"){
  //  Fl_Menu_Item it = {"Choose...", 0, onelab_input_choice_file_chooser_cb, (void*)n};
  //  menu.push_back(it);
  //  Fl_Menu_Item it2 = {"Edit...", 0, onelab_input_choice_file_edit_cb, (void*)n};
  //  menu.push_back(it2);
  //  if(GuessFileFormatFromFileName(p.getValue()) >= 0){
  //    Fl_Menu_Item it3 = {"Merge...", 0, onelab_input_choice_file_merge_cb, (void*)n};
  //    menu.push_back(it3);
  //  }
  //}
  Fl_Menu_Item it = {0};
  menu.push_back(it);
  but->menubutton()->copy(&menu[0]);
  but->value(p.getValue().c_str());
  but->callback(onelab_string_input_choice_cb, (void*)path);
  but->input()->when(FL_WHEN_ENTER_KEY);
  but->align(FL_ALIGN_RIGHT);
  if(highlight) but->input()->color(c);
  return but;
}