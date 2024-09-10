void MainSynthWindow::populateMenu (void)
{
    /* File */
    {
        Gtk::Menu::MenuList &menulist = menuFile_.items();

        menulist.push_back(
            Gtk::Menu_Helpers::MenuElem("_Keyboard",
                                        Gtk::AccelKey("<ctrl>k"),
                                        sigc::mem_fun(*this, &MainSynthWindow::menuKeyboard)));

        menulist.push_back(
            Gtk::Menu_Helpers::MenuElem("_Patch Selector",
                                        Gtk::AccelKey("<ctrl>p"),
                                        sigc::mem_fun(*this, &MainSynthWindow::menuPatchSel)));

        menulist.push_back(
            Gtk::Menu_Helpers::MenuElem("_MIDI Controllers",
                                        Gtk::AccelKey("<ctrl>m"),
                                        sigc::mem_fun(*this, &MainSynthWindow::menuMidiMap)));

        menulist.push_back(Gtk::Menu_Helpers::SeparatorElem());

        menulist.push_back(
            Gtk::Menu_Helpers::MenuElem("_Quit",
                                        Gtk::AccelKey("<ctrl>q"),
                                        sigc::mem_fun(*this, &MainSynthWindow::menuQuit)));
    }

#ifdef HAVE_JACK
    /* JACK */
    if (dynamic_cast<gthJackAudio*>(audio_) != NULL)
    {
        gthPrefs *prefs = gthPrefs::instance();
        Gtk::Menu::MenuList &menulist = menuJack_.items();
        Gtk::CheckMenuItem *elem;
        sigc::slot0<void> autoslot =
            sigc::mem_fun(*this, &MainSynthWindow::menuJackAuto);
        string** vals;
        bool sel;
        
        menulist.push_back(
            Gtk::Menu_Helpers::MenuElem("_Connect to JACK now",
                sigc::mem_fun(*this, &MainSynthWindow::menuJackTry)));

        menulist.push_back(
            Gtk::Menu_Helpers::MenuElem("_Disconnect from JACK",
                sigc::mem_fun(*this, &MainSynthWindow::menuJackDis)));

        menulist.back().set_sensitive(false);

        menulist.push_back(Gtk::Menu_Helpers::SeparatorElem());

        menulist.push_back(
            Gtk::Menu_Helpers::CheckMenuElem ("_Auto-connect to JACK",
                autoslot));

        elem = (Gtk::CheckMenuItem*)&menulist.back();
    
        vals = prefs->Get("autoconnect");
        sel = !!(vals && *vals[0] == "true");
        elem->set_active(sel);
    }
#endif /* HAVE_JACK */
    
    /* Help */
    {
        Gtk::Menu::MenuList &menulist = menuHelp_.items();

        menulist.push_back(
            Gtk::Menu_Helpers::MenuElem("_About",
                                        sigc::mem_fun(
                                            *this, &MainSynthWindow::menuAbout)
                ));
    }

    /* add the menus to the menubar */
    {
        Gtk::Menu::MenuList &menulist = menuBar_.items();

        menulist.push_back(Gtk::Menu_Helpers::MenuElem("_File",
                                                       menuFile_));

#ifdef HAVE_JACK
        if (dynamic_cast<gthJackAudio*>(audio_) != NULL)
            menulist.push_back(Gtk::Menu_Helpers::MenuElem("_JACK",
                                                        menuJack_));
#endif
        
        Gtk::MenuItem *helpMenu = manage(new Gtk::MenuItem("_Help", true));
        helpMenu->set_submenu(menuHelp_);
        helpMenu->set_right_justified();
        menulist.push_back(*helpMenu);
    }
}