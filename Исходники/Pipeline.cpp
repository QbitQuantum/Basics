void Pipeline::InitCameraTransfrom(Matrix4f& CameraTrans,Matrix4f& CameraRot)
{
    CameraTrans.mat[0][0] = 1.0f;CameraTrans.mat[0][1] = 0.0f;CameraTrans.mat[0][2] = 0.0f;CameraTrans.mat[0][3] = -m_camera.Pos.x;
    CameraTrans.mat[1][0] = 0.0f;CameraTrans.mat[1][1] = 1.0f;CameraTrans.mat[1][2] = 0.0f;CameraTrans.mat[1][3] = -m_camera.Pos.y;
    CameraTrans.mat[2][0] = 0.0f;CameraTrans.mat[2][1] = 0.0f;CameraTrans.mat[2][2] = 1.0f;CameraTrans.mat[2][3] = -m_camera.Pos.z;
    CameraTrans.mat[3][0] = 0.0f;CameraTrans.mat[3][1] = 0.0f;CameraTrans.mat[3][2] = 0.0f;CameraTrans.mat[3][3] = 1.0f;

    Vector3f N = m_camera.Target;
    N.Normalize();
    Vector3f U = m_camera.Up;
    U.Normalize();
    U = U.Cross(N);
    Vector3f V = N.Cross(U);

    CameraRot.mat[0][0] = U.x;CameraRot.mat[0][1] = U.y;CameraRot.mat[0][2] = U.z;CameraRot.mat[0][3] = 0.0f;
    CameraRot.mat[1][0] = V.x;CameraRot.mat[1][1] = V.y;CameraRot.mat[1][2] = V.z;CameraRot.mat[1][3] = 0.0f;
    CameraRot.mat[2][0] = N.x;CameraRot.mat[2][1] = N.y;CameraRot.mat[2][2] = N.z;CameraRot.mat[2][3] = 0.0f;
    CameraRot.mat[3][0] = 0.0f;CameraRot.mat[3][1] = 0.0f;CameraRot.mat[3][2] = 0.0f;CameraRot.mat[3][3] = 1.0f;
}