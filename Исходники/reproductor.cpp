bool Reproductor::eventFilter(QObject *obj, QEvent *event)
{
    Q_UNUSED(obj);
    if (event->type() == QEvent::MouseMove)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        mouseEvent->accept();
        if (Value == "Si")
        {
            ui->widget->show();
            Reproductor::setCursor(Qt::ArrowCursor);
            Contador->start(2000);
        }
    }
    if (event->type() == QEvent::KeyRelease)
    {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_F1)
        {
            ayuda = new Ayuda(this);
            ayuda->show();
            ayuda->Valor(tr("VideoDrake"));
            return true;
        }
    }
    return false;
}