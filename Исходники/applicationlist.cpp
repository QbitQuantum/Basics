bool ApplicationList::LoadSettings()
{
    QSettings settings;
    QStringList names = settings.value(SETTINGS_APPLICATION_NAMES, QStringList()).toStringList();
    QStringList paths = settings.value(SETTINGS_APPLICATION_PATHS, QStringList()).toStringList();
    QStringList params = settings.value(SETTINGS_APPLICATION_PARAMS, QStringList()).toStringList();
    int defapp = settings.value(SETTINGS_APPLICATION_DEFAULT, -1).toInt();

    // Params will be empty first time starting with the new setting.
    // Return false and inform user about problem with application settings.
    bool succeeded = true;
    if (!names.empty() && !paths.empty() && params.empty()) {
        for (int i = 0; i < paths.length(); i++)
            params << "";
        succeeded = false;
    }

    if (names.empty() && paths.empty() && params.empty()) {
        do {
            // use as default for gnome environments
            if (QFileInfo("/usr/bin/gedit").isExecutable()) {
                Application app;
                app.setName("gedit");
                app.setPath("/usr/bin/gedit");
                app.setParameters("+(line) (file)");
                AddApplication(app);
                defapp = 0;
                break;
            }
            // use as default for kde environments
            if (QFileInfo("/usr/bin/kate").isExecutable()) {
                Application app;
                app.setName("kate");
                app.setPath("/usr/bin/kate");
                app.setParameters("-l(line) (file)");
                AddApplication(app);
                defapp = 0;
                break;
            }
            if (FindDefaultWindowsEditor()) {
                defapp = 0;
                break;
            }
        } while (0);
    }

    if (names.size() > 0 && (names.size() == paths.size())) {
        for (int i = 0; i < names.size(); i++) {
            const Application app(names[i], paths[i], params[i]);
            AddApplication(app);
        }

        if (defapp == -1)
            mDefaultApplicationIndex = 0;
        else if (defapp < names.size())
            mDefaultApplicationIndex = defapp;
        else
            mDefaultApplicationIndex = 0;
    }
    return succeeded;
}