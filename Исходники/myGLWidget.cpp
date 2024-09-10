void MyGLWidget::keyPressEvent(QKeyEvent *event)
{

    GLfloat   cameraSpeed = 1.0f ;
    QVector3D cross ;

    bool      changedFront = false ;
    switch ( event->key()) {
        case Qt::Key_W     : cameraPos += cameraSpeed * cameraFront ;
             break ;
        case Qt:: Key_S    : cameraPos -= cameraSpeed * cameraFront ;
             break ;
        case Qt::Key_A     : cross = cross.crossProduct(cameraFront , cameraUp) ;
                             cross.normalize();
                             cameraPos -= cross * cameraSpeed ;
             break ;
        case Qt::Key_D     : cross = cross.crossProduct(cameraFront , cameraUp) ;
                             cross.normalize();
                             cameraPos += cross * cameraSpeed ;
             break ;
        case Qt::Key_Up    : pitch += 1 ;
                             changedFront = true ;
             break ;
        case Qt::Key_Down  : pitch -= 1 ;
                             changedFront = true ;
             break ;
        case Qt::Key_Left  : yaw -= 1 ;
                             changedFront = true ;
             break ;
        case Qt::Key_Right : yaw += 1 ;
                             changedFront = true ;
             break ;
        case Qt::Key_P     : paused = !paused ;
             break ;
        case Qt::Key_R     : cameraPos = QVector3D(0.0f, 0.0f, 3.0f);
                             cameraFront = QVector3D(0.0f, 0.0f, -1.0f);
                             cameraUp = QVector3D(0.0f, 1.0f, 0.0f);
             break ;
        default : QGLWidget::keyPressEvent(event) ;
    }

    if (changedFront)
    {
    QVector3D front;
        front.setX ( cos(pitch*(M_PI/180)) * cos(yaw*(M_PI/180)) );
        front.setY ( sin(pitch*(M_PI/180) )  );
        front.setZ ( cos(pitch*(M_PI/180)) * sin(yaw*(M_PI/180)) );
        front.normalize();
        cameraFront = front ;
    }

}