//----------------------------------------------------------------------------
void ClodMeshes::UpdateClods ()
{
    // Adjust the triangle quantities for the clod meshes.  The distance along
    // the camera direction controls the triangle quantities.  A nonlinear
    // drop-off is used.
    for (int i = 0; i < 2; ++i)
    {
        AVector diff =
            mClod[i]->WorldBound.GetCenter() - mCamera->GetPosition();

        float depth = diff.Dot(mCamera->GetDVector());
        int targetRecord;
        if (depth <= mCamera->GetDMin())
        {
            targetRecord = 0;
        }
        else if (depth >= mCamera->GetDMax())
        {
            targetRecord = mClod[i]->GetNumRecords() - 1;
        }
        else
        {
            float dmin = mCamera->GetDMin();
            float dmax = mCamera->GetDMax();
            float ratio = Mathf::Pow((depth - dmin)/(dmax - dmin), 0.5f);
            targetRecord = (int)((mClod[i]->GetNumRecords() - 1)*ratio);
        }

        mClod[i]->TargetRecord() = targetRecord;
    }
}