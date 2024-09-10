void MpdClientDialog::keyReleaseEvent(QKeyEvent *ke)
{
    switch(ke->key())
    {
    case Qt::Key_Left:
    case Qt::Key_Right:
    {
        QWidget *wnd = ui::moveFocus(&button_widget_, ke->key());
        if (wnd)
        {
            wnd->setFocus();
            onyx::screen::instance().flush();
            onyx::screen::instance().updateWidget(&button_widget_, onyx::screen::ScreenProxy::DW, false);
        }
        break;
    }
    case Qt::Key_Escape:
        done();
        break;
    case Qt::Key_Return:
    case Qt::Key_PageDown:
    case Qt::Key_PageUp:
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Menu:
    default:
        break;
    }
}