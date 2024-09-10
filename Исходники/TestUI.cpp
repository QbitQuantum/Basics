QWidget* createTerminalWidget(QWidget* parent = 0)
{
    KPluginFactory* factory = KPluginLoader("libkonsolepart").factory();
    KParts::ReadOnlyPart* part = factory ? (factory->create<KParts::ReadOnlyPart>(parent)) : 0;

    if (!part) {
        printf("Failed to initialize part\n");
        return 0;
    }

    TerminalInterface* terminal = qobject_cast<TerminalInterface*>(part);
    if (!terminal) {
        printf("Failed to initialize terminal\n");
        return 0;
    }

    terminal->showShellInDir(KUrl().path());
    terminal->sendInput("cd " + KShell::quoteArg(KUrl().path()) + '\n');
    terminal->sendInput("clear\n");
    return part->widget();
}