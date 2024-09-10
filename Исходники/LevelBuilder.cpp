void LevelBuilder::CreateBoundingBox()
{


    //
    // Compute scene bounding box.
    //
    XMFLOAT3 minPt(+MathHelper::Infinity, +MathHelper::Infinity, +MathHelper::Infinity);
    XMFLOAT3 maxPt(-MathHelper::Infinity, -MathHelper::Infinity, -MathHelper::Infinity);



    for (UINT i = 0; i < mLevelPartsInstances.size(); ++i)
    {
        minPt.x = 0.0f;
        minPt.y = 0.0f;
        minPt.z = 0.0f;

        maxPt.x = 0.0f;
        maxPt.y = 0.0f;
        maxPt.z = 0.0f;

        for (UINT j = 0; j < mLevelPartsInstances[i].Model->BasicVertices.size(); ++j)
        {

            XMFLOAT3 P = mLevelPartsInstances[i].Model->BasicVertices[j].Pos;




            minPt.x = MathHelper::Min(minPt.x, P.x);
            minPt.y = MathHelper::Min(minPt.y, P.y);
            minPt.z = MathHelper::Min(minPt.z, P.z);

            maxPt.x = MathHelper::Max(maxPt.x, P.x);
            maxPt.y = MathHelper::Max(maxPt.y, P.y);
            maxPt.z = MathHelper::Max(maxPt.z, P.z);


        }

        XMMATRIX temp = XMLoadFloat4x4(&mLevelPartsInstances[i].World);

        LevelPartsclass[i]->setWorld(mLevelPartsInstances[i].World);

        XMVECTOR Scale;
        XMVECTOR Position;
        XMVECTOR Rotation;


        XMMatrixDecompose(&Scale, &Rotation, &Position, temp);

        XMFLOAT3 tempPos;
        XMStoreFloat3(&tempPos, Position);

        LevelCollisions[i].Center = tempPos;


        LevelCollisions[i].Extents = XMFLOAT3(0.5f*(maxPt.x - minPt.x),
                                              0.5f*(maxPt.y - minPt.y),
                                              0.5f*(maxPt.z - minPt.z));

        LevelCollisions[i].collisionType = LevelPartsclass[i]->getCollisionType();

        // sets the scale of the collision box
        int scale = LevelPartsclass[i]->getScale();

        LevelCollisions[i].Extents.x = LevelCollisions[i].Extents.x * scale;
        LevelCollisions[i].Extents.y = LevelCollisions[i].Extents.y * scale;
        LevelCollisions[i].Extents.z = LevelCollisions[i].Extents.z * scale;

        if (LevelPartsclass[i]->getRotationY() != 0)
        {
            FLOAT tempX = LevelCollisions[i].Extents.x;
            FLOAT tempZ = LevelCollisions[i].Extents.z;

            LevelCollisions[i].Extents.x = tempZ;
            LevelCollisions[i].Extents.z = tempX;

        }


        //// this doesn't work, useless atm
        //LevelPartsBox[i]->setCollisionType();


        LevelPartsclass[i]->setAABB(&LevelCollisions[i]);

    }
}