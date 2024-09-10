float G(const QVector3D& wi, const QVector3D& wo, const QVector3D& normal)
{
    using std::min;
    QVector3D wh = wi + wo;
    wh.normalize();
    return min(1.f, 2 * QVector3D::dotProduct(normal, wh) * min(QVector3D::dotProduct(normal, wo), QVector3D::dotProduct(normal, wi)) / QVector3D::dotProduct(wo, wh));
}