CCGUI::
CCGUI(
    QWidget        *pParent /* = 0 */,
    Qt::WFlags      Flags /* = 0 */
) :
    QMainWindow(pParent, Flags)
{
    LOGFONTW lf;

    ui.setupUi(this);

    setWindowTitle(QString::fromUtf16(L"ÐÇ³½Ö®¼ä"));

    SystemParametersInfoW(SPI_GETICONTITLELOGFONT, sizeof(lf), &lf, 0);
    QFont font(QApplication::font());

    font.setWeight(QFont::Normal);
    font.setStyleStrategy(QFont::PreferQuality);
    font.setFamily(QString::fromUtf16(lf.lfFaceName));

    QApplication::setFont(font);

    AllocConsole();

    BOOL b;

    connect(ui.actionFileExit, SIGNAL(triggered()), this, SLOT(close()));
    b = connect(ui.MenuAbout, SIGNAL(aboutToShow()), this, SLOT(About()));

    PrintConsoleW(L"%d\n", b);
}