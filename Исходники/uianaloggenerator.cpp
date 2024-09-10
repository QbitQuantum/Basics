/*!
    Remove all analog signals associated with this widget.
*/
void UiAnalogGenerator::removeAllSignals()
{
    QList<QMdiSubWindow*> list = mWinArea->subWindowList();
    foreach(QMdiSubWindow* win, list) {
        closeWindow(win, true);
    }