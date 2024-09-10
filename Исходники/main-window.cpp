// handle osx's applicationShouldHandleReopen
// QTBUG-10899 OS X: Add support for ApplicationState capability
void MainWindow::checkShowWindow()
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 2, 0))
    if (qApp->applicationState() & Qt::ApplicationActive)
        showWindow();
#endif
}