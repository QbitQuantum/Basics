void SettingsDialog::keyReleaseEvent(QKeyEvent *ke)
{
    QWidget *wnd = 0;
    ke->accept();
    switch (ke->key())
    {
    case Qt::Key_Up:
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Down:
    case Qt::Key_PageDown:
    case Qt::Key_PageUp:
        wnd = ui::moveFocus(&content_widget_, ke->key());
        if (wnd)
        {
            wnd->setFocus();
        }
        break;
    case Qt::Key_Return:
        break;
    case Qt::Key_Escape:
        reject();
        break;
    }
}