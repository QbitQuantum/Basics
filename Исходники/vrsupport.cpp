_Use_decl_annotations_
void VRBeginEye(uint32_t eye, const XMFLOAT3& position, float yaw, D3D11_VIEWPORT* viewport, XMFLOAT4X4* view, XMFLOAT4X4* projection)
{
    g_CurrentEye = g_HMDDesc.EyeRenderOrder[eye];
    g_EyeRenderPose[g_CurrentEye] = ovrHmd_BeginEyeRender(g_HMD, g_CurrentEye);

    ovrQuatf orientation = g_EyeRenderPose[g_CurrentEye].Orientation;
    orientation.y *= -1;
    orientation.w *= -1;

    Matrix4f rollPitchYaw = Matrix4f::RotationY(yaw) * Matrix4f(orientation);
    Vector3f up = rollPitchYaw.Transform(Vector3f(0, 1, 0));
    Vector3f forward = rollPitchYaw.Transform(Vector3f(0, 0, 1));
    Vector3f shiftedEyePos = Vector3f(position.x, position.y, position.z) + rollPitchYaw.Transform(g_EyeRenderPose[g_CurrentEye].Position);

    Matrix4f theView = Matrix4f::LookAtRH(shiftedEyePos,
                                          shiftedEyePos + forward,
                                          up);

    theView =  Matrix4f::Translation(g_EyeRenderDesc[eye].ViewAdjust) * theView;
    XMStoreFloat4x4(view, XMMatrixTranspose(XMLoadFloat4x4((XMFLOAT4X4*)theView.M)));

    Matrix4f theProj = ovrMatrix4f_Projection(g_EyeRenderDesc[g_CurrentEye].Fov, 0.01f, 10000.0f, true);
    XMStoreFloat4x4(projection, XMMatrixTranspose(XMLoadFloat4x4((XMFLOAT4X4*)theProj.M)));

    viewport->TopLeftX = (float)g_EyeRenderViewport[g_CurrentEye].Pos.x;
    viewport->TopLeftY = (float)g_EyeRenderViewport[g_CurrentEye].Pos.y;
    viewport->Width = (float)g_EyeRenderViewport[g_CurrentEye].Size.w;
    viewport->Height = (float)g_EyeRenderViewport[g_CurrentEye].Size.h;
    viewport->MaxDepth = 1.0f;
}