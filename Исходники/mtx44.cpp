void Mtx44::lookat(const Vec3& eye, const Vec3& target, const Vec3& up)
{
    /*
      [note] z軸はカメラ位置から視線方向へのベクトル。
       x軸はz軸と上方向に垂直なので両者の外積。
       y軸はz軸とx軸に垂直なので両者の外積。
       平行移動成分は各軸に対してカメラ位置に合うように移動。
    */
    Vec3 zaxis = (eye - target).getNormalized();
    Vec3 xaxis = up.getCrossed(zaxis).getNormalized();
    Vec3 yaxis = zaxis.getCrossed(xaxis);
    setRow(0, xaxis.x, yaxis.x, zaxis.x, 0);
    setRow(1, xaxis.y, yaxis.y, zaxis.y, 0);
    setRow(2, xaxis.z, yaxis.z, zaxis.z, 0);
    setRow(3, -xaxis.dot(eye), -yaxis.dot(eye), -zaxis.dot(eye), 1);
}