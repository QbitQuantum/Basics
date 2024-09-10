    TRef<Geo> Execute(const Matrix& mat, GroupGeo* pgroup)
    {
        ZString strName = pgroup->GetName();

        if (!strName.IsEmpty()) {
            if (   strName.Find("frm-") == 0
                    && (!pgroup->AnyChildGroups())
               ) {
                Vector vecPosition = mat.Transform(Vector(0, 0, 0));
                Vector vecForward  = mat.TransformDirection(Vector(0, 0, -1));
                Vector vecUp       = mat.TransformDirection(Vector(0, 1,  0));

                strName = strName.RightOf(4);

                if (strName.Find("SS") != -1) {
                    //
                    // a strobe light
                    //

                    ValueList* plist = pgroup->GetList();

                    if (plist->GetCount() == 1) {
                        MaterialGeo* pmatGeo;
                        CastTo(pmatGeo, plist->GetFirst());
                        Material* pmaterial = pmatGeo->GetMaterial();

                        AddLight(strName, pmaterial->GetDiffuse(), vecPosition);
                    } else {
                        AddLight(strName, Color(1, 1, 1), vecPosition);
                    }

                    return Geo::GetEmpty();
                } else if (
                    strName.Find("thrust") != -1
                    || strName.Find("smoke") != -1
                    || strName.Find("rocket") != -1
                ) {
                    //
                    // this is an engine
                    //

                    m_pframes->GetList().PushFront(
                        FrameData(strName, vecPosition, vecForward, vecUp)
                    );

                    return Geo::GetEmpty();
                } else if (
                    (strName.Find("weapon") != -1)
                    || (strName.Find("wepatt") != -1)
                    || (strName.Find("wepemt") != -1)
                    || (strName.Find("wepmnt") != -1)
                    || (strName.Find("trail")  != -1)
                ) {
                    //
                    // This is an attachment point
                    //

                    m_pframes->GetList().PushFront(
                        FrameData(strName, vecPosition, vecForward, vecUp)
                    );
                    return Geo::GetEmpty();
                } else if (
                    (strName.Find("garage") != -1)
                ) {
                    //
                    // This is a garage we need to leave the frame in the graph
                    //

                    m_pframes->GetList().PushFront(
                        FrameData(strName, vecPosition, vecForward, vecUp)
                    );
                }
            }
        }

        return NULL;
    }