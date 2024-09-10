bool DockContainer::dockModule(ConfigModule *module)
{
    if(module == _module)
        return true;

    if(_module && _module->isChanged())
    {

        int res = KMessageBox::warningYesNoCancel(this, module ? i18n("There are unsaved changes in the active module.\n"
                                                                      "Do you want to apply the changes before running "
                                                                      "the new module or discard the changes?")
                                                               : i18n("There are unsaved changes in the active module.\n"
                                                                      "Do you want to apply the changes before exiting "
                                                                      "the Control Center or discard the changes?"),
                                                  i18n("Unsaved Changes"), KStdGuiItem::apply(), KStdGuiItem::discard());
        if(res == KMessageBox::Yes)
            _module->module()->applyClicked();
        if(res == KMessageBox::Cancel)
            return false;
    }

    raiseWidget(_busyw);
    kapp->processEvents();

    deleteModule();
    if(!module)
        return true;

    ProxyWidget *widget = loadModule(module);

    KCGlobal::repairAccels(topLevelWidget());
    return (widget != 0);
}