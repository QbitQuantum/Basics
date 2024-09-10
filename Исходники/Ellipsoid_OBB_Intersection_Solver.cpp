// Test intersection between an ellipsoid and oriented bounding box
//  Given an Ellipsoid defined by:   x'*Minv*x = NodeErrorBound
//  N is the decomposition of Minv:  Minv = N'*N
//  Dmin is the inverse sqrt of the largest eigenvalue of M (used for quick escape test)
//    Dmin = 1/sqrt(D[0])  where D = diag(D[0],D[1],D[2]) is the diagonal matrix of 
//    eigenvalues of M arranged largest to smallest
//    In other words, Dmin is the sqrt of the smallest eigenvalue of Minv
//  Note:  Minv = R*D^2*R' = N'*N     M = R*Dinv^2*R' => R' = V', Dinv = sqrt(S)
//         N = D*R'
//         Ninv = R*inv(D)
int Ellipsoid_OBB_Intersection_Solver::Test_Ellipsoid_OBB_Intersection( 
                                           const vct3 &v, 
                                           const BoundingBox &OBB, const vctFrm3 &Fobb,
                                           double NodeErrorBound,
                                           const  vct3x3 &N,
                                           double Dmin )
{
  // Algorithm is a modification of:
  //  Thomas Larsson, "An Efficient Ellipsoid-OBB Intersection Test"
  // 
  // Method:
  //  1) determine faces of oriented bounding box (OBB) visible from ellipse center
  //  2) affine transform to convert: ellipsoid -> sphere and OBB -> parallelpiped
  //  3) Sphere-Parallelpiped intersection test
  //
  // Define Bounding Box face indexes as:
  //  F1: X+  F2: X-
  //  F3: Y+  F4: Y-
  //  F5: Z+  F6: Z-
  //
  // Define Bounding Box vertex positions as:
  //   p[0] = m + Vx + Vy + Vz;       where  m = geometric center
  //   p[1] = m + Vx + Vy - Vz;             Vx = extent along local x axis (Vy & Vz similar)
  //   p[2] = m + Vx - Vy + Vz;
  //   p[3] = m + Vx - Vy - Vz;
  //   p[4] = m - Vx + Vy + Vz;
  //   p[5] = m - Vx + Vy - Vz;
  //   p[6] = m - Vx - Vy + Vz;
  //   p[7] = m - Vx - Vy - Vz;
  //
  // Define edge numbering for each face as:
  //   Note:  edge numbers progress in counterclockwise order around
  //          each face, meaning adjacent edges on a face have adjacent numbers
  //          in the edge numbering assigned below:
  //
  //         Edge0   Edge1   Edge2   Edge3
  //   F1:  [p0,p2] [p2,p3] [p3,p1] [p1,p0]
  //   F2:  [p6,p4] [p4,p5] [p5,p7] [p7,p6]
  //   F3:  [p4,p0] [p0,p1] [p1,p5] [p5,p4]
  //   F4:  [p2,p6] [p6,p7] [p7,p3] [p3,p2]
  //   F5:  [p4,p6] [p6,p2] [p2,p0] [p0,p4]
  //   F6:  [p1,p3] [p3,p7] [p7,p5] [p5,p1]
  //
  //  Note:  to understand this code, it helps to draw a picture of a bounding box
  //         using the face, vertex, and edge numbering as defined above
  //  Note:  face, vertex, and edge numbers for parallelpiped elements are derived
  //         directly from the affine mapped bounding box elements
  //
  static vct3 Fv;
  static vctFrm3 Finv;
  static vct3x3 Ns;
  static vct3 m;
  static vct3 nx,ny,nz;
  static vct3 Vx_,Vy_,Vz_;
  static vct3 Vxpos,Vypos,Vzpos;
  static vct3 Vxneg,Vyneg,Vzneg;
  static vct3 m_Vxp, m_Vxn;
  static vct3 Vyp_Vzp, Vyp_Vzn, Vyn_Vzn, Vyn_Vzp;
  static vct3 Nx,Ny,Nz;
  static vct3 p0,p1,p2,p3,p4,p5,p6,p7;
  //static vct3x3 Anode_sphere;
  //static vct3 Tnode_sphere;
  //static vct3 Edge0Norm, Edge1Norm;
  double S0,S1,S2;
  int vsblFaces[3], numFacesProcessed, Fi;
  bool rv;
  
  double sqrtNodeErrorBound = sqrt(NodeErrorBound);


  // === Determine Visible Faces of OBB === //
  //  (and quick escape test)

  // Determine visible faces of OBB by projecting ellipsoid center
  //  onto each axis of the bounding box
  int numVsblFaces = 0;
  bool bVsblFaceFound = 0;
  Fv = Fobb*v;    // center of ellipsoid in OBB coords
  
#ifdef QUICK_ESCAPE_SPHERE
  // Quick Escape: Sphere projection
  //  project ellipsoid bounding sphere onto the node axis
  S0 = S1 = S2 = (sqrtNodeErrorBound/Dmin);
#else
  std::cout << "ERROR: quick escape by ellipsoid projection no longer supported" << std::endl;
  assert(0);
  //// Quick Escape: Ellipsoid projection
  ////  project ellipsoid itself onto the node axis
  //Ns = sqrtNodeErrorBound * NinvT * node->F.Rotation().Transpose();
  //// since we are working in the node coords, the projections
  ////  values are easy to compute as multiplications of
  ////  Ns and the standard axis unit vectors
  ////S0 = (Ns*vct3(1,0,0)).Norm();
  //S0 = Ns.Column(0).Norm();
  //S1 = Ns.Column(1).Norm();
  //S2 = Ns.Column(2).Norm();
#endif

  if (Fv[0] >= OBB.MaxCorner[0])
  { // Face Fx+ is visible from sample point
    if (Fv[0] > OBB.MaxCorner[0] + S0)
    { // visible face is out-of-range
      return 0;
    }
    vsblFaces[numVsblFaces++] = 1;
  }
  else if (Fv[0] <= OBB.MinCorner[0])
  { // Face Fx- is visible
    if (Fv[0] < OBB.MinCorner[0] - S0)
    { // visible face out-of-range
      return 0;
    }
    vsblFaces[numVsblFaces++] = 2;
  }    
  if (Fv[1] >= OBB.MaxCorner[1])
  { // Face Fy+ is visible
    if (Fv[1] > OBB.MaxCorner[1] + S1)
    { // visible face out-of-range
      return 0;
    }
    vsblFaces[numVsblFaces++] = 3;
  }
  else if (Fv[1] <= OBB.MinCorner[1]) 
  { // Face Fy- is visible
    if (Fv[1] < OBB.MinCorner[1] - S1)
    { // visible face out-of-range
      return 0;
    }
    vsblFaces[numVsblFaces++] = 4;
  }
  if (Fv[2] >= OBB.MaxCorner[2])
  { // Face Fz+ is visible
    if (Fv[2] > OBB.MaxCorner[2] + S2)
    { // visible face out-of-range
      return 0;
    }
    vsblFaces[numVsblFaces++] = 5;
  }
  else if (Fv[2] <= OBB.MinCorner[2])
  { // Face Fz- is visible
    if (Fv[2] < OBB.MinCorner[2] - S2)
    { // visible face out-of-range
      return 0;
    }
    vsblFaces[numVsblFaces++] = 6;
  }
  if (numVsblFaces == 0)
  { // sample point lies w/in node => ellipsoid intersects OBB
    return 1;
  }


  //=== Affine Xfm Ellipsoid -> Sphere ===//

  // Apply affine transform to convert ellipsoid to a sphere 
  //  and convert OBB to a parallelpiped;
  //  then apply translation to move center of sphere to the origin
  Finv = Fobb.Inverse();
  nx = Finv.Rotation().Column(0);   // OBB axis in world coords
  ny = Finv.Rotation().Column(1);   //  ''
  nz = Finv.Rotation().Column(2);   //  ''
  m = Finv.Translation();           // OBB origin in world coords
  m = N*(m - v);                // OBB origin in sphere coords

  //// Transforms points from sphere coords to node coords [A,t]
  //Anode_sphere = node->F.Rotation()*Ninv;                       // affine
  //Tnode_sphere = node->F.Rotation()*v + node->F.Translation();  // offset

  // parallelpiped axis
  //  Note: axis unit vectors are no longer oriented to the face normals
  //        due to the skewed nature of the parallelpiped (i.e. due to affine skew)
  Vx_ = N*nx;     // affine xfmd OBB axis (do not make these unit vectors!)
  Vy_ = N*ny;
  Vz_ = N*nz;

  //  Note: we cannot assume that the OBB have equal extents along the +/- dir
  //        of each coordinate axis, because the origin for the node is based
  //        on statistics of a single vertex from each triangle.
  //        We may, however, assume that the extents are positive along each
  //        axis direction, i.e. that the origin lies within the node.
  Vxpos = OBB.MaxCorner[0]*Vx_;  // parallelpiped extents along each axis
  Vypos = OBB.MaxCorner[1]*Vy_;  //  ''
  Vzpos = OBB.MaxCorner[2]*Vz_;  //  ''
  Vxneg = OBB.MinCorner[0]*Vx_;  //  ''
  Vyneg = OBB.MinCorner[1]*Vy_;  //  ''
  Vzneg = OBB.MinCorner[2]*Vz_;  //  ''
  m_Vxp = m + Vxpos;              // precompute these for efficiency
  m_Vxn = m + Vxneg;              //  ''
  Vyp_Vzp = Vypos + Vzpos;        //  ''
  Vyp_Vzn = Vypos + Vzneg;        //  ''
  Vyn_Vzp = Vyneg + Vzpos;        //  ''
  Vyn_Vzn = Vyneg + Vzneg;        //  ''
  p0 = m_Vxp + Vyp_Vzp;           // parallelpiped vertices
  p1 = m_Vxp + Vyp_Vzn;           //  ''
  p2 = m_Vxp + Vyn_Vzp;           //  ''
  p3 = m_Vxp + Vyn_Vzn;           //  ''
  p4 = m_Vxn + Vyp_Vzp;           //  ''
  p5 = m_Vxn + Vyp_Vzn;           //  ''
  p6 = m_Vxn + Vyn_Vzp;           //  ''
  p7 = m_Vxn + Vyn_Vzn;           //  ''

  // face normals of parallelpiped
  Nx.Assign( vctCrossProduct(Vy_,Vz_).Normalized() );
  Ny.Assign( vctCrossProduct(Vz_,Vx_).Normalized() );
  Nz.Assign( vctCrossProduct(Vx_,Vy_).Normalized() );


  //=== Check for Sphere/Parallelpiped Intersection ===//

  // Check for Sphere-Parallelpiped Overlap
  //  Note: the code below assumes that visible faces are added to
  //        the queue in order from lowest to highest face index
  numFacesProcessed = 0;
  Fi = vsblFaces[numFacesProcessed++];
  
  //if (Fi == 1 || Fi == 2)
  //{ 
    // compute in-plane edge normals for this face pair
    //  Note: these need not be unit vectors
    //Edge0Norm =  Nz - vctDotProduct(Nz,Nx)*Nx;  // in-plane component of Nz
    //Edge1Norm = -Ny + vctDotProduct(Ny,Nx)*Nx;  // in-plane component of -Ny
    if (Fi == 1)
    { // check sphere-face intersection
      rv = IntersectionSphereFace( Nx, p0,p2,p3,p1,
                                   sqrtNodeErrorBound, NodeErrorBound);
                                   //Edge0Norm,Edge1Norm,-Edge0Norm,-Edge1Norm,
      if (rv) return 1;
      // no intersection => get next visible face
      if (numFacesProcessed == numVsblFaces) return 0;
      Fi = vsblFaces[numFacesProcessed++];
    }
    if (Fi == 2)
    { // check sphere-face intersection
      rv = IntersectionSphereFace( -Nx, p6,p4,p5,p7,
                                   sqrtNodeErrorBound, NodeErrorBound);
                                   //Edge0Norm,-Edge1Norm,-Edge0Norm,Edge1Norm,
      if (rv) return 1;
      // no intersection => get next visible face
      if (numFacesProcessed == numVsblFaces) return 0;
      Fi = vsblFaces[numFacesProcessed++];
    }
  //}
  //if (Fi == 3 || Fi == 4)
  //{ 
    // compute in-plane edge normals for this face pair
    //  Note: these need not be unit vectors
    //Edge0Norm = Nz - vctDotProduct(Nz,Ny)*Ny; // in-plane component of Nz
    //Edge1Norm = Nx - vctDotProduct(Nx,Ny)*Ny; // in-plane component of Nx
    if (Fi == 3)
    { // check sphere-face intersection
      rv = IntersectionSphereFace( Ny, p4,p0,p1,p5,
                                   sqrtNodeErrorBound, NodeErrorBound);
                                   //Edge0Norm,Edge1Norm,-Edge0Norm,-Edge1Norm,
      if (rv){
        //std::cout << "--> Intersection" << std::endl; 
        return 1;
      }
      // no intersection => get next visible face
      if (numFacesProcessed == numVsblFaces) return 0;
      Fi = vsblFaces[numFacesProcessed++];
    }
    if (Fi == 4)
    { // check sphere-face intersection
      rv = IntersectionSphereFace( -Ny, p2,p6,p7,p3,
                                   sqrtNodeErrorBound, NodeErrorBound);
                                   //Edge0Norm,-Edge1Norm,-Edge0Norm,Edge1Norm,
      if (rv) return 1;
      // no intersection => get next visible face
      if (numFacesProcessed == numVsblFaces) return 0;
      Fi = vsblFaces[numFacesProcessed++];
    }
  //}
  //if (Fi == 5 || Fi == 6)
  //{ 
    // compute in-plane edge normals for this face pair
    //  Note: these need not be unit vectors
    //Edge0Norm = -Nx + vctDotProduct(Nx,Nz)*Nz;  // in-plane component of -Nx
    //Edge1Norm = -Ny + vctDotProduct(Ny,Nz)*Nz;  // in-plane component of -Ny
    if (Fi == 5)
    { // check sphere-face intersection
      rv = IntersectionSphereFace( Nz, p4,p6,p2,p0,
                                   sqrtNodeErrorBound, NodeErrorBound);
                                   //Edge0Norm,Edge1Norm,-Edge0Norm,-Edge1Norm,
      if (rv) return 1;
      // no intersection => get next visible face
      if (numFacesProcessed == numVsblFaces) return 0;
      Fi = vsblFaces[numFacesProcessed++];
    }
    if (Fi == 6)
    { // check sphere-face intersection
      rv = IntersectionSphereFace( -Nz, p1,p3,p7,p5,                                   
                                   sqrtNodeErrorBound, NodeErrorBound);
                                   //-Edge0Norm,Edge1Norm,Edge0Norm,-Edge1Norm,
      if (rv) return 1;
      // no intersection => get next visible face
      if (numFacesProcessed == numVsblFaces) return 0;
    }
  //}

  // should never arrive here
    std::cout << "ERROR: execution should never arrive here" << std::endl;
  assert(0);
  return 0;
}