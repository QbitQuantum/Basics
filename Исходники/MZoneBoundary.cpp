int edge_normal
(const MVertex *const vertex, const int zoneIndex, const GEdge *const gEdge,
 const CCon::FaceVector<MZoneBoundary<2>::GlobalVertexData<MEdge>::FaceDataB>
 &faces, SVector3 &boNormal, const int onlyFace = -1)
{

  double par=0.0;
  // Note: const_cast used to match MVertex.cpp interface
  if(!reparamMeshVertexOnEdge(const_cast<MVertex*>(vertex), gEdge, par)) return 1;

  const SVector3 tangent(gEdge->firstDer(par));
                                        // Tangent to the boundary face
  SPoint3 interior(0., 0., 0.);         // An interior point
  SVector3 meshPlaneNormal(0.);         // This normal is perpendicular to the
                                        // plane of the mesh

  // The interior point and mesh plane normal are computed from all elements in
  // the zone.
  int cFace = 0;
  int iFace = 0;
  int nFace = faces.size();
  if ( onlyFace >= 0 ) {
    iFace = onlyFace;
    nFace = onlyFace + 1;
  }
  for(; iFace != nFace; ++iFace) {
    if(faces[iFace].zoneIndex == zoneIndex) {
      ++cFace;
      interior += faces[iFace].parentElement->barycenter();
      // Make sure all the planes go in the same direction
      //**Required?
      SVector3 mpnt = faces[iFace].parentElement->getFace(0).normal();
      if(dot(mpnt, meshPlaneNormal) < 0.) mpnt.negate();
      meshPlaneNormal += mpnt;
    }
  }
  interior /= cFace;
  // Normal to the boundary edge (but unknown direction)
  boNormal = crossprod(tangent, meshPlaneNormal);
  boNormal.normalize();
  // Direction vector from vertex to interior (inwards).  The normal should
  // point in the same direction.
  if(dot(boNormal, SVector3(vertex->point(), interior)) < 0.)
    boNormal.negate();
  return 0;

}