void QMenuBarPrivate::QWceMenuBarPrivate::rebuild()
{
    d->q_func()->resize(0,0);
    parentWindowHandle = d->q_func()->parentWidget() ? QApplicationPrivate::getHWNDForWidget(d->q_func()->parentWidget()) :
                                                       QApplicationPrivate::getHWNDForWidget(d->q_func());
    if (d->wceClassicMenu) {
        QList<QAction*> actions = d->actions;
        int maxEntries;
        int resourceHandle;
        if (actions.size() < 5) {
            maxEntries = 4;
            resourceHandle = IDR_MAIN_MENU3;
        } else if (actions.size() < 7) {
            maxEntries = 6;
            resourceHandle = IDR_MAIN_MENU4;
        }
        else {
          maxEntries = 8;
          resourceHandle = IDR_MAIN_MENU5;
        }
        Q_ASSERT_X(menubarHandle, "rebuild !created", "menubar already deleted");
        qt_wce_clear_menu(menuHandle);
        DestroyWindow(menubarHandle);
        menubarHandle = qt_wce_create_menubar(parentWindowHandle, qt_wce_get_module_handle(), resourceHandle);
        Q_ASSERT_X(menubarHandle, "rebuild classic menu", "cannot create menubar from resource");
        DrawMenuBar(menubarHandle);
        QList<int> menu_ids;
        QList<int> item_ids;
        menu_ids << IDM_MENU1 << IDM_MENU2 << IDM_MENU3 << IDM_MENU4 << IDM_MENU5 << IDM_MENU6 << IDM_MENU7 << IDM_MENU8;
        item_ids << IDM_ITEM1 << IDM_ITEM2 << IDM_ITEM3 << IDM_ITEM4 << IDM_ITEM5 << IDM_ITEM6 << IDM_ITEM7 << IDM_ITEM8;

        for (int i = 0; i < actionItemsClassic.size(); ++i)
          if (!actionItemsClassic.value(i).empty())
            qt_wce_delete_action_list(&actionItemsClassic[i]);
        actionItemsClassic.clear();

        for (int i = 0; i < actions.size(); ++i) {
            qt_wce_rename_menu_item(menubarHandle, menu_ids.at(i), actions.at(i)->text());
            QList<QAction *> subActions = actions.at(i)->menu()->actions();
            HMENU subMenuHandle = (HMENU) SendMessage(menubarHandle, SHCMBM_GETSUBMENU,0 , menu_ids.at(i));
            DeleteMenu(subMenuHandle, item_ids.at(i), MF_BYCOMMAND);
            for (int c = 0; c < subActions.size(); ++c) {
                QList<QWceMenuAction*> list;
                actionItemsClassic.append(list);
                QWceMenuAction *action = new QWceMenuAction;
                action->action = subActions.at(c);
                action->command = qt_wce_menu_static_cmd_id++;
                action->menuHandle = subMenuHandle;
                actionItemsClassic.last().append(action);
                qt_wce_insert_action(subMenuHandle, action);
            }
        }
        for (int i = actions.size();i<maxEntries;++i) {
            qt_wce_rename_menu_item(menubarHandle, menu_ids.at(i), QString());
            qt_wce_disable_soft_key(menubarHandle, menu_ids.at(i));
        }
    } else {
        leftButtonAction = d->defaultAction;
        if (!leftButtonAction)
            leftButtonAction = qt_wce_get_quit_action(actionItems);

        leftButtonIsMenu = (leftButtonAction && leftButtonAction->menu());
        Q_ASSERT_X(menubarHandle, "rebuild !created", "menubar already deleted");
        qt_wce_clear_menu(menuHandle);
        DestroyWindow(menubarHandle);
        if (leftButtonIsMenu) {
            menubarHandle = qt_wce_create_menubar(parentWindowHandle, qt_wce_get_module_handle(), IDR_MAIN_MENU2);
            Q_ASSERT_X(menubarHandle, "rebuild !created left menubar", "cannot create menubar from resource");
            menuHandle = (HMENU) SendMessage(menubarHandle, SHCMBM_GETSUBMENU,0,IDM_MENU);
            Q_ASSERT_X(menuHandle, "rebuild !created", "IDM_MENU not found - invalid resource?");
            DeleteMenu(menuHandle, IDM_ABOUT, MF_BYCOMMAND);
            leftButtonMenuHandle = (HMENU) SendMessage(menubarHandle, SHCMBM_GETSUBMENU,0,IDM_LEFTMENU);
            Q_ASSERT_X(leftButtonMenuHandle, "rebuild !created", "IDM_LEFTMENU not found - invalid resource?");
            DeleteMenu(leftButtonMenuHandle, IDM_VIEW, MF_BYCOMMAND);
        } else {
            menubarHandle = qt_wce_create_menubar(parentWindowHandle, qt_wce_get_module_handle(), IDR_MAIN_MENU);
            Q_ASSERT_X(menubarHandle, "rebuild !created no left menubar", "cannot create menubar from resource");
            menuHandle = (HMENU) SendMessage(menubarHandle, SHCMBM_GETSUBMENU,0,IDM_MENU);
            Q_ASSERT_X(menuHandle, "rebuild !created", "IDM_MENU not found - invalid resource?");
            DeleteMenu(menuHandle, IDM_ABOUT, MF_BYCOMMAND);
            leftButtonMenuHandle = 0;
            leftButtonCommand = qt_wce_menu_static_cmd_id++;
            qt_wce_change_command(menubarHandle, IDM_EXIT, leftButtonCommand);
        }

        if (actionItems.size() == 0) {
            qt_wce_rename_menu_item(menubarHandle, IDM_MENU, QLatin1String(""));
            qt_wce_disable_soft_key(menubarHandle, IDM_MENU);
        }
        for (int i = 0; i < actionItems.size(); ++i) {
            QWceMenuAction *action = actionItems.at(i);
            action->menuHandle = menuHandle;
            qt_wce_insert_action(menuHandle, action);
        }
        if (!leftButtonIsMenu) {
            if (leftButtonAction) {
                qt_wce_rename_menu_item(menubarHandle, leftButtonCommand, leftButtonAction->text());
                qt_wce_enable_soft_key(menubarHandle, leftButtonCommand);
            } else {
                qt_wce_rename_menu_item(menubarHandle, leftButtonCommand, QLatin1String(""));           
                qt_wce_disable_soft_key(menubarHandle, leftButtonCommand);
            }
        } else {
            qt_wce_rename_menu_item(menubarHandle, IDM_LEFTMENU, leftButtonAction->text());
            QList<QAction *> actions = leftButtonAction->menu()->actions();
            qt_wce_delete_action_list(&actionItemsLeftButton);
            for (int i=0; i<actions.size(); ++i) {
                QWceMenuAction *action = new QWceMenuAction;
                action->action = actions.at(i);
                action->command = qt_wce_menu_static_cmd_id++;
                action->menuHandle = leftButtonMenuHandle;
                actionItemsLeftButton.append(action);
                qt_wce_insert_action(leftButtonMenuHandle, action);
            }
        }
    }
    DrawMenuBar(menubarHandle);
}