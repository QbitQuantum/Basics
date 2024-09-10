void SynthModular::LoadPlugins (string pluginPath) {
     int Width  = 35;
     int Height = 35;
     int SWidth  = 256;
     int SHeight = 256;
     Fl_Pixmap pic (SSM_xpm);
     Fl_Double_Window* Splash = new Fl_Double_Window ((Fl::w()/2) - (SWidth/2), (Fl::h()/2) - (SHeight/2),
                                                       SWidth, SHeight, "SSM");
     Splash->border(0);
     Fl_Box* pbut = new Fl_Box (0, 8, SWidth, SHeight, "");
     pbut->box (FL_NO_BOX);
     pic.label (pbut);
     Fl_Box *splashtext = new Fl_Box (5, SHeight-20, 200, 20, "Loading...");
     splashtext->labelsize (10);
     splashtext->box (FL_NO_BOX);
     splashtext->align (FL_ALIGN_INSIDE | FL_ALIGN_LEFT);
     Splash->add (pbut);
     Splash->add (splashtext);
     Splash->show();
     int ID=-1;
     vector<string> PluginVector;
     if (SpiralInfo::USEPLUGINLIST) PluginVector = SpiralInfo::PLUGINVEC;
     else {
        if (pluginPath.empty()) PluginVector = BuildPluginList (SpiralInfo::PLUGIN_PATH);
        else {
           string::iterator i = pluginPath.end() - 1;
           if (*i != '/') pluginPath += '/';
           PluginVector = BuildPluginList (pluginPath);
        }
     }
     for (vector<string>::iterator i=PluginVector.begin(); i!=PluginVector.end(); i++) {
         string Fullpath;
         if (pluginPath=="") Fullpath=SpiralInfo::PLUGIN_PATH+*i;
         else Fullpath = pluginPath + *"/" + *i;
         ID = PluginManager::Get()->LoadPlugin (Fullpath.c_str());
         if (ID!=PluginError) {
            #ifdef DEBUG_PLUGINS
            cerr << ID << " = Plugin [" << *i << "]" << endl;
            #endif
            Fl_ToolButton *NewButton = new Fl_ToolButton (0, 0, Width, Height, "");
            // we can't set user data, because the callback uses it
            // NewButton->user_data ((void*)(this));
            NewButton->labelsize (1);
            Fl_Pixmap *tPix = new Fl_Pixmap (PluginManager::Get()->GetPlugin(ID)->GetIcon());
            NewButton->image(tPix->copy(tPix->w(),tPix->h()));
            delete tPix;
            const char * gName = PluginManager::Get()->GetPlugin(ID)->GetGroupName();
            string GroupName(gName);
            Fl_Pack* the_group=NULL;
            // find or create this group, and add an icon
            map<string,Fl_Pack*>::iterator gi = m_PluginGroupMap.find (GroupName);
            if (gi == m_PluginGroupMap.end()) {
               the_group = new Fl_Pack (m_GroupTab->x(), 16, m_GroupTab->w(), m_GroupTab->h() - 15, gName);
               the_group->type(FL_HORIZONTAL);
               the_group->labelsize(8);
               the_group->color(SpiralInfo::GUICOL_Button);
               the_group->user_data((void*)(this));
               //m_GroupTab->add(the_group);
               m_GroupTab->value(the_group);
               m_PluginGroupMap[GroupName]=the_group;
            }
            else the_group = gi->second;
            NewButton->type (0);
            NewButton->box (FL_NO_BOX);
            NewButton->down_box (FL_NO_BOX);
            //NewButton->color(SpiralInfo::GUICOL_Button);
            //NewButton->selection_color(SpiralInfo::GUICOL_Button);
            the_group->add (NewButton);

            // we need to keep tooltips stored outside their widgets - widgets just have a pointer
            // I haven't done anything about cleaning up these strings - which may cause memory leaks?
            // But m_DeviceVec - which, I assume, would be used to keep track of / clean up the dynamicly
            //     created NewButton widgets isn't cleaned up either, so we might have 2 memory leaks
            //     involved? - but then again, they might be automatically deallocated because they're
            //     in another widget, in which case there's just one memory leak to deal with. (andy)
            string* PluginName = new string (*i);
            // find the first slash, if there is one, and get rid of everything before and including it
            unsigned int p = PluginName->find ('/');
            if (p < PluginName->length()) PluginName->erase (0, p);
            // find last . and get rid of everything after and including it
            p = PluginName->rfind ('.');
            unsigned int l = PluginName->length ();
            if (p < l) PluginName->erase (p, l);
            NewButton->tooltip (PluginName->c_str());
            // Slashes have significance to the menu widgets, remove them from the GroupName
            while ((p = GroupName.find ('/')) < PluginName->length())
                  GroupName = GroupName.replace (p, 1, " and ");
            string MenuEntry = "Plugins/" + GroupName + "/" + *PluginName;
            m_MainMenu->add (MenuEntry.c_str(), 0, cb_NewDeviceFromMenu, &Numbers[ID], 0);
            // when help is working better - this will put the plugins into the help menu
            // MenuEntry = "Help/" + MenuEntry;
            // m_MainMenu->add (MenuEntry.c_str(), 0, NULL, &Numbers[ID], 0);

            // Add the plugins to the canvas menu
            m_Canvas->AddPluginName (MenuEntry, PluginManager::Get()->GetPlugin(ID)->ID);
            // this overwrites the widget's user_data with that specified for the callback
            // so we can't use it for other purposes
            NewButton->callback ((Fl_Callback*)cb_NewDevice, &Numbers[ID]);
            NewButton->show();
            // Nothing else ever touches m_DeviceVec - is this right??? (andy)
            m_DeviceVec.push_back (NewButton);
            the_group->redraw();
            // m_NextPluginButton++;
            Fl::check();
            splashtext->label (PluginName->c_str());
            Splash->redraw();
         }
     }
     map<string,Fl_Pack*>::iterator PlugGrp;
     for (PlugGrp = m_PluginGroupMap.begin(); PlugGrp!= m_PluginGroupMap.end(); ++PlugGrp) {
         m_GroupTab->add (PlugGrp->second);
         PlugGrp->second->add (new Fl_Box (0, 0, 600, 100, ""));
     }
     // try to show the SpiralSound group
     PlugGrp = m_PluginGroupMap.find("SpiralSound");
     // can't find it - show the first plugin group
     if (PlugGrp==m_PluginGroupMap.end()) PlugGrp=m_PluginGroupMap.begin();
     m_GroupTab->value(PlugGrp->second);
     bool found_dummy;
     int i;
     do {
        found_dummy = false;
        for (i=0; i<m_MainMenu->size(); i++) {
            if (m_MainMenu->text (i) != NULL) {
               found_dummy = (strcmp ("dummy", m_MainMenu->text (i)) == 0);
               if (found_dummy) break;
            }
        }
        if (found_dummy) m_MainMenu->remove (i);
     } while (found_dummy);
     Splash->hide();
     delete Splash;
}