int KankerApp::createGui() {

  /* Main panel.*/
  gui = new Panel(new RenderGL(), painter.height() - 20, GUI_STYLE_NONE);
  if (NULL == gui) {
    RX_ERROR("Cannot allocate the gui.");
    return -1;
  }

  gui->setPosition(painter.width() - (gui->w + 30), 8);
  gui->lockPosition();
  
  /* Font options. */
  Group* group_font = gui->addGroup("Font", GUI_STYLE_NONE);
  if (NULL == group_font) {
    RX_ERROR("Failed to allocate a new gui group.");
    return -2;
  }

  group_font->add(new Button("Add character to loaded font",  0, GUI_ICON_FONT, on_add_characters_clicked, this,  GUI_STYLE_NONE));
  group_font->add(new Button("Show test message",  0, GUI_ICON_FONT, on_font_test_clicked, this,  GUI_STYLE_NONE));
  group_font->add(new Button("Send test message to robot", 0, GUI_ICON_UPLOAD, on_abb_send_message_to_robot_clicked, this, GUI_STYLE_NONE));
  group_font->add(new Button("Send test positions to robot",  0, GUI_ICON_UPLOAD, on_abb_send_test_clicked, this,  GUI_STYLE_NONE));
  group_font->add(new Button("Send SWIPE to robot",  0, GUI_ICON_UPLOAD, on_abb_send_swipe_clicked, this,  GUI_STYLE_NONE)).setMarginBottom(10);

  /* Saving */
  Group* group_save = gui->addGroup("Save font", GUI_STYLE_NONE);
  if (NULL == group_save) {
    RX_ERROR("Failed to allocate a new gui group");
    return -3;
  }

  group_save->add(new Text("Filename", font_filename, 135));
  group_save->add(new Button("Save",  0, GUI_ICON_FLOPPY_O, on_font_save_clicked, this, GUI_STYLE_NONE)).setMarginBottom(10);
  
  /* Loading */
  {
    std::vector<std::string> fonts;
    if (0 == getFontFiles(fonts)) {
      Group* group_load = gui->addGroup("Load font", GUI_STYLE_NONE);
      if (NULL == group_load) {
        RX_ERROR("Failed to allocate the load gui group");
        return -4;
      }

      Select* sel = new Select("Load file", 1, fonts, on_font_file_selected, this, GUI_STYLE_NONE);
      sel->setDirection(GUI_DIRECTION_UP);
      group_load->add(sel);
      group_load->add(new Button("Load",  0, GUI_ICON_FOLDER_OPEN, on_font_load_clicked, this, GUI_STYLE_NONE)).setMarginBottom(10);
    }
  }

  /* Abb settings. */
  Group* group_abb = gui->addGroup("Abb", GUI_STYLE_NONE);
  if (NULL == group_abb) {
    RX_ERROR("Failed to allocate the abb gui group");
    return -5;
  }

  group_abb->add(new Slider<float>("ABB.offset_x", kanker_abb.offset_x, -1300, 1300, 1, GUI_STYLE_NONE));
  group_abb->add(new Slider<float>("ABB.offset_y", kanker_abb.offset_y, -1300, 1300, 1, GUI_STYLE_NONE));
  group_abb->add(new Slider<float>("ABB.char_scale", kanker_abb.char_scale, 0, 1000, 1, GUI_STYLE_NONE));
  group_abb->add(new Slider<float>("ABB.line_height", kanker_abb.line_height, 0, 1000, 1, GUI_STYLE_NONE));
  group_abb->add(new Slider<float>("ABB.word_spacing", kanker_abb.word_spacing, 0, 1000, 1, GUI_STYLE_NONE));
  group_abb->add(new Slider<int>("ABB.min_x", kanker_abb.min_x, -15000, 15000, 1, GUI_STYLE_NONE));
  group_abb->add(new Slider<int>("ABB.max_x", kanker_abb.max_x, -15000, 15000, 1, GUI_STYLE_NONE));
  group_abb->add(new Slider<int>("ABB.min_y", kanker_abb.min_y, -15000, 15000, 1, GUI_STYLE_NONE));
  group_abb->add(new Slider<int>("ABB.max_y", kanker_abb.max_y, -15000, 15000, 1, GUI_STYLE_NONE));
  group_abb->add(new Slider<float>("ABB.min_point_dist", kanker_abb.min_point_dist, 1.0, 50.0, 0.5, GUI_STYLE_NONE)).setMarginBottom(10);
  group_abb->add(new Text("ABB.host", kanker_abb.abb_host));
  group_abb->add(new Slider<int>("ABB.port", kanker_abb.abb_port, 0, 999999, 1, GUI_STYLE_NONE)).setMarginBottom(10);
  group_abb->add(new Button("Save ABB Settings", 0, GUI_ICON_FLOPPY_O, on_abb_save_settings_clicked, this, GUI_STYLE_NONE));
  group_abb->add(new Button("Load ABB Settings", 0, GUI_ICON_REFRESH, on_abb_load_settings_clicked, this, GUI_STYLE_NONE));
  return 0;
}