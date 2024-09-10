/**
 * @brief LookAt Setup view matrix
 * @param eye Camera position
 * @param center Looking center
 * @param up Up vector
 * @return
 */
mat4 LookAt(vec3 eye, vec3 view, vec3 up)
{
    vec3 z_cam = view.normalized();
    vec3 x_cam = up.cross(z_cam).normalized();
    vec3 y_cam = z_cam.cross(x_cam);
    mat3 R = mat3::Zero();
    R.col(0) = x_cam;
    R.col(1) = y_cam;
    R.col(2) = z_cam;
    mat4 L = mat4::Zero();
    L.block(0, 0, 3, 3) =  R.transpose();
    L(3, 3) = 1.0f;
    L.block(0, 3, 3, 1) = -R.transpose() * (eye);
    return L;
}