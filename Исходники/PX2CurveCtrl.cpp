//----------------------------------------------------------------------------
void CurveCtrlFloat::OnCtrlChanged (bool updateCurve)
{
    if (mIndex >= (int)(mCurveFloat->mCurve->Points.size()))
        return;

    float inVal = mCurveFloat->mCurve->Points[mIndex].InVal;
    float outVal = mCurveFloat->mCurve->Points[mIndex].OutVal;
    float arriveTangent = mCurveFloat->mCurve->Points[mIndex].ArriveTangent;
    float leaveTangent = mCurveFloat->mCurve->Points[mIndex].LeaveTangent;
    InterpCurveMode mode = mCurveFloat->mCurve->Points[mIndex].InterpMode;

    mInVal = inVal;
    mOutVal = Float3(inVal, 0.0f, outVal);

    AVector at(1.0f, 0.0f, arriveTangent);
    at.Normalize();
    mArriveTangent = at;

    AVector lt (1.0f, 0.0f, leaveTangent);
    lt.Normalize();
    mLeaveTangent = lt;

    mInterpCurveMode = mode;

    CurveCtrl::OnCtrlChanged(updateCurve);
}