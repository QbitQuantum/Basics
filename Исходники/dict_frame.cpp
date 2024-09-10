void DictFrame::keyReleaseEvent(QKeyEvent *ke)
{
    QWidget * wnd = 0;
    QPushButton * btn = 0;
    int key = ke->key();
    if (key == Qt::Key_Escape || key == ui::Device_Menu_Key)
    {
        ke->accept();
        onCloseClicked();
        return;
    }

    if (internalState() == LOOKUP)
    {
        emit keyReleaseSignal(ke->key());
        return;
    }

    ke->accept();
    switch (ke->key())
    {
    case Qt::Key_Up:
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Down:
        wnd = ui::moveFocus(this, key);
        if (wnd)
        {
            wnd->setFocus();
        }
        break;
    default:
        break;
    }
}