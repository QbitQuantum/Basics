/*
Extract height and slope data from given square and make
a sub-functional call for calculations upon whose data.
*/
float CMoveMath::SpeedMod(const MoveData& moveData, int xSquare, int zSquare,const float3& moveDir) {
    //Error-check
    if(xSquare < 0 || zSquare < 0
            || xSquare >= gs->mapx || zSquare >= gs->mapy)
        return 0.0f;

    //Extract data.
    int square = xSquare/2 + zSquare/2 * gs->hmapx;
    float height = readmap->halfHeightmap[square];
    float slope = readmap->slopemap[square];

    float3 flatNorm=readmap->facenormals[(xSquare + zSquare * gs->mapx)*2];
    flatNorm.y=0;
    flatNorm.Normalize();
    float moveSlope=-moveDir.dot(flatNorm);
    float typemod=moveinfo->terrainType2MoveFamilySpeed[readmap->typemap[square]][moveData.moveFamily];

    //Call calculations.
    return SpeedMod(moveData, height, slope,moveSlope)*typemod;
}