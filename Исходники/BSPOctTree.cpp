void BSPOctree::PerformBoolean(PolygonPtrList& mesh1, PolygonPtrList& mesh2, const Box3& bbox, OctTreeNode** node)
{
    FixedPlane bounds[] = {FixedPlane(double3(1,0,0),-bbox.Min().x)
                            , FixedPlane(double3(-1,0,0),bbox.Max().x)
                            , FixedPlane(double3(0,1,0),-bbox.Min().y)
                            , FixedPlane(double3(0,-1,0),bbox.Max().y)
                            , FixedPlane(double3(0,0,1),-bbox.Min().z)
                            , FixedPlane(double3(0,0,-1),bbox.Max().z)};

    FixedPlaneMesh myMesh1, myMesh2;
    FixedPlanePolygon poly;
    std::list<FixedPlanePolygon*> polyPool;

    // for containment test, jxd
    OctLeafNode* pLeaf = new OctLeafNode;
    pLeaf->bbox = bbox;
    // end

    for (auto index: mesh1)
    {
        MeshData *data = &(mMesh1[index]);
        /// convert simple mesh into plane based mesh
        if (!data->bSplitted)
        {
            data->bSplitted = true;
            data->OrigPolygon = FixedPlanePolygon(data->Position[0],
                data->Position[1], data->Position[2]);
            FixedPlanePolygon *root = new FixedPlanePolygon(data->OrigPolygon);
            data->Fragments.push_back(root);
        }

        // get the inside polygons: myMesh1
        poly = data->OrigPolygon;
        bool bNeedInsert = true;
        for (int i = 0; i < 6; i++)
        {
            poly.ClipByPlaneNoFront(bounds[i]);
            if (poly.Size() == 0)
            {
                bNeedInsert = false;
                break;
            }
        }
        if (bNeedInsert) myMesh1.AddPolygon(poly);
        poly.Clear();
    }
    if (myMesh1.PrimitiveCount() == 0)
    {
        pLeaf->type = eCritical;
        FillOctreeLeafNode(mesh1, mesh2, pLeaf);
        *node = pLeaf;
        return;
    }

    for (auto index: mesh2)
    {
        /// convert simple mesh into plane based mesh
        MeshData *data = &(mMesh2[index]);
        if (!data->bSplitted)
        {
            data->bSplitted = true;
            data->OrigPolygon = FixedPlanePolygon(data->Position[0],
                data->Position[1], data->Position[2]);
            FixedPlanePolygon *root = new FixedPlanePolygon(data->OrigPolygon);
            data->Fragments.push_back(root);
        }

        // get the inside polygons: myMesh2
        poly = data->OrigPolygon;
        bool bNeedInsert = true;
        for (int i = 0; i < 6; i++)
        {
            poly.ClipByPlaneNoFront(bounds[i]);
            if (poly.Size() == 0)
            {
                bNeedInsert = false;
                break;
            }
        }
        if (bNeedInsert) myMesh2.AddPolygon(poly);
        poly.Clear();
    }
    if (myMesh2.PrimitiveCount() == 0)
    {
        pLeaf->type = eCritical;
        FillOctreeLeafNode(mesh1, mesh2, pLeaf);
        *node = pLeaf;
        return;
    }
    FixedBSPTree *tree1, *tree2;
    tree1 = myMesh1.ToBSPTree();
    tree1->FormSubHyperPlane(bbox);
    tree2 = myMesh2.ToBSPTree();
    tree2->FormSubHyperPlane(bbox);

    auto op = mOperation;
    if (mOperation == FixedBSPTree::OP_DIFFERENCE)
    {
        op = FixedBSPTree::OP_INTERSECT;
    }

    FixedBSPTree *mergeTree = tree1->Merge(tree2, op);
    delete tree1;
    delete tree2;

    mergeTree->GetPolygons(mPlanePolygon);
    delete mergeTree;

    pLeaf->type = eIntered;
    FillOctreeLeafNode(mesh1, mesh2, pLeaf);
    *node = pLeaf;
}