void SatHorizon::render(QMatrix4x4 projection, float distance, QQuaternion quat, QVector3D posnorm, float alt, QColor rendercolor)
{

    float radius = sqrt( alt * alt - 1 ) / alt;

    float theta = acos(QVector3D::dotProduct(QVector3D(0,0,1), posnorm));
    QVector3D vecnorm = QVector3D::crossProduct(QVector3D(0,0,1), posnorm);
    vecnorm.normalize();

    createCircleBuffer(radius, SEGMENTS);

    QMatrix4x4 modelview;
    modelview.translate(0.0, 0.0, distance);
    modelview.rotate(quat);

    modelview.translate(posnorm * (1/alt) * (alt > 1.5 ? 1.0015 : 1.0001));
    modelview.rotate(theta * 180.0f/ PI, vecnorm );

    posBuf.bind();
    posBuf.write(0, vertexData, SEGMENTS * sizeof(QVector3D));
    posBuf.release();

    program->bind();

    program->setUniformValue("MVP", projection * modelview);
    QMatrix3x3 norm = modelview.normalMatrix();
    program->setUniformValue("NormalMatrix", norm);

    program->setUniformValue("outcolor", QVector4D(rendercolor.redF(), rendercolor.greenF(), rendercolor.blueF(), 1.0f));
    QOpenGLVertexArrayObject::Binder vaoBinder(&vao);
    glDrawArrays(GL_LINE_LOOP, 0, SEGMENTS);

}