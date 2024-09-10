QVector3D cube::getCameraVector(PointDDD& polyPoint)
{
    PointDDD cameraPos;
    cameraPos.setX(SCREENDIST * sin(m_omega) * cos(m_phi));
    cameraPos.setY(SCREENDIST * sin(m_omega) * sin(m_phi));
    cameraPos.setZ(SCREENDIST * cos(m_omega));
    QVector3D res = createVectorByPoint(polyPoint,cameraPos);
    res.normalize();
    return res;
}