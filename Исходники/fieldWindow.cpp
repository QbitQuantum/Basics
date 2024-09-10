void fieldWindow::editField(Field *f)
{
  editor_group->user_data(f);
  put_on_view_btn->deactivate();
  delete_btn->deactivate();
  if(f == NULL){
    selected_id = -1;
    editor_group->hide();
    empty_message->show();
    loadFieldList();
    return;
  }

  FL_NORMAL_SIZE -= _deltaFontSize;

  selected_id = f->id;
  empty_message->hide();
  editor_group->show();
  editor_group->user_data(f);
  title->label(f->getName());
  options_scroll->clear();
  options_widget.clear();
  options_scroll->begin();
  int xx = options_scroll->x();
  int yy = options_scroll->y();

  std::string help = f->getDescription();
  ConvertToHTML(help);
  if (! f->options.empty())
    help += std::string("<p><center><b>Options</b></center>");
  for(std::map<std::string, FieldOption*>::iterator it = f->options.begin();
      it != f->options.end(); it++){
    Fl_Widget *input;
    help += std::string("<p><b>") + it->first + "</b>";
    help += " (<em>" + it->second->getTypeName() + "</em>): ";
    help += it->second->getDescription();
    switch(it->second->getType()){
    case FIELD_OPTION_INT:
    case FIELD_OPTION_DOUBLE:
      input = new Fl_Value_Input(xx, yy, IW, BH, it->first.c_str());
      input->align(FL_ALIGN_RIGHT);
      break;
    case FIELD_OPTION_BOOL:
      input = new Fl_Check_Button(xx, yy, 2 * BB, BH, it->first.c_str());
      input->type(FL_TOGGLE_BUTTON);
      break;
    case FIELD_OPTION_PATH:
      {
        input = new Fl_Input(xx, yy, IW, BH, it->first.c_str());
        input->align(FL_ALIGN_RIGHT);
        int tw = (int)fl_width(it->first.c_str());
        Fl_Button *b = new Fl_Button(xx + IW + tw + 2 * WB, yy, BB, BH, "Choose");
        b->callback(field_select_file_cb, input);
      }
      break;
    case FIELD_OPTION_STRING:
      input = new Fl_Input(xx, yy, IW, BH, it->first.c_str());
      input->align(FL_ALIGN_RIGHT);
      break;
    case FIELD_OPTION_LIST:
    default:
      input = new Fl_Input(xx, yy, IW, BH, it->first.c_str());
      input->align(FL_ALIGN_RIGHT);
      break;
    }
    options_widget.push_back(input);
    yy += BH;
  }
  if (! f->callbacks.empty())
    help += std::string("<p><center><b>Actions</b></center>");
  for(std::map<std::string, FieldCallback*>::iterator it = f->callbacks.begin();
      it != f->callbacks.end(); it++){
    Fl_Widget *btn;
    help += std::string("<p><b>") + it->first + "</b>: ";
    help += it->second->getDescription();
    btn = new Fl_Button(xx, yy, IW, BH, it->first.c_str());
    btn->callback(field_callback_cb, it->second);
    yy += BH;
  }
  help_display->value(help.c_str());
  options_scroll->end();

  FL_NORMAL_SIZE += _deltaFontSize;

  loadFieldOptions();
  options_scroll->damage(1);
  put_on_view_btn->activate();
  delete_btn->activate();
  loadFieldList();
}