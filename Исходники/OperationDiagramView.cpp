static void displayContextMenu(guint button, guint32 acttime, gpointer data)
    {
    GdkEventButton *event = static_cast<GdkEventButton*>(data);
    const OperationClass *node = gOperationDiagramView->getDiagram().getNode(
        static_cast<int>(event->x), static_cast<int>(event->y));
    const OperationCall *opcall = gOperationDiagramView->getDiagram().getOperation(
            gStartPosInfo.x, gStartPosInfo.y);
    OovStringRef const nodeitems[] =
        {
        "OperGotoClassMenuitem",
        "RemoveOperClassMenuitem",
        };
    Builder *builder = Builder::getBuilder();
    for(size_t i=0; i<sizeof(nodeitems)/sizeof(nodeitems[i]); i++)
        {
        gtk_widget_set_sensitive(builder->getWidget(nodeitems[i]),
                node != nullptr);
        }
    OovStringRef const operitems[] =
        {
        "OperGotoOperationMenuitem",
        "AddCallsMenuitem",
        "AddCallersMenuitem",
        "RemoveCallsMenuitem"
        };
    for(size_t i=0; i<sizeof(operitems)/sizeof(operitems[i]); i++)
        {
        gtk_widget_set_sensitive(builder->getWidget(operitems[i]),
                opcall != nullptr);
        }
    gtk_widget_set_sensitive(builder->getWidget("ViewOperSourceMenuitem"),
            opcall != nullptr || node != nullptr);

    GtkMenu *menu = builder->getMenu("DrawOperationPopupMenu");
    gtk_menu_popup(menu, nullptr, nullptr, nullptr, nullptr, button, acttime);
    gStartPosInfo.set(static_cast<int>(event->x), static_cast<int>(event->y));
    }