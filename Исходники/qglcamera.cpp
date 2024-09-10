/*!
    Returns the transformation to apply to the modelview matrix
    to present the scene as viewed from the eye position.

    The \a eye parameter is used to adjust the camera's position
    horizontally by half of eyeSeparation() if \a eye is QGL::LeftEye
    or QGL::RightEye.

    \sa projectionMatrix()
*/
QMatrix4x4 QGLCamera::modelViewMatrix(QGL::Eye eye) const
{
    Q_D(const QGLCamera);
    QMatrix4x4 m;
    QVector3D adjust;
    if (eye == QGL::LeftEye)
        adjust = translation(-d->eyeSeparation / 2.0f, 0.0f, 0.0f);
    else if (eye == QGL::RightEye)
        adjust = translation(d->eyeSeparation / 2.0f, 0.0f, 0.0f);
    if (d->motionQuaternion.isIdentity()) {
        m.lookAt(d->eye + adjust, d->center, d->upVector);
    } else {
        QVector3D up = d->motionQuaternion.rotatedVector(d->upVector);
        QVector3D view = d->motionQuaternion.rotatedVector(d->viewVector);
        m.lookAt(d->center - view + adjust, d->center, up);
    }
    return m;
}