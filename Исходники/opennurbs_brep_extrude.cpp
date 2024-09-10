bool ON_BrepExtrude( 
          ON_Brep& brep,
          const ON_Curve& path_curve,
          bool bCap
          )
{
  ON_Workspace ws;
  const int vcount0 = brep.m_V.Count();
  const int tcount0 = brep.m_T.Count();
  const int lcount0 = brep.m_L.Count();
  const int ecount0 = brep.m_E.Count();
  const int fcount0 = brep.m_F.Count();

  const ON_3dPoint PathStart = path_curve.PointAtStart();
  ON_3dPoint P = path_curve.PointAtEnd();
  if ( !PathStart.IsValid() || !P.IsValid() )
    return false;
  const ON_3dVector height = P - PathStart;
  if ( !height.IsValid() || height.Length() <= ON_ZERO_TOLERANCE )
    return false;

  ON_Xform tr;
  tr.Translation(height);

  // count number of new sides
  int side_count = 0;
  int i, vi, ei, fi;
  bool* bSideEdge = (bool*)ws.GetIntMemory(ecount0*sizeof(bSideEdge[0]));
  for ( ei = 0; ei < ecount0; ei++ )
  {
    const ON_BrepEdge& e = brep.m_E[ei];
    if ( 1 == e.m_ti.Count() )
    {
      side_count++;
      bSideEdge[ei] = true;
    }
    else
    {
      bSideEdge[ei] = false;
    }
  }

  brep.m_V.Reserve( 2*vcount0 );
  i = 4*side_count + (bCap?tcount0:0);
  brep.m_T.Reserve( tcount0 + i );
  brep.m_C2.Reserve( brep.m_C2.Count() + i );
  brep.m_L.Reserve( lcount0 + side_count + (bCap?lcount0:0) );
  i = side_count + (bCap?ecount0:side_count);
  brep.m_E.Reserve( ecount0 + i );
  brep.m_C3.Reserve( brep.m_C3.Count() + i );
  i = side_count + (bCap?fcount0:0);
  brep.m_F.Reserve( fcount0 + i );
  brep.m_S.Reserve( brep.m_S.Count() + i );

  bool bOK = true;

  // build top vertices
  int* topvimap = ws.GetIntMemory(vcount0);
  memset(topvimap,0,vcount0*sizeof(topvimap[0]));
  if ( bCap )
  {
    for ( vi = 0; vi < vcount0; vi++ )
    {
      const ON_BrepVertex& bottomv = brep.m_V[vi];
      ON_BrepVertex& topv = brep.NewVertex(bottomv.point+height,bottomv.m_tolerance);
      topvimap[vi] = topv.m_vertex_index;
    }
  }
  else
  {
    for ( ei = 0; ei < ecount0; ei++ )
    {
      if ( bSideEdge[ei] )
      {
        const ON_BrepEdge& bottome = brep.m_E[ei];
        int bottomvi0 = bottome.m_vi[0];
        if ( bottomvi0 < 0 || bottomvi0 >= vcount0 )
        {
          bOK = false;
          break;
        }
        int bottomvi1 = bottome.m_vi[1];
        if ( bottomvi1 < 0 || bottomvi1 >= vcount0 )
        {
          bOK = false;
          break;
        }
        if ( !topvimap[bottomvi0] )
        {
          const ON_BrepVertex& bottomv = brep.m_V[bottomvi0];
          ON_BrepVertex& topv = brep.NewVertex(bottomv.point+height,bottomv.m_tolerance);
          topvimap[bottomvi0] = topv.m_vertex_index;
        }
        if ( !topvimap[bottomvi1] )
        {
          const ON_BrepVertex& bottomv = brep.m_V[bottomvi1];
          ON_BrepVertex& topv = brep.NewVertex(bottomv.point+height,bottomv.m_tolerance);
          topvimap[bottomvi1] = topv.m_vertex_index;
        }
      }
    }
  }

  // build top edges
  int* topeimap = ws.GetIntMemory(ecount0);
  memset(topeimap,0,ecount0*sizeof(topeimap[0]));
  if ( bOK ) for ( ei = 0; ei < ecount0; ei++ )
  {
    if ( bCap || bSideEdge[ei] )
    {
      const ON_BrepEdge& bottome = brep.m_E[ei];
      ON_BrepVertex& topv0 = brep.m_V[topvimap[bottome.m_vi[0]]];
      ON_BrepVertex& topv1 = brep.m_V[topvimap[bottome.m_vi[1]]];
      ON_Curve* c3 = bottome.DuplicateCurve();
      if ( !c3 )
      {
        bOK = false;
        break;
      }
      c3->Transform(tr);
      int c3i = brep.AddEdgeCurve(c3);
      ON_BrepEdge& tope = brep.NewEdge(topv0,topv1,c3i,0,bottome.m_tolerance);
      topeimap[ei] = tope.m_edge_index;
    }
  }

  // build side edges
  int* sideveimap = ws.GetIntMemory(vcount0);
  memset(sideveimap,0,vcount0*sizeof(sideveimap[0]));
  if ( bOK ) for ( vi = 0; vi < vcount0; vi++ )
  {
    ON_BrepVertex& bottomv = brep.m_V[vi];
    for ( int vei = 0; vei < bottomv.m_ei.Count(); vei++ )
    {
      if ( bSideEdge[bottomv.m_ei[vei]] && topvimap[vi] )
      {
        ON_BrepVertex& topv = brep.m_V[topvimap[vi]];
        ON_Curve* c3 = path_curve.DuplicateCurve();
        if ( !c3 )
        {
          bOK = false;
        }
        else
        {
          ON_3dVector D = bottomv.point - PathStart;
          c3->Translate(D);
          int c3i = brep.AddEdgeCurve(c3);
          const ON_BrepEdge& e = brep.NewEdge(bottomv,topv,c3i,0,0.0);
          sideveimap[vi] = e.m_edge_index;
        }
        break;
      }
    }
  }

  if ( bOK && bCap )
  {
    // build top faces
    for (fi = 0; fi < fcount0; fi++ )
    {
      const ON_BrepFace& bottomf = brep.m_F[fi];
      ON_Surface* srf = bottomf.DuplicateSurface();
      if ( !srf )
      {
        bOK = false;
        break;
      }
      srf->Transform(tr);
      int si = brep.AddSurface(srf);
      ON_BrepFace& topf = brep.NewFace(si);
      topf.m_bRev = !bottomf.m_bRev;
      const int loop_count = bottomf.m_li.Count();
      topf.m_li.Reserve(loop_count);
      for ( int fli = 0; fli < loop_count; fli++ )
      {
        const ON_BrepLoop& bottoml = brep.m_L[bottomf.m_li[fli]];
        ON_BrepLoop& topl = brep.NewLoop(bottoml.m_type,topf);
        const int loop_trim_count = bottoml.m_ti.Count();
        topl.m_ti.Reserve(loop_trim_count);
        for ( int lti = 0; lti < loop_trim_count; lti++ )
        {
          const ON_BrepTrim& bottomt = brep.m_T[bottoml.m_ti[lti]];
          ON_NurbsCurve* c2 = ON_NurbsCurve::New();
          if ( !bottomt.GetNurbForm(*c2) )
          {
            delete c2;
            bOK = false;
            break;
          }
          int c2i = brep.AddTrimCurve(c2);
          ON_BrepTrim* topt = 0;
          if ( bottomt.m_ei >= 0 )
          {
            ON_BrepEdge& tope = brep.m_E[topeimap[bottomt.m_ei]];
            topt = &brep.NewTrim(tope,bottomt.m_bRev3d,topl,c2i);
          }
          else
          {
            // singular trim
            ON_BrepVertex& topv = brep.m_V[topvimap[bottomt.m_vi[0]]];
            topt = &brep.NewSingularTrim(topv,topl,bottomt.m_iso,c2i);
          }
          topt->m_tolerance[0] = bottomt.m_tolerance[0];
          topt->m_tolerance[1] = bottomt.m_tolerance[1];
          topt->m_pbox = bottomt.m_pbox;
          topt->m_type = bottomt.m_type;
          topt->m_iso = bottomt.m_iso;
        }
        topl.m_pbox = bottoml.m_pbox;
      }
    }
  }

  // build sides
  int bRev3d[4] = {0,0,1,1};
  int vid[4], eid[4];
  if( bOK ) for ( ei = 0; ei < ecount0; ei++ )
  {
    if ( bSideEdge[ei] && topeimap[ei] )
    {
      ON_BrepEdge& bottome = brep.m_E[ei];
      ON_BrepEdge& tope = brep.m_E[topeimap[ei]];
      vid[0] = bottome.m_vi[0];
      vid[1] = bottome.m_vi[1];
      vid[2] = topvimap[vid[1]];
      vid[3] = topvimap[vid[0]];
      if ( sideveimap[vid[0]] && sideveimap[vid[1]] )
      {
        ON_BrepEdge& leftedge = brep.m_E[sideveimap[vid[0]]];
        ON_BrepEdge& rightedge = brep.m_E[sideveimap[vid[1]]];
        ON_Curve* cx = bottome.DuplicateCurve();
        if ( !cx )
        {
          bOK = false;
          break;
        }
        ON_Curve* cy = leftedge.DuplicateCurve();
        if ( !cy )
        {
          delete cx;
          bOK = false;
          break;
        }
        ON_SumSurface* srf = new ON_SumSurface();
        srf->m_curve[0] = cx;
        srf->m_curve[1] = cy;
        srf->m_basepoint = srf->m_curve[1]->PointAtStart();
        srf->m_basepoint.x = -srf->m_basepoint.x;
        srf->m_basepoint.y = -srf->m_basepoint.y;
        srf->m_basepoint.z = -srf->m_basepoint.z;
        eid[0] = bottome.m_edge_index;
        eid[1] = rightedge.m_edge_index;
        eid[2] = tope.m_edge_index;
        eid[3] = leftedge.m_edge_index;
        ON_BrepFace* face = brep.NewFace(srf,vid,eid,bRev3d);
        if ( !face )
        {
          bOK = false;
          break;
        }
        else if ( bottome.m_ti.Count() == 2 )
        {
          const ON_BrepTrim& trim0 = brep.m_T[bottome.m_ti[0]];
          const ON_BrepTrim& trim1 = brep.m_T[bottome.m_ti[1]];
          const ON_BrepLoop& loop0 = brep.m_L[trim0.m_li];
          const ON_BrepLoop& loop1 = brep.m_L[trim1.m_li];
          bool bBottomFaceRev = brep.m_F[(loop0.m_fi != face->m_face_index) ? loop0.m_fi : loop1.m_fi].m_bRev;
          bool bSideFaceRev = ( trim0.m_bRev3d != trim1.m_bRev3d ) 
                            ? bBottomFaceRev 
                            : !bBottomFaceRev;
          face->m_bRev = bSideFaceRev;
        }
      }
    }
  }

  if ( !bOK )
  {
    for ( vi = brep.m_V.Count(); vi >= vcount0; vi-- )
    {
      brep.DeleteVertex(brep.m_V[vi]);
    }
  }

  return bOK;
}