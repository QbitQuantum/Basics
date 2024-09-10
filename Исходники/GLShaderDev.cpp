GLShaderDev::GLShaderDev(const QStringList& args)
:   _editor(new CodeEditor(this)),
    _output(new BuildOutput(this)),
    _glInfoDialog(nullptr),
    _newFileDialog(new NewFileDialog(this))
{
    resize(1000, 800); // FIXME set sizeHint instead of hardcoding it
    setWindowIcon(QIcon(":/glsd-icon.png"));
    setCentralWidget(_editor);

    initializeContext();
    initializeActions();
    initializeDockWidgets();

    loadSettings();
    updateTitleBar();

    for (int i = 0; i < args.size(); ++i)
        openFile(args.at(i));
}