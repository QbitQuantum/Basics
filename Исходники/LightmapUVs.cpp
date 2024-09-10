    void RebuildStorageBlocks(bool bSpecificArea=false, StorageData *rebuildArea=NULL)
    {
        int startX = 0, startY = 0, endX = seperationUnits, endY = seperationUnits;
        if(!bSpecificArea)
        {
            StorageBlocks.ClearAll();
            storageBlockSize = curSize/float(seperationUnits);
            storageBlockSizeI = 1.0f/storageBlockSize;

            availableOffsetBlocks = (curSize.x > curSize.y) ? int(curSize.x*storageBlockSizeI.y) : int(curSize.y*storageBlockSizeI.x);
            availableOffsetBlocks -= seperationUnits;
        }
        else
        {
            UVSection &section = Sections[rebuildArea->item];

            Vect2 max;
            if(rebuildArea->bRot)   max.Set(rebuildArea->pos.x+section.height, rebuildArea->pos.y+section.width);
            else                    max.Set(rebuildArea->pos.x+section.width,  rebuildArea->pos.y+section.height);

            PosToBlock(rebuildArea->pos, startX, startY);
            PosToBlock(max, endX, endY, true);
        }

        for(int y=startY; y<endY; y++)
        {
            DWORD yPos = y*seperationUnits;
            for(int x=startX; x<endX; x++)
            {
                DWORD blockPos = yPos+x;

                //doing a 5-point check to speed things up rather than a full box/tri intersection
                Vect2 checkPoints[2];
                checkPoints[0].Set(float(x)*storageBlockSize.x, float(y)*storageBlockSize.y);
                checkPoints[1] = checkPoints[0]+storageBlockSize;

                for(int i=0; i<CurStorage.Num(); i++)
                {
                    StorageData &data = CurStorage[i];
                    UVSection &section = Sections[data.item];

                    Vect2 max;
                    if(data.bRot)   max.Set(data.pos.x+section.height, data.pos.y+section.width);
                    else            max.Set(data.pos.x+section.width,  data.pos.y+section.height);

                    if( checkPoints[0].x > max.x || data.pos.x > checkPoints[1].x ||
                        checkPoints[0].y > max.y || data.pos.y > checkPoints[1].y )
                    {
                        continue;
                    }

                    int numTris = section.Verts.Num()/3;

                    bool bFoundBlocker = false;

                    for(int j=0; j<numTris; j++)
                    {
                        int startVert = j*3;
                        Vect2 vPos1 = section.ProjectedVerts[startVert];
                        Vect2 vPos2 = section.ProjectedVerts[startVert+1];
                        Vect2 vPos3 = section.ProjectedVerts[startVert+2];

                        if(data.bRot)
                        {
                            vPos1.SwapVals();
                            vPos2.SwapVals();
                            vPos3.SwapVals();

                            vPos1.x = section.height-vPos1.x;
                            vPos2.x = section.height-vPos2.x;
                            vPos3.x = section.height-vPos3.x;
                        }

                        vPos1 += data.pos;
                        vPos2 += data.pos;
                        vPos3 += data.pos;

                        if( LineCheckForBoxOnIsle2(checkPoints[0], checkPoints[1], vPos1, vPos2) ||
                            LineCheckForBoxOnIsle2(checkPoints[0], checkPoints[1], vPos2, vPos3) ||
                            LineCheckForBoxOnIsle2(checkPoints[0], checkPoints[1], vPos3, vPos1) )
                        {
                            StorageBlocks.Set(blockPos);
                            bFoundBlocker = true;
                            break;
                        }

                        Vect2 norm1 = (vPos1-checkPoints[0]).Norm();
                        Vect2 norm2 = (vPos2-checkPoints[0]).Norm();
                        Vect2 norm3 = (vPos3-checkPoints[0]).Norm();
                        float checkVal = acosf(norm1.Dot(norm2)) +
                                         acosf(norm2.Dot(norm3)) +
                                         acosf(norm3.Dot(norm1));

                        if(fabsf(checkVal-(M_PI*2.0f)) < 0.01f)
                        {
                            StorageBlocks.Set(blockPos);
                            bFoundBlocker = true;
                            break;
                        }
                    }

                    if(bFoundBlocker)
                        break;
                }
            }
        }

        /*String fileName;
        fileName << TEXT("floong") << IntString(storageBlockRebuildCount) << TEXT(".txt");
        XFile wong(fileName, XFILE_WRITE, XFILE_CREATEALWAYS);
        for(int y=0; y<seperationUnits; y++)
        {
            DWORD yPos = y*seperationUnits;
            for(int x=0; x<seperationUnits; x++)
            {
                wong.WriteAsUTF8(IntString(StorageBlocks[yPos+x] != 0));
            }

            wong.WriteAsUTF8(TEXT("\r\n"));
        }
        ++storageBlockRebuildCount;*/
    }