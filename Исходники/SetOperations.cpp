void SetOperations::TriangulateMesh (const MeshKernel &cutMesh, int side)
{
  // Triangulate Mesh 
  std::map<unsigned long, std::list<std::set<MeshPoint>::iterator> >::iterator it1;
  for (it1 = _facet2points[side].begin(); it1 != _facet2points[side].end(); it1++)
  {
    std::vector<Vector3f> points;
    std::set<MeshPoint>   pointsSet;

    unsigned long fidx = it1->first;
    MeshGeomFacet f = cutMesh.GetFacet(fidx);

    //if (side == 1)
    //    _builder.addSingleTriangle(f._aclPoints[0], f._aclPoints[1], f._aclPoints[2], 3, 0, 1, 1);

     // facet corner points
    //const MeshFacet& mf = cutMesh._aclFacetArray[fidx];
    int i;
    for (i = 0; i < 3; i++)
    {
      pointsSet.insert(f._aclPoints[i]);
      points.push_back(f._aclPoints[i]);
    }
    
    // triangulated facets
    std::list<std::set<MeshPoint>::iterator>::iterator it2;
    for (it2 = it1->second.begin(); it2 != it1->second.end(); it2++)
    {
      if (pointsSet.find(*(*it2)) == pointsSet.end())
      {
        pointsSet.insert(*(*it2));
        points.push_back(*(*it2));
      }

    }

    Vector3f normal = f.GetNormal();
    Vector3f base = points[0];
    Vector3f dirX = points[1] - points[0];
    dirX.Normalize();
    Vector3f dirY = dirX % normal;

    // project points to 2D plane
    i = 0;
    std::vector<Vector3f>::iterator it;
    std::vector<Vector3f> vertices;
    for (it = points.begin(); it != points.end(); it++)
    {
      Vector3f pv = *it;
      pv.TransformToCoordinateSystem(base, dirX, dirY);
      vertices.push_back(pv);
    }

    DelaunayTriangulator tria;
    tria.SetPolygon(vertices);
    tria.TriangulatePolygon();

    std::vector<MeshFacet> facets = tria.GetFacets();
    for (std::vector<MeshFacet>::iterator it = facets.begin(); it != facets.end(); ++it)
    {
      if ((it->_aulPoints[0] == it->_aulPoints[1]) ||
          (it->_aulPoints[1] == it->_aulPoints[2]) ||
          (it->_aulPoints[2] == it->_aulPoints[0]))
      { // two same triangle corner points
        continue;
      }
  
      MeshGeomFacet facet(points[it->_aulPoints[0]],
                          points[it->_aulPoints[1]],
                          points[it->_aulPoints[2]]);

      //if (side == 1)
      // _builder.addSingleTriangle(facet._aclPoints[0], facet._aclPoints[1], facet._aclPoints[2], true, 3, 0, 1, 1);

      //if (facet.Area() < 0.0001f)
      //{ // too small facet
      //  continue;
      //}

      float dist0 = facet._aclPoints[0].DistanceToLine
          (facet._aclPoints[1],facet._aclPoints[1] - facet._aclPoints[2]);
      float dist1 = facet._aclPoints[1].DistanceToLine
          (facet._aclPoints[0],facet._aclPoints[0] - facet._aclPoints[2]);
      float dist2 = facet._aclPoints[2].DistanceToLine
          (facet._aclPoints[0],facet._aclPoints[0] - facet._aclPoints[1]);

      if ((dist0 < _minDistanceToPoint) ||
          (dist1 < _minDistanceToPoint) ||
          (dist2 < _minDistanceToPoint))
      {
        continue;
      }

      //dist0 = (facet._aclPoints[0] - facet._aclPoints[1]).Length();
      //dist1 = (facet._aclPoints[1] - facet._aclPoints[2]).Length();
      //dist2 = (facet._aclPoints[2] - facet._aclPoints[3]).Length();

      //if ((dist0 < _minDistanceToPoint) || (dist1 < _minDistanceToPoint) || (dist2 < _minDistanceToPoint))
      //{
      //  continue;
      //}

      facet.CalcNormal();
      if ((facet.GetNormal() * f.GetNormal()) < 0.0f)
      { // adjust normal
         std::swap(facet._aclPoints[0], facet._aclPoints[1]);
         facet.CalcNormal();
      }


      int j;
      for (j = 0; j < 3; j++)
      {
        std::map<Edge, EdgeInfo>::iterator eit = _edges.find(Edge(facet._aclPoints[j], facet._aclPoints[(j+1)%3]));

        if (eit != _edges.end())
        {

          if (eit->second.fcounter[side] < 2)
          {
            //if (side == 0)
            //   _builder.addSingleTriangle(facet._aclPoints[0], facet._aclPoints[1], facet._aclPoints[2], true, 3, 0, 1, 1);

            eit->second.facet[side] = fidx;
            eit->second.facets[side][eit->second.fcounter[side]] = facet;
            eit->second.fcounter[side]++;
            facet.SetFlag(MeshFacet::MARKED); // set all facets connected to an edge: MARKED

          }
        }
      }

      _newMeshFacets[side].push_back(facet);

    } // for (i = 0; i < (out->numberoftriangles * 3); i += 3)
  } // for (it1 = _facet2points[side].begin(); it1 != _facet2points[side].end(); it1++)
}