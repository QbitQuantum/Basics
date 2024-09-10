//----------------------------------------------------------------------------
void Culler::SetFrustum (const float* frustum)
{
    if (!mCamera)
    {
        assertion(false, "SetFrustum requires the existence of a camera\n");
        return;
    }

    // Copy the frustum values.
    mFrustum[Camera::VF_DMIN] = frustum[Camera::VF_DMIN];
    mFrustum[Camera::VF_DMAX] = frustum[Camera::VF_DMAX];
    mFrustum[Camera::VF_UMIN] = frustum[Camera::VF_UMIN];
    mFrustum[Camera::VF_UMAX] = frustum[Camera::VF_UMAX];
    mFrustum[Camera::VF_RMIN] = frustum[Camera::VF_RMIN];
    mFrustum[Camera::VF_RMAX] = frustum[Camera::VF_RMAX];

    float dMin2 = mFrustum[Camera::VF_DMIN]*mFrustum[Camera::VF_DMIN];
    float uMin2 = mFrustum[Camera::VF_UMIN]*mFrustum[Camera::VF_UMIN];
    float uMax2 = mFrustum[Camera::VF_UMAX]*mFrustum[Camera::VF_UMAX];
    float rMin2 = mFrustum[Camera::VF_RMIN]*mFrustum[Camera::VF_RMIN];
    float rMax2 = mFrustum[Camera::VF_RMAX]*mFrustum[Camera::VF_RMAX];

    // Get the camera coordinate frame.
    APoint position = mCamera->GetPosition();
    AVector dVector = mCamera->GetDVector();
    AVector uVector = mCamera->GetUVector();
    AVector rVector = mCamera->GetRVector();
    float dirDotEye = position.Dot(dVector);

    // Update the near plane.
    mPlane[Camera::VF_DMIN].SetNormal(dVector);
    mPlane[Camera::VF_DMIN].SetConstant(
        dirDotEye + mFrustum[Camera::VF_DMIN]);

    // Update the far plane.
    mPlane[Camera::VF_DMAX].SetNormal(-dVector);
    mPlane[Camera::VF_DMAX].SetConstant(
        -(dirDotEye + mFrustum[Camera::VF_DMAX]));

    // Update the bottom plane
    float invLength = Mathf::InvSqrt(dMin2 + uMin2);
    float c0 = -mFrustum[Camera::VF_UMIN]*invLength;  // D component
    float c1 = +mFrustum[Camera::VF_DMIN]*invLength;  // U component
    AVector normal = c0*dVector + c1*uVector;
    float constant = position.Dot(normal);
    mPlane[Camera::VF_UMIN].SetNormal(normal);
    mPlane[Camera::VF_UMIN].SetConstant(constant);

    // Update the top plane.
    invLength = Mathf::InvSqrt(dMin2 + uMax2);
    c0 = +mFrustum[Camera::VF_UMAX]*invLength;  // D component
    c1 = -mFrustum[Camera::VF_DMIN]*invLength;  // U component
    normal = c0*dVector + c1*uVector;
    constant = position.Dot(normal);
    mPlane[Camera::VF_UMAX].SetNormal(normal);
    mPlane[Camera::VF_UMAX].SetConstant(constant);

    // Update the left plane.
    invLength = Mathf::InvSqrt(dMin2 + rMin2);
    c0 = -mFrustum[Camera::VF_RMIN]*invLength;  // D component
    c1 = +mFrustum[Camera::VF_DMIN]*invLength;  // R component
    normal = c0*dVector + c1*rVector;
    constant = position.Dot(normal);
    mPlane[Camera::VF_RMIN].SetNormal(normal);
    mPlane[Camera::VF_RMIN].SetConstant(constant);

    // Update the right plane.
    invLength = Mathf::InvSqrt(dMin2 + rMax2);
    c0 = +mFrustum[Camera::VF_RMAX]*invLength;  // D component
    c1 = -mFrustum[Camera::VF_DMIN]*invLength;  // R component
    normal = c0*dVector + c1*rVector;
    constant = position.Dot(normal);
    mPlane[Camera::VF_RMAX].SetNormal(normal);
    mPlane[Camera::VF_RMAX].SetConstant(constant);

    // All planes are active initially.
    mPlaneState = 0xFFFFFFFF;
}