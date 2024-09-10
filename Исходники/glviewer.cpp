void GLViewer::mousePressEvent(QMouseEvent * event) {
    const WindowModel *windowModel = controller->getWindowModel();
    if (windowModel->isDragEnabled()) {
        float fov, ar;
        float screenWidth;
        float screenHeight;
        Vec3Df camPos;
        Vec3Df viewDirection;
        Vec3Df upVector;
        Vec3Df rightVector;
        getCameraInformation(fov, ar, screenWidth, screenHeight, camPos, viewDirection, upVector, rightVector);
        float tanX = tan(fov)*ar;
        float tanY = tan(fov);
        Vec3Df stepX = (float (event->x()) - screenWidth/2.f)/screenWidth * tanX * rightVector;
        Vec3Df stepY = (float (screenHeight-event->y()) - screenHeight/2.f)/screenHeight * tanY * upVector;
        Vec3Df step = stepX + stepY;
        Vec3Df dir = viewDirection + step;
        float distanceCameraScreen = dir.getLength();
        dir.normalize();
        Ray ray;
        if (controller->getRayTracer()->intersect(dir, camPos, ray)) {
            Object *o=ray.getIntersectedObject();
            QPoint p = event->globalPos();
            Vec3Df oPos = o->getTrans();
            float ratio = distanceCameraScreen/sqrt(ray.getIntersectionDistance());
            controller->viewerStartsDragging(o, oPos, p, ratio);
        }
    }
    if (!controller->getWindowModel()->isRealTime()) {
        controller->viewerSetDisplayMode(WindowModel::OpenGLDisplayMode);
    }
    else {
        controller->forceThreadUpdate();
    }
    QGLViewer::mousePressEvent(event);
}