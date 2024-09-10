// createUnitBodyGreenChunks
//---------------------------------------------------------------------------
void ChunkTrajectoryParticle2D::createUnitBodyGreenChunks()
{

    // Blt the green titan body onto a surface to pull colors from.
    Surface tempUnitBodyGray;
    tempUnitBodyGray.create(gAbramsBody.getPixX(), gAbramsBody.getPixY(), gAbramsBody.getPixX(), 1);
    tempUnitBodyGray.fill(0);
    gAbramsBody.blt(tempUnitBodyGray, 0, 0);

    // Build a table of the green unit colors.
    Surface tempSurface(2, 2, 2, 64);

    int x = 0;
    int y = 0;

    for (int i = 0; i < tempSurface.getFrameCount(); i++) {
        tempSurface.setFrame(i);

        while (tempUnitBodyGray.getPixel(x, y) == 0) {
            x++;

            if (x > tempUnitBodyGray.getPixX() - 1) {
                x = 0;
                y++;
            } else if (y > tempUnitBodyGray.getPixY() - 1) {
                assert(false);
            }
        }

        tempSurface.fill(tempUnitBodyGray.getPixel(x, y));
    }

    PackedSurface tempPackedSurface;
    tempPackedSurface.pack(tempSurface);

    char chunkPathPAK[] = "pics/particles/chunks/pak/";
    char strBuf[256];
    sprintf(strBuf, "%sgreenUnitChunks.pak", chunkPathPAK);
    tempPackedSurface.save(strBuf);

} // end ChunkTrajectoryParticle2D::createUnitBodyGreenChunks