void AbcWriteJob::perFrameCallback(double iFrame)
{
    MBoundingBox bbox;

    util::ShapeSet::iterator it = mArgs.dagPaths.begin();
    const util::ShapeSet::iterator end = mArgs.dagPaths.end();
    for (; it != end; it ++)
    {
        mCurDag = *it;

        MMatrix eMInvMat;
        if (mArgs.worldSpace)
        {
            eMInvMat.setToIdentity();
        }
        else
        {
            eMInvMat = mCurDag.exclusiveMatrixInverse();
        }

        bbox.expand(getBoundingBox(iFrame, eMInvMat));
    }

    Alembic::Abc::V3d min(bbox.min().x, bbox.min().y, bbox.min().z);
    Alembic::Abc::V3d max(bbox.max().x, bbox.max().y, bbox.max().z);
    Alembic::Abc::Box3d b(min, max);
    mBoxProp.set(b);

    processCallback(mArgs.melPerFrameCallback, true, iFrame, bbox);
    processCallback(mArgs.pythonPerFrameCallback, false, iFrame, bbox);
}