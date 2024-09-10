/*!
    Rotates \a vector with this quaternion to produce a new vector
    in 3D space.  The following code:

    \code
    QVector3D result = q.rotatedVector(vector);
    \endcode

    is equivalent to the following:

    \code
    QVector3D result = (q * QQuaternion(0, vector) * q.conjugate()).vector();
    \endcode
*/
QVector3D QQuaternion::rotatedVector(const QVector3D& vector) const
{
    return (*this * QQuaternion(0, vector) * conjugate()).vector();
}