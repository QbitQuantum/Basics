void ClassDiagramView::displayDrawContextMenu(guint button, guint32 acttime, gpointer data)
    {
    GdkEventButton *event = static_cast<GdkEventButton*>(data);
    ClassNode *node = getNode(static_cast<int>(event->x), static_cast<int>(event->y));
    OovStringRef const nodeMenus[] =
        {
        "GotoClassMenuitem", "ClassPreferencesMenuitem", "AddSelectedMenuitem",
        "AddStandardMenuitem", "AddAllMenuitem",
        "AddSuperclassesMenuitem", "AddSubclassesMenuitem",
        "AddMembersUsingMenuitem", "AddMemberUsersMenuitem",
        "AddTemplateMenuItem",
        "AddFuncParamsUsingMenuitem", "AddFuncParamUsersMenuitem",
        "AddFuncBodyVarUsingMenuitem", "AddFuncBodyVarUsersMenuitem",
        "RemoveClassMenuitem", "ViewSourceMenuitem"
        };
    Builder *builder = Builder::getBuilder();
    for(size_t i=0; i<sizeof(nodeMenus)/sizeof(nodeMenus[i]); i++)
        {
        gtk_widget_set_sensitive(builder->getWidget(
                nodeMenus[i]), node != nullptr);
        }

    GtkMenu *menu = builder->getMenu("DrawClassPopupMenu");
    gtk_menu_popup(menu, nullptr, nullptr, nullptr, nullptr, button, acttime);
    gStartPosInfo.set(static_cast<int>(event->x), static_cast<int>(event->y));
    }