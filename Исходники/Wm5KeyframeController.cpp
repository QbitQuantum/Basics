//----------------------------------------------------------------------------
HMatrix KeyframeController::GetRotate (float normTime, int i0, int i1)
{
    HQuaternion q;
    q.Slerp(normTime, mRotations[i0], mRotations[i1]);

    HMatrix rot;
    q.ToRotationMatrix(rot);
    return rot;
}