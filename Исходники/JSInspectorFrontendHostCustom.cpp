JSValue JSInspectorFrontendHost::showContextMenu(ExecState* exec)
{
    if (exec->argumentCount() < 2)
        return jsUndefined();
#if ENABLE(CONTEXT_MENUS)
    Event* event = toEvent(exec->argument(0));

    JSArray* array = asArray(exec->argument(1));
    Vector<ContextMenuItem*> items;

    for (size_t i = 0; i < array->length(); ++i) {
        JSObject* item = asObject(array->getIndex(i));
        JSValue label = item->get(exec, Identifier(exec, "label"));
        JSValue type = item->get(exec, Identifier(exec, "type"));
        JSValue id = item->get(exec, Identifier(exec, "id"));
        JSValue enabled = item->get(exec, Identifier(exec, "enabled"));
        JSValue checked = item->get(exec, Identifier(exec, "checked"));
        if (!type.isString())
            continue;

        String typeString = ustringToString(type.toString(exec)->value(exec));
        if (typeString == "separator") {
            items.append(new ContextMenuItem(SeparatorType,
                                             ContextMenuItemCustomTagNoAction,
                                             String()));
        } else {
            ContextMenuAction typedId = static_cast<ContextMenuAction>(ContextMenuItemBaseCustomTag + id.toInt32(exec));
            ContextMenuItem* menuItem = new ContextMenuItem((typeString == "checkbox" ? CheckableActionType : ActionType), typedId, ustringToString(label.toString(exec)->value(exec)));
            if (!enabled.isUndefined())
                menuItem->setEnabled(enabled.toBoolean(exec));
            if (!checked.isUndefined())
                menuItem->setChecked(checked.toBoolean(exec));
            items.append(menuItem);
        }
    }

    impl()->showContextMenu(event, items);
#endif
    return jsUndefined();
}