void MeshAlgos::LoftOnCurve(MeshCore::MeshKernel &ResultMesh, const TopoDS_Shape &Shape, const std::vector<Base::Vector3f> &poly, const Base::Vector3f & up, float MaxSize)
{
  TopExp_Explorer Ex;
  Standard_Real fBegin, fEnd;
  std::vector<MeshGeomFacet> cVAry;
  std::map<TopoDS_Vertex,std::vector<Base::Vector3f>,_VertexCompare> ConnectMap;

  for (Ex.Init(Shape, TopAbs_EDGE); Ex.More(); Ex.Next())
  {
    // get the edge and the belonging Vertexes
    TopoDS_Edge Edge = (TopoDS_Edge&)Ex.Current();
    TopoDS_Vertex V1, V2;
    TopExp::Vertices(Edge, V1, V2);
    bool bBegin = false,bEnd = false;
    // geting the geometric curve and the interval
    GeomLProp_CLProps prop(BRep_Tool::Curve(Edge,fBegin,fEnd),1,0.0000000001);
    int res = int((fEnd - fBegin)/MaxSize);
    // do at least 2 segments
    if(res < 2) 
      res = 2;
    gp_Dir Tangent;

    std::vector<Base::Vector3f> prePoint(poly.size());
    std::vector<Base::Vector3f> actPoint(poly.size());
    
    // checking if there is already a end to conect
    if(ConnectMap.find(V1) != ConnectMap.end() ){
      bBegin = true;
      prePoint = ConnectMap[V1];
    }
    
    if(ConnectMap.find(V2) != ConnectMap.end() )
      bEnd = true;

    for (long i = 0; i < res; i++)
    {

      // get point and tangent at the position, up is fix for the moment
      prop.SetParameter(fBegin + ((fEnd - fBegin) * float(i)) / float(res-1));
      prop.Tangent(Tangent);
      Base::Vector3f Tng((float)Tangent.X(),
                         (float)Tangent.Y(),
                         (float)Tangent.Z());
      Base::Vector3f Ptn((float)prop.Value().X(),
                         (float)prop.Value().Y(),
                         (float)prop.Value().Z());
      Base::Vector3f Up (up);
      // normalize and calc the third vector of the plane coordinatesystem
      Tng.Normalize(); 
      Up.Normalize();
      Base::Vector3f Third(Tng%Up);

//      Base::Console().Log("Pos: %f %f %f \n",Ptn.x,Ptn.y,Ptn.z);

      unsigned int l=0;
      std::vector<Base::Vector3f>::const_iterator It;

      // got through the profile
      for(It=poly.begin();It!=poly.end();++It,l++)
        actPoint[l] = ((Third*It->x)+(Up*It->y)+(Tng*It->z)+Ptn);

      if(i == res-1 && !bEnd)
        // remeber the last row to conect to a otger edge with the same vertex
        ConnectMap[V2] = actPoint;

      if(i==1 && bBegin)
        // using the end of an other edge as start 
        prePoint = ConnectMap[V1];

      if(i==0 && !bBegin)
          // remember the first row for conection to a edge with the same vertex
          ConnectMap[V1] = actPoint;

      if(i ) // not the first row or somthing to conect to
      {
        for(l=0;l<actPoint.size();l++)
        {
          if(l) // not first point in row 
          {
            if(i == res-1 && bEnd) // if last row and a end to conect
              actPoint = ConnectMap[V2];

            Base::Vector3f p1 = prePoint[l-1],
                     p2 = actPoint[l-1],
                     p3 = prePoint[l],
                     p4 = actPoint[l];

            cVAry.push_back(MeshGeomFacet(p1,p2,p3));
            cVAry.push_back(MeshGeomFacet(p3,p2,p4));
          }
        }
      }

      prePoint = actPoint;
    }
  }

  ResultMesh.AddFacets(cVAry);

}