void plDistributor::IDistributeOverFace(int iFace, plDistribInstTab& reps, plMeshCacheTab& cache) const
{
    Point3 p0 = fSurfMesh->getVert(fSurfMesh->faces[iFace].getVert(0));
    Point3 p1 = fSurfMesh->getVert(fSurfMesh->faces[iFace].getVert(1));
    Point3 p2 = fSurfMesh->getVert(fSurfMesh->faces[iFace].getVert(2));

    Box3 grid = ISetupGrid(p0, p1, p2);

    float delta = fSpacing;

    float x, y, z;
    for( x = grid.Min().x; x < grid.Max().x; x += delta )
    {
        for( y = grid.Min().y; y < grid.Max().y; y += delta )
        {
            for( z = grid.Min().z; z < grid.Max().z; z += delta )
            {
                Point3 pt(x, y, z);

                pt = IPerturbPoint(pt);

                Point3 plnPt = pt;
                Point3 bary;

                // Get Barycentric coord of projection of grid pt onto face
                plTriUtils triUtil;
                plTriUtils::Bary baryVal = triUtil.ComputeBarycentricProjection(hsP3(p0), hsP3(p1), hsP3(p2), hsP3(plnPt), hsP3(bary));
                if( !(baryVal & (plTriUtils::kOutsideTri | plTriUtils::kDegenerateTri)) )
                {
                    int iRepNode = ISelectRepNode();

                    Matrix3 l2w = IGenerateTransform(iRepNode, iFace, plnPt, bary);

                    // l2w as ident means this position turned out to be not so good afterall.
                    if( l2w.IsIdentity() )
                    {
                        continue;
                    }

                    Box3 clearBox;
                    if( !ISpaceClear(iRepNode, l2w, clearBox, cache) )
                    {
                        continue;
                    }

                    int iCacheNode = iRepNode;
                    if( !IConform(l2w, iRepNode, cache, iCacheNode) )
                    {
                        continue;
                    }

                    // If |projGridPt - GridPt| < gridCubeRadius
                    // and probBitmap->GetPixel(src->UVW(bary)) < RandomZeroToOne()
                    // Also a generic random factor.
                    if( IProbablyDoIt(iFace, pt - plnPt, bary) )
                    {
                        IReplicate(l2w, iRepNode, reps, cache[iCacheNode]);

                        IReserveSpace(clearBox);
                    }
                }
            }
        }
    }
}