void vtIcoGlobe::CreateUnfoldableDymax()
{
    int i;
    for (i = 0; i < 22; i++)
    {
        m_mface[i].xform = new vtTransform;
        m_mface[i].surfgroup = new vtGroup;
        m_mface[i].surfgroup->SetEnabled(false);
        m_mface[i].geode = new vtGeode;
        m_mface[i].xform->addChild(m_mface[i].geode);
        m_mface[i].xform->addChild(m_mface[i].surfgroup);

        vtString str;
        str.Format("IcoFace %d", i);
        m_mface[i].xform->setName(str);

        int face = dymax_subfaces[i].face;
        int subfaces = dymax_subfaces[i].subfaces;

        bool which;
        int mat = GetMaterialForFace(face, which);

        add_face2(m_mesh[i], face, i, subfaces, which);

        m_mface[i].geode->SetMaterials(m_earthmats);
        m_mface[i].geode->AddMesh(m_mesh[i], m_globe_mat[mat]);
    }
    m_top->addChild(m_mface[0].xform);

    m_mface[0].local_origin.Set(0,0,0);
    for (i = 1; i < 22; i++)
        FindLocalOrigin(i);
    for (i = 1; i < 22; i++)
        SetMeshConnect(i);

    // Determine necessary rotation to orient flat map toward viewer.
    FQuat qface;
    DPoint3 v0 = m_verts[icosa_face_v[0][0]];
    DPoint3 v1 = m_verts[icosa_face_v[0][1]];
    DPoint3 v2 = m_verts[icosa_face_v[0][2]];

    // Create a rotation to turn the globe so that a specific edge
    //  is pointed down -X for proper map orientation
    DPoint3 edge = v2 - v0;
    edge.Normalize();

    // compose face norm and face quaternion
    DPoint3 fnorm = (v0 + v1 + v2).Normalize();
    qface.SetFromVectors(edge, fnorm);

    // desired vector points down -X
    FQuat qdesired;
    qdesired.SetFromVectors(FPoint3(-1,0,0),FPoint3(0,0,1));

    // determine rotational difference
    m_diff = qface.Inverse() * qdesired;

#if 0
    // scaffolding mesh for debugging
    vtMesh *sm = new vtMesh(GL_LINES, VT_Colors, 12);
    sm->AddVertex(v0*1.0001f);
    sm->AddVertex(v1*1.0001f);
    sm->AddVertex(v2*1.0001f);
    sm->AddVertex(v0*1.0001f+fnorm);
    sm->SetVtxColor(0, RGBf(1,0,0));
    sm->SetVtxColor(1, RGBf(0,1,0));
    sm->SetVtxColor(2, RGBf(0,0,1));
    sm->SetVtxColor(3, RGBf(1,1,0));
    sm->AddLine(0,1);
    sm->AddLine(0,2);
    sm->AddLine(0,3);
    m_geom[0]->AddMesh(sm, m_red);
    sm->Release();
#endif

    // Show axis of rotation (north and south poles)
    vtMaterialArray *pMats = new vtMaterialArray;
    int green = pMats->AddRGBMaterial1(RGBf(0,1,0), false, false);
    m_pAxisGeom = new vtGeode;
    m_pAxisGeom->setName("AxisGeom");
    m_pAxisGeom->SetMaterials(pMats);
    m_pAxisGeom->SetEnabled(false);

    vtMesh *pMesh = new vtMesh(osg::PrimitiveSet::LINES, 0, 6);
    pMesh->AddVertex(FPoint3(0,2,0));
    pMesh->AddVertex(FPoint3(0,-2,0));
    pMesh->AddLine(0,1);
    m_pAxisGeom->AddMesh(pMesh, green);
    m_top->addChild(m_pAxisGeom);

#if 0
    axis = WireAxis(RGBf(1,1,1), 1.1f);
    m_top->addChild(axis);
#endif
}