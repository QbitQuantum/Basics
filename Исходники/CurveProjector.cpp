void CurveProjectorWithToolMesh::makeToolMesh( const TopoDS_Edge& aEdge,std::vector<MeshGeomFacet> &cVAry )
{
  Standard_Real fBegin, fEnd;
  Handle(Geom_Curve) hCurve = BRep_Tool::Curve(aEdge,fBegin,fEnd);
  float fLen   = float(fEnd - fBegin);
  Base::Vector3f cResultPoint;

  unsigned long ulNbOfPoints = 15,PointCount=0/*,uCurFacetIdx*/;

  std::vector<LineSeg> LineSegs;

  MeshFacetIterator It(_Mesh);

  Base::SequencerLauncher seq("Building up tool mesh...", ulNbOfPoints+1);  

  std::map<unsigned long,std::vector<Base::Vector3f> > FaceProjctMap;
 
  for (unsigned long i = 0; i < ulNbOfPoints; i++)
  {
    seq.next();
    gp_Pnt gpPt = hCurve->Value(fBegin + (fLen * float(i)) / float(ulNbOfPoints-1));
    Base::Vector3f LinePoint((float)gpPt.X(),
                             (float)gpPt.Y(),
                             (float)gpPt.Z());

    Base::Vector3f ResultNormal;

    // go through the whole Mesh
    for(It.Init();It.More();It.Next())
    {
      // try to project (with angle) to the face
      if (It->IntersectWithLine (Base::Vector3f((float)gpPt.X(),(float)gpPt.Y(),(float)gpPt.Z()),
          It->GetNormal(), cResultPoint) )
      {
        if(Base::Distance(LinePoint,cResultPoint) < 0.5)
          ResultNormal += It->GetNormal();
      }
    }
    LineSeg s;
    s.p = Base::Vector3f((float)gpPt.X(),
                         (float)gpPt.Y(),
                         (float)gpPt.Z());
    s.n = ResultNormal.Normalize();
    LineSegs.push_back(s);
  }

  Base::Console().Log("Projection map [%d facets with %d points]\n",FaceProjctMap.size(),PointCount);


  // build up the new mesh
  Base::Vector3f lp(FLOAT_MAX,0,0), ln, p1, p2, p3, p4,p5,p6;
  float ToolSize = 0.2f;

  for (std::vector<LineSeg>::iterator It2=LineSegs.begin(); It2!=LineSegs.end();++It2)
  {
    if(lp.x != FLOAT_MAX)
    {
      p1 = lp       + (ln       * (-ToolSize));
      p2 = lp       + (ln       *  ToolSize);
      p3 = lp;
      p4 = (*It2).p;
      p5 = (*It2).p + ((*It2).n * (-ToolSize));
      p6 = (*It2).p + ((*It2).n *  ToolSize);

      cVAry.push_back(MeshGeomFacet(p3,p2,p6));
      cVAry.push_back(MeshGeomFacet(p3,p6,p4));
      cVAry.push_back(MeshGeomFacet(p1,p3,p4));
      cVAry.push_back(MeshGeomFacet(p1,p4,p5));

    }

    lp = (*It2).p;
    ln = (*It2).n;
  }



}