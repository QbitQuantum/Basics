void CompleteBoxPruningTest::Init()
{
    m_firstTime = true;

    SRand(0);
    mBoxes = new AABB[mNbBoxes];
    mBoxPtrs = new const AABB*[mNbBoxes];
    mBoxTime = new float[mNbBoxes];
    for(udword i=0; i<mNbBoxes; i++)
    {
        Point Center, Extents;

        Center.x = (UnitRandomFloat()-0.5f) * 100.0f;
        Center.y = (UnitRandomFloat()-0.5f) * 10.0f;
        Center.z = (UnitRandomFloat()-0.5f) * 100.0f;
        Extents.x = 2.0f + UnitRandomFloat() * 2.0f;
        Extents.y = 2.0f + UnitRandomFloat() * 2.0f;
        Extents.z = 2.0f + UnitRandomFloat() * 2.0f;

        mBoxes[i].SetCenterExtents(Center, Extents);
        mBoxPtrs[i] = &mBoxes[i];

        mBoxTime[i] = 2000.0f*UnitRandomFloat();
    }
}