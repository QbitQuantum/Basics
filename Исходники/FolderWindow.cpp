void FolderWindow::AddStructure(const char* filename, const int index)
{
    
    Fl_Pack* pack = folderPack;
    pack->begin();
    
    int vertPosn = pack->children() * NAVBUTTONS_BHEIGHT; //+ pack->y() + 15;
    
    Fl_Group* group = new Fl_Group(pack->x(), vertPosn, pack->w(), NAVBUTTONS_BHEIGHT);
    group->begin();
    
    Fl_Button* label = new Fl_Button(pack->x() + 10, vertPosn, pack->w() - 40, 30, filename);
    label->align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE | FL_ALIGN_LEFT);
    label->callback(FolderWindow::ShowFileCallback);
    label->user_data((void*)index);
    label->labelcolor(GUI_BTEXT_COLOR);
    char labelWithIcon[MAX_BUFFER_SIZE];

    std::string spaceBuffer = string("                                                    ");
    int curLabelLen = 0;
    char filePrefix[MAX_BUFFER_SIZE];
    size_t fileNameBytes = strlen(filename);
    snprintf(filePrefix, MAX_BUFFER_SIZE, "%-.20s%s", filename, 
	     fileNameBytes > MAX_FOLDER_LABEL_CHARS ? "..." : "");
    snprintf(labelWithIcon, MAX_BUFFER_SIZE - 1, "@filenew   %s%s", 
	     filePrefix, spaceBuffer.substr(0, 
             MAX(0, MAX_FOLDER_LABEL_CHARS - ((int ) strlen(filePrefix)))).c_str());
    //strcat(labelWithIcon, "   @|>");
    label->copy_label(labelWithIcon);
    label->tooltip(filename); 
    
    Fl_Button* removeButton = new Fl_Button(pack->x() + pack->w() - 20, vertPosn + 5, 20, 20);
    removeButton->callback(FolderWindow::RemoveCallback);
    removeButton->user_data((void*)index);
    removeButton->label("@1+");
    removeButton->labelcolor(GUI_TEXT_COLOR);
    
    group->resizable(label);
    group->end();
    pack->end();
        
    folderScroll->redraw();
}