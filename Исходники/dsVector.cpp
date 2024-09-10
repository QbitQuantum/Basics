// 输入 点相对于球心的球坐标 和 球心的直角坐标，输出 点的直角坐标 GLdouble
void dsSphereToOrtho3dv(
    const GLdouble sphere[3],
    const GLdouble center[3],
    GLdouble ortho[3]
) {
    ortho[0] = center[0] + sphere[0] * sin(sphere[1]) * cos(sphere[2]);
    ortho[1] = center[1] + sphere[0] * sin(sphere[1]) * sin(sphere[2]);
    ortho[2] = center[2] + sphere[0] * cos(sphere[1]);
}