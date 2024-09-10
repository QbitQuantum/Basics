static void readAndDeleteLegacyCMakeSettings ()
{
    // restore the legacy cmake
    QSettings *settings = ICore::settings();
    settings->beginGroup(QLatin1String("CMakeSettings"));

    FileName exec = FileName::fromUserInput(settings->value(QLatin1String("cmakeExecutable")).toString());
    if (exec.toFileInfo().isExecutable()) {
        CMakeTool *item = CMakeToolManager::findByCommand(exec);
        if (!item) {
            item = new CMakeTool(CMakeTool::ManualDetection);
            item->setCMakeExecutable(exec);
            item->setDisplayName(CMakeToolManager::tr("CMake at %1").arg(item->cmakeExecutable().toUserOutput()));

            if (!CMakeToolManager::registerCMakeTool(item)) {
                delete item;
                item = 0;
            }
        }

        //this setting used to be the default cmake, make sure it is again
        if (item)
            d->m_defaultCMake = item->id();
    }

    //read the legacy ninja setting, if its not available use the current value
    d->m_preferNinja = settings->value(QLatin1String("preferNinja"), d->m_preferNinja).toBool();

    settings->remove(QString());
    settings->endGroup();
}