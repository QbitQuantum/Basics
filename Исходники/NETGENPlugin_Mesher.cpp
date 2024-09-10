bool NETGENPlugin_Mesher::fillNgMesh(netgen::OCCGeometry&           occgeom,
                                     netgen::Mesh&                  ngMesh,
                                     vector<SMDS_MeshNode*>&        nodeVec,
                                     const list< SMESH_subMesh* > & meshedSM)
{
  TNode2IdMap nodeNgIdMap;

  TopTools_MapOfShape visitedShapes;

  SMESH_MesherHelper helper (*_mesh);

  int faceID = occgeom.fmap.Extent();
  _faceDescriptors.clear();

  list< SMESH_subMesh* >::const_iterator smIt, smEnd = meshedSM.end();
  for ( smIt = meshedSM.begin(); smIt != smEnd; ++smIt )
  {
    SMESH_subMesh* sm = *smIt;
    if ( !visitedShapes.Add( sm->GetSubShape() ))
      continue;

    SMESHDS_SubMesh * smDS = sm->GetSubMeshDS();

    switch ( sm->GetSubShape().ShapeType() )
    {
    case TopAbs_EDGE: { // EDGE
      // ----------------------
      const TopoDS_Edge& geomEdge  = TopoDS::Edge( sm->GetSubShape() );

      // Add ng segments for each not meshed face the edge bounds
      TopTools_MapOfShape visitedAncestors;
      const TopTools_ListOfShape& ancestors = _mesh->GetAncestors( geomEdge );
      TopTools_ListIteratorOfListOfShape ancestorIt ( ancestors );
      for ( ; ancestorIt.More(); ancestorIt.Next() )
      {
        const TopoDS_Shape & ans = ancestorIt.Value();
        if ( ans.ShapeType() != TopAbs_FACE || !visitedAncestors.Add( ans ))
          continue;
        const TopoDS_Face& face = TopoDS::Face( ans );

        int faceID = occgeom.fmap.FindIndex( face );
        if ( faceID < 1 )
          continue; // meshed face

        // find out orientation of geomEdge within face
        bool isForwad = false;
        for ( TopExp_Explorer exp( face, TopAbs_EDGE ); exp.More(); exp.Next() ) {
          if ( geomEdge.IsSame( exp.Current() )) {
            isForwad = ( exp.Current().Orientation() == geomEdge.Orientation() );
            break;
          }
        }
        bool isQuad = smDS->GetElements()->next()->IsQuadratic();

        // get all nodes from geomEdge
        StdMeshers_FaceSide fSide( face, geomEdge, _mesh, isForwad, isQuad );
        const vector<UVPtStruct>& points = fSide.GetUVPtStruct();
        int i, nbSeg = fSide.NbSegments();

        double otherSeamParam = 0;
        helper.SetSubShape( face );
        bool isSeam = helper.IsRealSeam( geomEdge );
        if ( isSeam )
          otherSeamParam =
            helper.GetOtherParam( helper.GetPeriodicIndex() == 1 ? points[0].u : points[0].v );

        // add segments

        int prevNgId = ngNodeId( points[0].node, ngMesh, nodeNgIdMap );

        for ( i = 0; i < nbSeg; ++i )
        {
          const UVPtStruct& p1 = points[ i ];
          const UVPtStruct& p2 = points[ i+1 ];

          netgen::Segment seg;
          // ng node ids
          seg.p1 = prevNgId;
          seg.p2 = prevNgId = ngNodeId( p2.node, ngMesh, nodeNgIdMap );
          // node param on curve
          seg.epgeominfo[ 0 ].dist = p1.param;
          seg.epgeominfo[ 1 ].dist = p2.param;
          // uv on face
          seg.epgeominfo[ 0 ].u = p1.u;
          seg.epgeominfo[ 0 ].v = p1.v;
          seg.epgeominfo[ 1 ].u = p2.u;
          seg.epgeominfo[ 1 ].v = p2.v;

          //seg.epgeominfo[ iEnd ].edgenr = edgeID; //  = geom.emap.FindIndex(edge);
          seg.si = faceID;                   // = geom.fmap.FindIndex (face);
          seg.edgenr = ngMesh.GetNSeg() + 1; // segment id
          ngMesh.AddSegment (seg);

          if ( isSeam )
          {
            if ( helper.GetPeriodicIndex() == 1 ) {
              seg.epgeominfo[ 0 ].u = otherSeamParam;
              seg.epgeominfo[ 1 ].u = otherSeamParam;
              swap (seg.epgeominfo[0].v, seg.epgeominfo[1].v);
            } else {
              seg.epgeominfo[ 0 ].v = otherSeamParam;
              seg.epgeominfo[ 1 ].v = otherSeamParam;
              swap (seg.epgeominfo[0].u, seg.epgeominfo[1].u);
            }
            swap (seg.p1, seg.p2);
            swap (seg.epgeominfo[0].dist, seg.epgeominfo[1].dist);
            seg.edgenr = ngMesh.GetNSeg() + 1; // segment id
            ngMesh.AddSegment (seg);
          }
        }
      } // loop on geomEdge ancestors

      break;
    } // case TopAbs_EDGE

    case TopAbs_FACE: { // FACE
      // ----------------------
      const TopoDS_Face& geomFace  = TopoDS::Face( sm->GetSubShape() );
      helper.SetSubShape( geomFace );

      // Find solids the geomFace bounds
      int solidID1 = 0, solidID2 = 0;
      const TopTools_ListOfShape& ancestors = _mesh->GetAncestors( geomFace );
      TopTools_ListIteratorOfListOfShape ancestorIt ( ancestors );
      for ( ; ancestorIt.More(); ancestorIt.Next() )
      {
        const TopoDS_Shape & solid = ancestorIt.Value();
        if ( solid.ShapeType() == TopAbs_SOLID  ) {
          int id = occgeom.somap.FindIndex ( solid );
          if ( solidID1 && id != solidID1 ) solidID2 = id;
          else                              solidID1 = id;
        }
      }
      faceID++;
      _faceDescriptors[ faceID ].first  = solidID1;
      _faceDescriptors[ faceID ].second = solidID2;

      // Orient the face correctly in solidID1 (issue 0020206)
      bool reverse = false;
      if ( solidID1 ) {
        TopoDS_Shape solid = occgeom.somap( solidID1 );
        for ( TopExp_Explorer f( solid, TopAbs_FACE ); f.More(); f.Next() ) {
          if ( geomFace.IsSame( f.Current() )) {
            reverse = SMESH_Algo::IsReversedSubMesh( TopoDS::Face( f.Current()), helper.GetMeshDS() );
            break;
          }
        }
      }

      // Add surface elements
      SMDS_ElemIteratorPtr faces = smDS->GetElements();
      while ( faces->more() ) {

        const SMDS_MeshElement* f = faces->next();
        if ( f->NbNodes() % 3 != 0 ) { // not triangle
          for ( ancestorIt.Initialize(ancestors); ancestorIt.More(); ancestorIt.Next() )
            if ( ancestorIt.Value().ShapeType() == TopAbs_SOLID  ) {
              sm = _mesh->GetSubMesh( ancestorIt.Value() );
              break;
            }
          SMESH_ComputeErrorPtr& smError = sm->GetComputeError();
          smError.reset( new SMESH_ComputeError(COMPERR_BAD_INPUT_MESH,"Not triangle submesh"));
          smError->myBadElements.push_back( f );
          return false;
        }

        netgen::Element2d tri(3);
        tri.SetIndex ( faceID );

        for ( int i = 0; i < 3; ++i ) {
          const SMDS_MeshNode* node = f->GetNode( i ), * inFaceNode=0;
          if ( helper.IsSeamShape( node->GetPosition()->GetShapeId() ))
            if ( helper.IsSeamShape( f->GetNodeWrap( i+1 )->GetPosition()->GetShapeId() ))
              inFaceNode = f->GetNodeWrap( i-1 );
            else 
              inFaceNode = f->GetNodeWrap( i+1 );

          gp_XY uv = helper.GetNodeUV( geomFace, node, inFaceNode );
          if ( reverse ) {
            tri.GeomInfoPi(3-i).u = uv.X();
            tri.GeomInfoPi(3-i).v = uv.Y();
            tri.PNum      (3-i) = ngNodeId( node, ngMesh, nodeNgIdMap );
          } else {
            tri.GeomInfoPi(i+1).u = uv.X();
            tri.GeomInfoPi(i+1).v = uv.Y();
            tri.PNum      (i+1) = ngNodeId( node, ngMesh, nodeNgIdMap );
          }
        }

        ngMesh.AddSurfaceElement (tri);

      }
      break;
    } //

    case TopAbs_VERTEX: { // VERTEX
      // --------------------------
      SMDS_NodeIteratorPtr nodeIt = smDS->GetNodes();
      if ( nodeIt->more() )
        ngNodeId( nodeIt->next(), ngMesh, nodeNgIdMap );
      break;
    }
    default:;
    } // switch
  } // loop on submeshes

  // fill nodeVec
  nodeVec.resize( ngMesh.GetNP() + 1 );
  TNode2IdMap::iterator node_NgId, nodeNgIdEnd = nodeNgIdMap.end();
  for ( node_NgId = nodeNgIdMap.begin(); node_NgId != nodeNgIdEnd; ++node_NgId)
    nodeVec[ node_NgId->second ] = (SMDS_MeshNode*) node_NgId->first;

  return true;
}