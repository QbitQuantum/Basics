void sreLookAt(float viewpx, float viewpy, float viewpz, float lookx, float looky, float lookz,
float upx, float upy, float upz) {
    Vector3D F = Vector3D(lookx, looky, lookz) - Vector3D(viewpx, viewpy, viewpz);
    Vector3D Up = Vector3D(upx, upy, upz);
    Vector3D f = F.Normalize();
    sre_internal_camera_vector = f;
    Up.Normalize();
    sre_internal_up_vector = Up;
    Vector3D s = Cross(f, Up);
    Vector3D u = Cross(s, f);
    MatrixTransform M;
    M.Set(
        s.x, s.y, s.z, 0.0f,
        u.x, u.y, u.z, 0.0f,
        - f.x, - f.y, - f.z, 0.0f);
    MatrixTransform T;
    T.AssignTranslation(Vector3D(- viewpx, - viewpy, -viewpz));
    sre_internal_view_matrix = M * T;
    sre_internal_view_projection_matrix = sre_internal_projection_matrix * sre_internal_view_matrix;
//    printf("View-projection matrix:\n");
//    for (int row = 0; row < 4; row++)
//        for (int column = 0; column < 4; column++)
//            printf("%f, ", sre_internal_view_projection_matrix(row, column));
//    printf("\n");
}