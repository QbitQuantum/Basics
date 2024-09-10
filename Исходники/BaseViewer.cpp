bool BaseViewer::navigationOnKeys(QEvent *e)
{
    if (e->type() == QEvent::KeyPress)
    {
        QKeyEvent * event = static_cast<QKeyEvent*>(e);
        QPointF sceneCenter = getVisibleSceneRect().center();
        double step = 15.0;
        if (event->key() == Qt::Key_Right)
        {
            sceneCenter += QPointF(step,0.0);
        }
        else if (event->key() == Qt::Key_Left)
        {
            sceneCenter -= QPointF(step,0.0);
        }
        else if (event->key() == Qt::Key_Up)
        {
            sceneCenter -= QPointF(0.0,step);
        }
        else if (event->key() == Qt::Key_Down)
        {
            sceneCenter += QPointF(0.0,step);
        }
        else
        {
            return false;
        }

        centerOnAtZoom(_zoomLevel, sceneCenter);
        event->accept();
        return true;
    }
    return false;
}