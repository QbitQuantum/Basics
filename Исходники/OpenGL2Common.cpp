void OpenGL2Common::mousePress(QMouseEvent *e)
{
    if (e->buttons() & Qt::LeftButton)
    {
        moveVideo = (e->modifiers() & Qt::ShiftModifier);
        moveOSD = (e->modifiers() & Qt::ControlModifier);
        if (moveVideo || moveOSD)
        {
            QWidget *w = widget();
            w->setProperty("customCursor", (int)Qt::ArrowCursor);
            w->setCursor(Qt::ClosedHandCursor);
            mousePos = e->pos();
        }
    }
}